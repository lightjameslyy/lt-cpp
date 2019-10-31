/*
 * @lc app=leetcode id=125 lang=cpp
 *
 * [125] Valid Palindrome
 *
 * https://leetcode.com/problems/valid-palindrome/description/
 *
 * algorithms
 * Easy (32.85%)
 * Total Accepted:    431.2K
 * Total Submissions: 1.3M
 * Testcase Example:  '"A man, a plan, a canal: Panama"'
 *
 * Given a string, determine if it is a palindrome, considering only
 * alphanumeric characters and ignoring cases.
 * 
 * Note: For the purpose of this problem, we define empty string as valid
 * palindrome.
 * 
 * Example 1:
 * 
 * 
 * Input: "A man, a plan, a canal: Panama"
 * Output: true
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: "race a car"
 * Output: false
 * 
 * 
 */

#include <string>
#include <locale>

using namespace std;

class Solution {
public:
    // two-pointers
    // 4ms, 9.4MB, 99.34%
    bool isPalindrome(string s) {
        int slen = s.length();
        int left = 0, right = slen - 1;
        while (left < right) {
            while (left < right && !isalnum(s[left]))
                left++;
            while (right > left && !isalnum(s[right]))
                right--;
            if (left < right && tolower(s[left]) != tolower(s[right]))
                return false;
            left++;
            right--;
        }
        return true;
    }
};
