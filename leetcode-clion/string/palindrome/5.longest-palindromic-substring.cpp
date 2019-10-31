/*
 * @lc app=leetcode id=5 lang=cpp
 *
 * [5] Longest Palindromic Substring
 *
 * https://leetcode.com/problems/longest-palindromic-substring/description/
 *
 * algorithms
 * Medium (28.17%)
 * Total Accepted:    698.2K
 * Total Submissions: 2.5M
 * Testcase Example:  '"babad"'
 *
 * Given a string s, find the longest palindromic substring in s. You may
 * assume that the maximum length of s is 1000.
 * 
 * Example 1:
 * 
 * 
 * Input: "babad"
 * Output: "bab"
 * Note: "aba" is also a valid answer.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: "cbbd"
 * Output: "bb"
 * 
 * 
 */

#include <vector>

using namespace std;

class Solution {
public:
    // DP:
    // base: p(i,i) = true
    //       p(i, i+1) = (s[i] == s[i+1])
    // dp: p(i, j) = p(i+1, j-1) && (s[i] == s[j])
    // 104ms, 9MB, 41.12%
    string longestPalindrome_dp(string s) {
        int slen = s.length();
        int left = 0;
        int maxLen = 0;
        vector<int> dp(slen, 0);
        for (int j = 0; j < slen; ++j) {
            for (int i = 0; i <= j; ++i) {
                if (i == j)
                    dp[i] = 1;
                else if (j == i + 1) {
                    dp[i] = (s[i] == s[i + 1]);
                } else {
                    dp[i] = dp[i + 1] && (s[i] == s[j]);
                }
                if (dp[i] == 1) {
                    if (j - i + 1 > maxLen) {
                        maxLen = j - i + 1;
                        left = i;
                    }
                }
            }
        }
        return s.substr(left, maxLen);
    }

    int expandAroundCenter(const string &s, int left, int right) {
        while (left >= 0 && right < s.length() && s[left] == s[right]) {
            left--;
            right++;
        }
        return right - left - 1;
    }

    // expand around center
    // 12ms, 8.8MB, 87.91%
    string longestPalindrome(string s) {
        int slen = s.length();
        if (slen < 2)
            return s;
        int maxLen = 0;
        int pos = 0;
        for (int i = 0; i < slen; ++i) {
            int len1 = expandAroundCenter(s, i, i); // odd
            int len2 = expandAroundCenter(s, i, i + 1); // even
            int len = max(len1, len2);
            if (len > maxLen) {
                maxLen = len;
                pos = i - (len - 1) / 2;
            }
        }
        return s.substr(pos, maxLen);
    }
};
