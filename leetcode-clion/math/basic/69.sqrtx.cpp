/*
 * @lc app=leetcode id=69 lang=cpp
 *
 * [69] Sqrt(x)
 *
 * https://leetcode.com/problems/sqrtx/description/
 *
 * algorithms
 * Easy (32.34%)
 * Total Accepted:    434.7K
 * Total Submissions: 1.3M
 * Testcase Example:  '4'
 *
 * Implement int sqrt(int x).
 * 
 * Compute and return the square root of x, where x is guaranteed to be a
 * non-negative integer.
 * 
 * Since the return type is an integer, the decimal digits are truncated and
 * only the integer part of the result is returned.
 * 
 * Example 1:
 * 
 * 
 * Input: 4
 * Output: 2
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: 8
 * Output: 2
 * Explanation: The square root of 8 is 2.82842..., and since 
 * the decimal part is truncated, 2 is returned.
 * 
 * 
 */

/*
 *
 * binary search
 */

class Solution {
public:
    // 4ms, 8.2MB, 76.76%
    int mySqrt(int x) {
        long long lx = x;
        long long left = 1, right = lx;
        while (left < right) {
            long long mid = left + (right - left) / 2;
            long long val = mid * mid;
            if (val == lx) {
                return mid;
            } else if (val > lx) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        return left * left > lx ? left - 1 : left;
    }
};
