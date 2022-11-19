#pragma once

#include <vector>
#include <set>
#include <pthread.h>

namespace reducer
{
    constexpr int MEM_OFFSET = 2;

    struct Info
    {
        int t_id;
        std::vector<std::set<long long>*>* mapper_result;
        pthread_barrier_t* barrier;

        Info(int, std::vector<std::set<long long>*>*, pthread_barrier_t*);
        ~Info();
    };

    void* executor(void*);

    std::set<long long>& take_powers_of(int, std::vector<std::set<long long>*>*);

    void write_to_file(int, const std::set<long long>&);
} // end of namespace reducer