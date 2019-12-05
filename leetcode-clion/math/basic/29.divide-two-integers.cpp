/*
 * @lc app=leetcode id=29 lang=cpp
 *
 * [29] Divide Two Integers
 *
 * https://leetcode.com/problems/divide-two-integers/description/
 *
 * algorithms
 * Medium (16.16%)
 * Total Accepted:    225.2K
 * Total Submissions: 1.4M
 * Testcase Example:  '10\n3'
 *
 * Given two integers dividend and divisor, divide two integers without using
 * multiplication, division and mod operator.
 * 
 * Return the quotient after dividing dividend by divisor.
 * 
 * The integer division should truncate toward zero.
 * 
 * Example 1:
 * 
 * 
 * Input: dividend = 10, divisor = 3
 * Output: 3
 * 
 * Example 2:
 * 
 * 
 * Input: dividend = 7, divisor = -3
 * Output: -2
 * 
 * Note:
 * 
 * 
 * Both dividend and divisor will be 32-bit signed integers.
 * The divisor will never be 0.
 * Assume we are dealing with an environment which could only store integers
 * within the 32-bit signed integer range: [−2^31,  2^31 − 1]. For the purpose
 * of this problem, assume that your function returns 2^31 − 1 when the
 * division result overflows.
 * 
 * 
 */
class Solution {
public:
    // 4ms, 8.2MB, 76.52%
    int divide(int dividend, int divisor) {
        if (divisor == 0 || (dividend == 1 << 31 && divisor == -1))
            return ~(1 << 31);
        long long m = dividend, n = divisor;
        int sign = 1;
        if (dividend < 0) {
            m = -m;
            sign = -sign;
        }
        if (divisor < 0) {
            n = -n;
            sign = -sign;
        }
        if (n == 1) return sign == 1 ? m : -m;
        int res = 0;
        while (m >= n) {
            long long q = 1, tmp = n;
            while (m >= (tmp << 1)) {
                q <<= 1;
                tmp <<= 1;
            }
            m -= tmp;
            res += q;
        }
        return sign == 1 ? res : -res;
    }
};
