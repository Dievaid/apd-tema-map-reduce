#pragma once

#include <string>
#include <queue>

namespace mapper
{
    struct Info
    {
        int t_id;
        std::queue<std::string>* file_queue;
        pthread_mutex_t* q_mutex;
        pthread_barrier_t* barrier;

        Info(int t_id, std::queue<std::string>* file_queue, pthread_mutex_t* q_mutex, pthread_barrier_t* barrier);
        ~Info();
    };

    void* executor(void* arg);

    void read_from_file(std::string path, int t_id);    
} // end of namespace mapper