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

    /**
     * @brief used when creating the thread for processing the files enqueued 
     * 
     * @param arg 
     * @return void* always NULL
     */
    void* executor(void* arg);

    /**
     * @brief read data from a file
     * @brief used in mapper::executor
     * 
     * @param path relative path for the file to read
     * @param t_id thread id
     */
    void read_from_file(std::string path, int t_id);    
} // end of namespace mapper