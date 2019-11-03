/*
 * @lc app=leetcode id=32 lang=cpp
 *
 * [32] Longest Valid Parentheses
 *
 * https://leetcode.com/problems/longest-valid-parentheses/description/
 *
 * algorithms
 * Hard (26.61%)
 * Total Accepted:    225.5K
 * Total Submissions: 847.4K
 * Testcase Example:  '"(()"'
 *
 * Given a string containing just the characters '(' and ')', find the length
 * of the longest valid (well-formed) parentheses substring.
 * 
 * Example 1:
 * 
 * 
 * Input: "(()"
 * Output: 2
 * Explanation: The longest valid parentheses substring is "()"
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: ")()())"
 * Output: 4
 * Explanation: The longest valid parentheses substring is "()()"
 * 
 * 
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:

    // DP
    int longestValidParentheses_tle(string s) {
        int len = s.length();
        if (len < 2)
            return 0;
        int maxLen = 0;
        vector<int> dp(len);
        for (int i = 0; i < len - 1; ++i) {
            dp[i] = (s[i] == '(') ? 1 : -1;
            if (dp[i] == -1)
                continue;
            for (int j = i + 1; j < len; ++j) {
                if (dp[j - 1] == -1)
                    break;
                dp[j] = dp[j - 1] + ((s[j] == '(') ? 1 : -1);
                if (dp[j] == 0)
                    maxLen = max(maxLen, j - i + 1);
            }
            if (maxLen >= len - i)
                return maxLen;
        }
        return maxLen;
    }

    // DP, reduce memory usage
    // 572ms, 9.2MB, 5.01%
    int longestValidParentheses_dp(string s) {
        int len = s.length();
        if (len < 2)
            return 0;
        int maxLen = 0;
        int lsubr_pre, lsubr_cur;
        for (int i = 0; i < len - 1; ++i) {
            lsubr_pre = (s[i] == '(') ? 1 : -1;
            for (int j = i + 1; j < len; ++j) {
                if (lsubr_pre == -1)
                    break;
                lsubr_cur = lsubr_pre + ((s[j] == '(') ? 1 : -1);
                if (lsubr_cur == 0)
                    maxLen = max(maxLen, j - i + 1);
                lsubr_pre = lsubr_cur;
            }
            if (maxLen >= len - i)
                return maxLen;
        }
        return maxLen;
    }

    // better DP
    // 8ms, 9.7MB, 59.86%
    int longestValidParentheses(string s) {
        int len = s.length();
        if (len < 2)
            return 0;
        int res = 0;
        // dp[i]: longest valid parentheses from s[?] to s[i]
        vector<int> dp(len, 0);
        for (int i = 1; i < len; ++i) {
            if (s[i] == ')') {
                int pos = i - dp[i - 1] - 1;
                if (pos >= 0 && s[pos] == '(') {
                    dp[i] = dp[i - 1] + 2 + (pos > 1 ? dp[pos - 1] : 0);
                    res = max(res, dp[i]);
                }
            }
        }
        return res;
    }

};
