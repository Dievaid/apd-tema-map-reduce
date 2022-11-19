// lib header include
#include "../libs/mapper.hpp"

#include "./data_controller.cpp"
#include "../libs/power.hpp"

#include <iostream>
#include <fstream>
#include <set>
#include <queue>
#include <cmath>

void mapper::read_from_file(std::string path, int t_id)
{
    const auto& powers = data::controller::get().mapper_results()[t_id];

    std::ifstream fin(path);
    int no = 0;
    fin >> no;

    for (int i = 0; i < no; i++)
    {
        long read_num = 0;
        fin >> read_num;
        
        if (power::is_power(read_num))
        {
            powers->insert(read_num);
        }
    }    
}

mapper::Info::Info(int t_id, std::queue<std::string>* file_queue, pthread_mutex_t* q_mutex, pthread_barrier_t* barrier)
    : t_id(t_id), file_queue(file_queue), q_mutex(q_mutex), barrier(barrier) { }

void* mapper::executor(void* arg)
{
    mapper::Info* info = static_cast<mapper::Info*>(arg);

    while (!info->file_queue->empty())
    {
        pthread_mutex_lock(info->q_mutex);
        std::string path = info->file_queue->front();
        info->file_queue->pop();
        pthread_mutex_unlock(info->q_mutex);

        mapper::read_from_file(path, info->t_id);
    }

    pthread_barrier_wait(info->barrier);    
    pthread_exit(NULL);
}