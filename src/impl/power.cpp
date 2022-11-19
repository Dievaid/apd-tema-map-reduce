#include "../libs/power.hpp"

#include "../impl/data_controller.cpp"
#include "../libs/reducer.hpp"

#include <cmath>
#include <iostream>

// https://cstheory.stackexchange.com/questions/2077/how-to-check-if-a-number-is-a-perfect-power-in-polynomial-time

bool power::is_power(long long n)
{
    if (n == 1)
    {
        return true;
    }

    int lgn = log2(n);

    for (int b = 2; b < data::controller::get().reducers() + reducer::MEM_OFFSET; b++)
    {
        long lowA = 1L;
        long highA = 1L << (lgn / b + 1);
        while (lowA < highA - 1)
        {
            long midA = (lowA + highA) >> 1;
            long long ab = pow(midA, b);
            if (ab > n)
            {
                highA = midA;
            }
            else if (ab < n)
            {
                lowA = midA;
            }
            else
            {
                return true;
            }
        }
    }
    return false;
}

bool power::check_by_exponent(long long n, int exp)
{
    long lgn = log2(n);
    long lowA = 1L;
    long highA = 1L << (lgn / exp + 1);
    while (lowA < highA - 1)
    {
        long midA = (lowA + highA) >> 1;
        long long ab = pow(midA, exp);
        if (ab > n)
        {
            highA = midA;
        }
        else if (ab < n)
        {
            lowA = midA;
        }
        else
        {
            return true;
        }
    }
    return false;
}