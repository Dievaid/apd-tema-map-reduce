// lib header include
#include "../libs/reducer.hpp"

#include "./data_controller.cpp"
#include "../libs/power.hpp"

#include <fstream>
#include <iostream>
#include <cmath>

reducer::Info::Info(int t_id,
        std::vector<std::set<long long>*>* mapper_result,
        pthread_barrier_t* barrier)
        : t_id(t_id), mapper_result(mapper_result), barrier(barrier) { }

reducer::Info::~Info() = default;

std::set<long long>& reducer::take_powers_of(int n, std::vector<std::set<long long>*>* mapper_result)
{
    std::set<long long>* powers_set = new std::set<long long>();

    for (auto mapper : *mapper_result)
    {
        for (auto el : *mapper)
        {
            if (power::check_by_exponent(el, n) || el == 1)
            {
                powers_set->insert(el);
            }
        }
    }

    return *powers_set;
}

void reducer::write_to_file(int power, const std::set<long long>& numbers)
{
    constexpr int MAX_SIZE = 20;
    char* format_output = new char[MAX_SIZE];
    sprintf(format_output, "out%d.txt", power);

    std::ofstream fout(format_output);
    fout << numbers.size();
    fout.close();
    delete format_output;
}

void* reducer::executor(void* arg)
{
    reducer::Info* info = static_cast<reducer::Info*>(arg);
    pthread_barrier_wait(info->barrier);

    int power_to_scan = info->t_id + reducer::MEM_OFFSET;

    auto& power_set = reducer::take_powers_of(power_to_scan, info->mapper_result);
    reducer::write_to_file(power_to_scan, power_set);

    pthread_exit(NULL);
}