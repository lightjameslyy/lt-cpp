/*
 * @lc app=leetcode id=132 lang=cpp
 *
 * [132] Palindrome Partitioning II
 *
 * https://leetcode.com/problems/palindrome-partitioning-ii/description/
 *
 * algorithms
 * Hard (28.56%)
 * Total Accepted:    113.7K
 * Total Submissions: 397.9K
 * Testcase Example:  '"aab"'
 *
 * Given a string s, partition s such that every substring of the partition is
 * a palindrome.
 * 
 * Return the minimum cuts needed for a palindrome partitioning of s.
 * 
 * Example:
 * 
 * 
 * Input: "aab"
 * Output: 1
 * Explanation: The palindrome partitioning ["aa","b"] could be produced using
 * 1 cut.
 * 
 * 
 */

#include <algorithm>

using namespace std;

class Solution {
public:
    bool isPalindrome(const string &s, int left, int right) {
        while (left < right) {
            if (s[left++] != s[right--])
                return false;
        }
        return true;
    }

    // find minimum number of partitions
    void helper(const string &s, int left, int pars, int &minPars) {
        if (left == s.length()) {
            minPars = min(pars, minPars);
            return;
        }
        if (pars >= minPars)
            return;
        for (int right = left; right < s.length(); ++right) {
            if (isPalindrome(s, left, right)) {
                helper(s, right + 1, pars + 1, minPars);
            }
        }
    }

    // backtracking, Time Limited Exceeded...
    int minCut_tle(string s) {
        int slen = s.length();
        int minPars = slen;
        helper(s, 0, 0, minPars);
        return minPars > 0 ? minPars - 1 : 0;
    }

    // DP
    // 40ms, 9.5MB, 35.17%
    int minCut_dp(string s) {
        size_t slen = s.length();
        if (slen == 0)
            return 0;
        // build dp matrix
        vector<vector<bool>> isPal(slen, vector<bool>(slen, false));
        for (size_t j = 0; j < slen; ++j) {
            isPal[j][j] = true;
            for (size_t i = 0; i < j; ++i) {
                if (i + 1 == j) {
                    isPal[i][j] = (s[i] == s[j]);
                } else {
                    isPal[i][j] = isPal[i + 1][j - 1] && (s[i] == s[j]);
                }
            }
        }
        vector<int> minCuts(slen, slen);
        minCuts[0] = 0;
        for (size_t i = 1; i < slen; ++i) {
            if (isPal[0][i]) {
                minCuts[i] = 0;
                continue;
            }
            for (size_t j = 0; j < i; ++j) {
                if (isPal[j + 1][i]) {
                    minCuts[i] = min(minCuts[i], minCuts[j] + 1);
                }
            }
        }
        return minCuts[slen - 1];
    }

    void expandAroundCenter(const string &s, int left, int right, vector<int> &minCuts) {
        while (left >= 0 && right < s.length() && s[left] == s[right]) {
            if (left == 0) {    // s[0, right] is palindrome
                minCuts[right] = 0;
            } else {    // update most right
                minCuts[right] = min(minCuts[right], minCuts[left - 1] + 1);
            }
            left--;
            right++;
        }
    }

    // expand around center
    // 4ms, 8.7MB, 100%
    int minCut(string s) {
        int len = s.length();
        if (len < 2) return 0;
        vector<int> minCuts(len, len);
        for (int i = 0; i < len; ++i) {
            expandAroundCenter(s, i, i, minCuts);
            expandAroundCenter(s, i, i + 1, minCuts);
        }
        return minCuts[len - 1];
    }

};
