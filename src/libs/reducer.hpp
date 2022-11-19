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
        pthread_barrier_t* barrier;

        Info(int, pthread_barrier_t*);
        ~Info();
    };

    void* executor(void*);

    std::set<long long>& take_powers_of(int);

    void write_to_file(int, const std::set<long long>&);
} // end of namespace reducer