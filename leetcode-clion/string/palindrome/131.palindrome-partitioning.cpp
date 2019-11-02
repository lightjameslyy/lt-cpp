/*
 * @lc app=leetcode id=131 lang=cpp
 *
 * [131] Palindrome Partitioning
 *
 * https://leetcode.com/problems/palindrome-partitioning/description/
 *
 * algorithms
 * Medium (43.28%)
 * Total Accepted:    187.1K
 * Total Submissions: 432.2K
 * Testcase Example:  '"aab"'
 *
 * Given a string s, partition s such that every substring of the partition is
 * a palindrome.
 * 
 * Return all possible palindrome partitioning of s.
 * 
 * Example:
 * 
 * 
 * Input: "aab"
 * Output:
 * [
 * ⁠ ["aa","b"],
 * ⁠ ["a","a","b"]
 * ]
 * 
 * 
 */

#include <vector>

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

    // pass par as reference to reuse memory
    void helper(const string &s, int left, vector<string> &par, vector<vector<string>> &res) {
        if (left == s.length()) {
            res.push_back(par);
            return;
        }
        for (int right = left; right < s.length(); ++right) {
            if (isPalindrome(s, left, right)) {
                par.push_back(s.substr(left, right - left + 1));
                helper(s, right + 1, par, res);
                par.pop_back(); // revert par for next right position
            }
        }
    }

    // backtracking
    // 12ms, 12.5MB, 89.82%
    vector<vector<string>> partition(string s) {
        vector<vector<string>> res;
        vector<string> par;
        helper(s, 0, par, res);
        return res;
    }
};
