/*
 * @lc app=leetcode id=204 lang=cpp
 *
 * [204] Count Primes
 *
 * https://leetcode.com/problems/count-primes/description/
 *
 * algorithms
 * Easy (30.06%)
 * Total Accepted:    279.7K
 * Total Submissions: 930.5K
 * Testcase Example:  '10'
 *
 * Count the number of prime numbers less than a non-negative number, n.
 * 
 * Example:
 * 
 * 
 * Input: 10
 * Output: 4
 * Explanation: There are 4 prime numbers less than 10, they are 2, 3, 5, 7.
 * 
 * 
 */

#include <cmath>

class Solution {
public:
    bool isPrime(int m) {
        int s = sqrt(m);
        for (int divisor = 2; divisor <= s; ++divisor)
            if (m % divisor == 0)
                return false;
        return true;
    }

    // 604ms, 8.2MB, 9.05%
    int countPrimes1(int n) {
        if (n < 3)
            return 0;
        int res = 0;
        for (int i = 2; i < n; ++i)
            res += isPrime(i);
        return res;
    }

    // 60ms, 8.6MB, 65.23%
    int countPrimes(int n) {
        int res = 0;
        vector<bool> isPrime(n, true);
        // check [2, n-1]
        int mid = sqrt(n);
        for (long long i = 2; i <= mid; ++i) {
            if (!isPrime[i]) continue;
            ++res;
            for (long long j = 2 * i; j < n; j += i)
                isPrime[j] = false;
        }
        for (int i = mid + 1; i < n; ++i)
            if (isPrime[i])
                ++res;
        return res;
    }

};
