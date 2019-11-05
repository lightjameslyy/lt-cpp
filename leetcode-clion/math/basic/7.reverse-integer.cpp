/*
 * @lc app=leetcode id=7 lang=cpp
 *
 * [7] Reverse Integer
 *
 * https://leetcode.com/problems/reverse-integer/description/
 *
 * algorithms
 * Easy (25.53%)
 * Total Accepted:    848.8K
 * Total Submissions: 3.3M
 * Testcase Example:  '123'
 *
 * Given a 32-bit signed integer, reverse digits of an integer.
 * 
 * Example 1:
 * 
 * 
 * Input: 123
 * Output: 321
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: -123
 * Output: -321
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: 120
 * Output: 21
 * 
 * 
 * Note:
 * Assume we are dealing with an environment which could only store integers
 * within the 32-bit signed integer range: [−2^31,  2^31 − 1]. For the purpose
 * of this problem, assume that your function returns 0 when the reversed
 * integer overflows.
 * 
 */

#include <climits>

using namespace std;

class Solution {
public:
    // 4ms, 8.3MB, 68.64%
    int reverse(int x) {
        long long llx = x;
        long long orig = (llx >= 0) ? llx : -llx;
        long long res = 0;
        while (orig > 0) {
            res *= 10;
            res += orig % 10;
            orig = orig / 10;
        }
        res = (llx >= 0) ? res : -res;
        if (res < INT_MIN || res > INT_MAX)
            return 0;
        return res;
    }
};
