/*
 * @lc app=leetcode id=50 lang=cpp
 *
 * [50] Pow(x, n)
 *
 * https://leetcode.com/problems/powx-n/description/
 *
 * algorithms
 * Medium (28.74%)
 * Total Accepted:    373.5K
 * Total Submissions: 1.3M
 * Testcase Example:  '2.00000\n10'
 *
 * Implement pow(x, n), which calculates x raised to the power n (x^n).
 * 
 * Example 1:
 * 
 * 
 * Input: 2.00000, 10
 * Output: 1024.00000
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: 2.10000, 3
 * Output: 9.26100
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: 2.00000, -2
 * Output: 0.25000
 * Explanation: 2^-2 = 1/2^2 = 1/4 = 0.25
 * 
 * 
 * Note:
 * 
 * 
 * -100.0 < x < 100.0
 * n is a 32-bit signed integer, within the range [−2^31, 2^31 − 1]
 * 
 * 
 */

/*
 * bitwise scan
 */

class Solution {
public:
    // 4ms, 8.4MB, 60.25%
    double myPow(double x, int n) {
        long long ln = n;
        if (ln < 0)
            ln = -ln;
        double res = 1.0, factor = x;
        while (ln > 0) {
            if (ln & 1)
                res *= factor;
            ln >>= 1;
            factor *= factor;
        }
        return n >= 0 ? res : 1 / res;
    }
};
