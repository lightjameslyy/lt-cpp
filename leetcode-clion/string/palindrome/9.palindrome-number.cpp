/*
 * @lc app=leetcode id=9 lang=cpp
 *
 * [9] Palindrome Number
 *
 * https://leetcode.com/problems/palindrome-number/description/
 *
 * algorithms
 * Easy (45.42%)
 * Total Accepted:    714.2K
 * Total Submissions: 1.6M
 * Testcase Example:  '121'
 *
 * Determine whether an integer is a palindrome. An integer is a palindrome
 * when it reads the same backward as forward.
 * 
 * Example 1:
 * 
 * 
 * Input: 121
 * Output: true
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: -121
 * Output: false
 * Explanation: From left to right, it reads -121. From right to left, it
 * becomes 121-. Therefore it is not a palindrome.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: 10
 * Output: false
 * Explanation: Reads 01 from right to left. Therefore it is not a
 * palindrome.
 * 
 * 
 * Follow up:
 * 
 * Coud you solve it without converting the integer to a string?
 * 
 */

using namespace std;

class Solution {
public:
    // INT32_MAX = 2147483647, contains 10 digits
    // 24ms, 8.1MB, 18.69%
    bool isPalindrome_my(int x) {
        if (x < 0) return false;
        if (x < 10) return true;
        int order = 1e9;
        while (x / order == 0)
            order /= 10;
        while (order >= 10) {
            int high = x / order;
            x -= high * order;
            int low = x % 10;
            x /= 10;
            if (high != low)
                return false;
            order /= 100;
        }
        return true;
    }

    // generate the reverse number
    // NOTE: be careful of overflow
    bool isPalindrome_long_long(int x) {
        if (x < 0) return false;
        if (x < 10) return true;
        long long rev_x = 0;
        int tmp = x;
        while (tmp) {
            rev_x += (tmp % 10);
            if (tmp /= 10)
                rev_x *= 10;
        }
        return rev_x == x;
    }

    // check in case of overflow
    // 12ms, 8.1MB, 72.61%
    bool isPalindrome(int x) {
        if (x < 0) return false;
        if (x < 10) return true;
        int rev_x = 0;
        for (int tmp = x; tmp > 0; tmp /= 10) {
            if (rev_x > INT32_MAX / 10)
                return false;
            rev_x = 10 * rev_x + tmp % 10;
        }
        return rev_x == x;
    }
};
