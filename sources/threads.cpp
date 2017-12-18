#include "vk/threads.hpp"

Vk_Thread::Vk_Thread(const std::vector<Document> &l): lst(l)
{
}

auto Vk_Thread::print_thread(uint32_t id) -> void
{
   do
   {
       time_t  time_vk;
       time_vk=time(0);
       std::lock_guard<std::recursive_mutex> lk(m);
       auto begin = std::chrono::high_resolution_clock::now();
       if (curr_ptr < (lst.size()))
        {
            std::cout<<std::endl<<"----------------------------------------------"<<std::endl<<"Document #"<<(curr_ptr+1)<<" "<<std::endl;
            if (flag)
            {
                std::cout<<"Start time:"<<puts(ctime(&time_vk))<<std::endl;
                std::cout << "number_of_thread: " << id << std::endl;
                lst[curr_ptr].print_doc();
                std::cout<<"End time:"<<puts(ctime(&time_vk))<<std::endl;
                auto end = std::chrono::high_resolution_clock::now();
                std::cout<<"Duration time: "<<std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count()<<" nanoseconds"<< std::endl;

            }
            else
            {
                lst[curr_ptr].print_doc();
            }
        }
       curr_ptr ++;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    } while (curr_ptr < (lst.size()));

}

auto Vk_Thread::launch_threads(uint32_t n) -> bool
{
    curr_ptr = 0;

    if (n<1 || n>std::thread::hardware_concurrency())
    {
        return false;
    }

    for (uint32_t i = 0; i < n; i++)
    {
        vk_vec.push_back(std::thread(&Vk_Thread::print_thread, this, i));
    }

    for (uint32_t i = 0; i < n; i++)
    {
        vk_vec[i].join();
    }
    return true;
}

auto Vk_Thread::user_input() -> bool
{
    std::string cmd;
    uint32_t th_num;
    std::cin >> cmd;

    if (cmd == "get_docsv")
    {
        flag = true;
        std::cout << "Enter the number of threads: " << std::endl;
        std::cin >> th_num;
        return launch_threads(th_num);
    }
    if (cmd == "get_docs")
    {
        flag = false;
        std::cout << "Enter the number of threads: " << std::endl;
        std::cin >> th_num;
        return launch_threads(th_num);
    }
    return false;

}

Vk_Thread::~Vk_Thread()
{

}
