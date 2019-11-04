/*
 * @lc app=leetcode id=301 lang=cpp
 *
 * [301] Remove Invalid Parentheses
 *
 * https://leetcode.com/problems/remove-invalid-parentheses/description/
 *
 * algorithms
 * Hard (40.76%)
 * Total Accepted:    155.1K
 * Total Submissions: 380.4K
 * Testcase Example:  '"()())()"'
 *
 * Remove the minimum number of invalid parentheses in order to make the input
 * string valid. Return all possible results.
 * 
 * Note: The input string may contain letters other than the parentheses ( and
 * ).
 * 
 * Example 1:
 * 
 * 
 * Input: "()())()"
 * Output: ["()()()", "(())()"]
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: "(a)())()"
 * Output: ["(a)()()", "(a())()"]
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: ")("
 * Output: [""]
 * 
 */

#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
public:

    bool isValid(const string &s) {
        int sum = 0;
        for (char c : s) {
            if (c == '(')
                ++sum;
            else if (c == ')') {
                if (--sum == -1)
                    return false;
            }
        }
        return sum == 0;
    }

    void helper(const string &s, int left_unmatch, int right_unmatch, unordered_set<string> &res) {
        if (left_unmatch == 0 && right_unmatch == 0) {
            if (isValid(s))
                res.insert(s);
            return;
        }
        // consider duplicate situations:
        // not
        // ()()))()
        //    ^
        // but
        // ()()))()
        //      ^
        for (int i = 0; i < s.length(); ++i) {
            if (s[i] == '(' && (i == s.length() - 1 || s[i] != s[i + 1]))
                helper(s.substr(0, i) + s.substr(i + 1), left_unmatch - 1, right_unmatch, res);
            else if (s[i] == ')' && (i == s.length() - 1 || s[i] != s[i + 1]))
                helper(s.substr(0, i) + s.substr(i + 1), left_unmatch, right_unmatch - 1, res);
        }
    }

    // Time Limit Exceeded
    vector<string> removeInvalidParentheses_tle(string s) {
        int len = s.length();
        int sum_paren = 0;
        int left_unmatch = 0, right_unmatch = 0;
        for (char c : s) {
            if (c == '(') {
                ++sum_paren;
                ++left_unmatch;
            } else if (c == ')') {
                ++sum_paren;
                if (left_unmatch > 0)
                    --left_unmatch;
                else
                    ++right_unmatch;
            }
        }
        if (left_unmatch + right_unmatch == sum_paren) {
            string only_str = "";
            for (char c : s) {
                if (c != '(' && c != ')')
                    only_str += c;
            }
            return {only_str};
        }
        unordered_set<string> res;
        helper(s, left_unmatch, right_unmatch, res);
        return vector<string>(res.begin(), res.end());
    }

    void helper(const string &s, int pos, int left_unmatch, int right_unmatch, int unmatch, string &cur,
                vector<string> &res) {
        if (left_unmatch < 0 || right_unmatch < 0 || unmatch < 0)
            return;
        if (pos == s.length()) {
            if (left_unmatch == 0 && right_unmatch == 0 && unmatch == 0)
                res.push_back(cur);
            return;
        }
        char c = s[pos++];
        if (c == '(') {
            // skip, update left_unmatch
            if (cur.empty() || cur.back() != '(')
                helper(s, pos, left_unmatch - 1, right_unmatch, unmatch, cur, res);
            // use, update unmatch
            cur += '(';
            helper(s, pos, left_unmatch, right_unmatch, unmatch + 1, cur, res);
        } else if (c == ')') {
            // skip, update left_unmatch
            if (cur.empty() || cur.back() != ')')
                helper(s, pos, left_unmatch, right_unmatch - 1, unmatch, cur, res);
            // use, update unmatch
            cur += ')';
            helper(s, pos, left_unmatch, right_unmatch, unmatch - 1, cur, res);
        } else {
            cur += c;
            helper(s, pos, left_unmatch, right_unmatch, unmatch, cur, res);
        }
        cur.pop_back();
    }

    // copied backtracking
    // 4ms, 10.3MB, 92.96%
    vector<string> removeInvalidParentheses(string s) {
        int left_unmatch = 0, right_unmatch = 0;
        for (char c : s) {
            if (c == '(') {
                ++left_unmatch;
            } else if (c == ')') {
                if (left_unmatch > 0)
                    --left_unmatch;
                else
                    ++right_unmatch;
            }
        }
        vector<string> res;
        string cur = "";
        helper(s, 0, left_unmatch, right_unmatch, 0, cur, res);
        return res;
    }
};
