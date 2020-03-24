/*
 * @lc app=leetcode id=516 lang=cpp
 *
 * [516] Longest Palindromic Subsequence
 *
 * https://leetcode.com/problems/longest-palindromic-subsequence/description/
 *
 * algorithms
 * Medium (49.11%)
 * Total Accepted:    79K
 * Total Submissions: 161K
 * Testcase Example:  '"bbbab"'
 *
 *
 * Given a string s, find the longest palindromic subsequence's length in s.
 * You may assume that the maximum length of s is 1000.
 *
 *
 * Example 1:
 * Input:
 *
 * "bbbab"
 *
 * Output:
 *
 * 4
 *
 * One possible longest palindromic subsequence is "bbbb".
 *
 *
 * Example 2:
 * Input:
 *
 * "cbbd"
 *
 * Output:
 *
 * 2
 *
 * One possible longest palindromic subsequence is "bb".
 *
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
  public:
    int longestPalindromeSubseq(string s) {
        int n = s.length();
        if (n == 0)
            return 0;

        // dp[i][j]: longest palindromic subsequence in s[i:j]
        vector<vector<int>> dp(n, vector<int>(n, 0));
        // base case
        for (int i = 0; i < n; ++i)
            dp[i][i] = 1;

        // upwards, rightwards
        for (int i = n - 2; i >= 0; --i) {
            for (int j = i + 1; j < n; ++j) {
                if (s[i] == s[j])
                    dp[i][j] = dp[i + 1][j - 1] + 2;
                else
                    dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
            }
        }
        return dp[0][n - 1];
    }
};
