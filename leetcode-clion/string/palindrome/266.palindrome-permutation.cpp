/*
 * @lc app=leetcode id=266 lang=cpp
 *
 * [266] Palindrome Permutation
 *
 * https://leetcode.com/problems/palindrome-permutation/description/
 *
 * algorithms
 * Easy (60.70%)
 * Total Accepted:    73.9K
 * Total Submissions: 121.7K
 * Testcase Example:  '"code"'
 *
 * Given a string, determine if a permutation of the string could form a
 * palindrome.
 * 
 * Example 1:
 * 
 * 
 * Input: "code"
 * Output: false
 * 
 * Example 2:
 * 
 * 
 * Input: "aab"
 * Output: true
 * 
 * Example 3:
 * 
 * 
 * Input: "carerac"
 * Output: true
 * 
 */

using namespace std;

class Solution {
public:
    // statistics in hash
    // 0mx, 8.3MB, 100%
    bool canPermutePalindrome(string s) {
        int countMap[256] = {0};
        for (char c : s) {
            countMap[c]++;
        }
        int oddCount = 0;
        for (int i = 0; i < 256; ++i) {
            if (countMap[i] % 2 != 0)
                oddCount++;
            if (oddCount > 1)
                return false;
        }
        return true;
    }
};
