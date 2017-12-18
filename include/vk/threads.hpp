#ifndef VKCLIENT_THREADS_H
#define VKCLIENT_THREADS_H

#include <thread>
#include <future>
#include <chrono>
#include <vector>
#include <ctime>
#include "client.hpp"
class Vk_Thread
{
public:
    Vk_Thread(const std::vector<Document>&);

    auto print_thread(uint32_t id) -> void;

    auto launch_threads(uint32_t n) -> bool;

    auto user_input() -> bool;

    ~Vk_Thread();
private:
    uint32_t curr_ptr = 0;
    std::recursive_mutex m;
    bool flag;
    std::vector<Document> lst;
    std::vector<std::thread> vk_vec;

};
#endif //VKCLIENT_THREADS_H
