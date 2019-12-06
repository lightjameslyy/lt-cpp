/*
 * @lc app=leetcode id=367 lang=cpp
 *
 * [367] Valid Perfect Square
 *
 * https://leetcode.com/problems/valid-perfect-square/description/
 *
 * algorithms
 * Easy (40.51%)
 * Total Accepted:    130.3K
 * Total Submissions: 321.7K
 * Testcase Example:  '16'
 *
 * Given a positive integer num, write a function which returns True if num is
 * a perfect square else False.
 * 
 * Note: Do not use any built-in library function such as sqrt.
 * 
 * Example 1:
 * 
 * 
 * 
 * Input: 16
 * Output: true
 * 
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: 14
 * Output: false
 * 
 * 
 * 
 */

/*
 * binary search
 */

class Solution {
public:
    // 0ms, 8.1MB, 100%
    bool isPerfectSquare(int num) {
        long long n = num;
        long long left = 1, right = n;
        while (left < right) {
            long long mid = left + (right - left) / 2;
            long long val = mid * mid;
            if (val == n) {
                return true;
            } else if (val > n) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        return left * left == n;
    }
};
