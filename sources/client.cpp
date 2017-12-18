#include <iostream>
#include <vk/client.hpp>

auto Client::write_data(char* buffer, size_t size, size_t nmemb, std::string* userp_) -> size_t
{
    std::string& userp = *userp_;
    size_t result = 0;

    if (userp.c_str())
    {
        userp.append(buffer, size * nmemb);
        result = size * nmemb;
    }

    return result;
}

// конструктор, принимающий token
Client::Client(std::string token)
{
    a_token = token;
}

// проверка соединения
auto Client::check_connection() -> bool
{

    CURL *curl = curl_easy_init();

    if (curl)
    {
        std::string fields = "access_token=" + a_token + "&v=5.69";

        std::string buffer;

        // адрес, по которому будем переходить
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.vk.com/method/account.getProfileInfo?");

        curl_easy_setopt(curl, CURLOPT_POST, 1);

        //все данные, передаваемые в HTTP POST-запросе
        // передаем токен
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, fields.c_str());

        // указываем размер; до 2 гб, иначе CURLOPT_POSTFIELDSIZE_LARGE
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, fields.length());

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);

        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);

        // отправляем запрос к серверу
        if (curl_easy_perform(curl) == CURLE_OK)
        {
            try
            {
                json server_answer = json::parse(buffer);
                json response = server_answer["response"];
                if (!response.empty())
                {
                    std::cout << "RESPONSE: " << response << std::endl;
                    curl_easy_cleanup(curl);
                    return true;
                }
            }
            catch (const std::exception & ex)
            {
                std::cerr << ex.what() << std::endl;
            }
        }
        else
        {
            curl_easy_cleanup(curl);
            return false;
        }
    }
}


// список всех друзей для выбранного id
auto Client::get_docs() -> std::vector<Document>
{
    CURL *curl = curl_easy_init();

    // если удалось создать дескриптор
    if (curl)
    {
        // прописываем настройки для авторизации через token
       std::string fields = "count=45&offset=0&type=1&owner_id=383793643&access_token=" + a_token + "&v=5.69";
     //   std::string fields = "count=1&offset=0&type=1&owner_id=383793643&access_token=" + a_token + "&v=5.69";

        // строка для получения ответа от сервера
        std::string buffer = "";
        Document document;
        std::vector<Document> lst;

        //     https://vk.com/dev/audio.get?params[owner_id]=123373332&params[need_user]=1&params[count]=3&params[v]=5.60

        // адрес, по которому будем переходить
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.vk.com/method/docs.get?");
        curl_easy_setopt(curl, CURLOPT_POST, 1);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, fields.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, fields.length());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);

        // отправлем запрос к серверу
        if (curl_easy_perform(curl) == CURLE_OK)
        {
            try
            {
                json server_answer = json::parse(buffer);
                json response = server_answer["response"];
                if (!response.empty()) {
                    size_t g_count = response["count"];
                    std::cout << "TOTAL DOCS COUNT: " << g_count << std::endl;
                    if (g_count != 0) {
                        //                       size_t counter = 0;
                        std::cout << "Choose mode: get_docsv or get_docs"<<std::endl;
                        json docs = response["items"];
                        for (json::iterator it = docs.begin(); it != docs.end(); ++it) {
                            document.id = it.value()["id"];
                            document.title = it.value()["title"];
                            document.url = it.value()["url"];
                            document.size = it.value()["size"];
                            lst.push_back(document);
                        }
                    }
                    curl_easy_cleanup(curl);
                    return lst;//true;
                }
            }
            catch (const std::exception &ex)
            {
                std::cerr << ex.what() << std::endl;
            }
        }
        else
        {
            curl_easy_cleanup(curl);
            return lst;//false;
        }
    }
}

auto Client::print_docs() -> void
{
    std::vector<Document> lst = get_docs();
    size_t counter = 0;
    for (std::vector<Document>::iterator it = lst.begin(); it != lst.end(); ++it)
    {
        std::cout << ++counter << "." << std::endl;
        it->print_doc();
    }
}

