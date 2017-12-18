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
    Client client ("b0c1dab56ff84bc10520fa7974efe6f21c61c83c9e717c165239b11f82a0f5937d7ff7370ce4f01074700"); //старый "просроченный" токен
    if (client.check_connection())
    {
        std::cout<<std::endl<<"Successfully connected!"<<std::endl;
        lst = client.get_docs();
        std::cout<<std::endl<<"Successfully connected!"<<std::endl;
        Vk_Thread th(lst);
        std::cout<<std::endl<<"Successfully connected!"<<std::endl;
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


