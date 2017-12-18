#include <iostream>
#include <thread>
#include <vector>
#include <future>
#include "vk/client.hpp"
#include "vk/threads.hpp"

std::vector<Document> lst;

int main()
{
    std::cout<<std::endl<<"hardware_concurrency: "<<std::endl;
    std::cout<<std::thread::hardware_concurrency()<<std::endl;
    std::cout<<std::endl;
    Client client ("87b0f4e887b0f4e887b0f4e81f87ef2e05887b087b0f4e8dd928ec42b8c3a9268d740d1"); //старый "просроченный" токен
    if (client.check_connection())
    {
        std::cout<<std::endl<<"Successfully connected!"<<std::endl;
        lst = client.get_docs();
        Vk_Thread th(lst);
        if (th.user_input())
        {
            std::cout << "END" << std::endl;
        }
        else
        {
            std::cout << "EGGOG";
        }

    }
    else
        std::cout<<std::endl<<"Connection failed!"<<std::endl;
    return 0;
}


