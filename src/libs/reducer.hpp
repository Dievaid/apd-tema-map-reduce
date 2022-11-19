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

    /**
     * @brief take an exponent and extract all the powers of it
     * 
     * @return std::set<long long>& all the unique values raised to the passed power as parameter
     */
    std::set<long long>& take_powers_of(int);

    /**
     * @brief writes data into the reducer thread's specific file
     * 
     */
    void write_to_file(int, const std::set<long long>&);
} // end of namespace reducer