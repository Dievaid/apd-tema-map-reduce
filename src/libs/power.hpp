#pragma once

namespace power
{
    /**
     * @brief checks if a number is a perfect power
     * 
     * @param n number to check
     * @return true if it's a perfect power
     * @return false if not
     */
    bool is_power(long long n);

    /**
     * @brief checks if a number can be obtained by being raised by the passed exponent
     * 
     * @param n number to check
     * @param exp the exponent the number n could have been raised to
     * @return true 
     * @return false 
     */
    bool check_by_exponent(long long n, int exp);
}