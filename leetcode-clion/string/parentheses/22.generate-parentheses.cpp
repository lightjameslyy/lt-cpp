/*
 * @lc app=leetcode id=22 lang=cpp
 *
 * [22] Generate Parentheses
 *
 * https://leetcode.com/problems/generate-parentheses/description/
 *
 * algorithms
 * Medium (57.82%)
 * Total Accepted:    413.9K
 * Total Submissions: 715.9K
 * Testcase Example:  '3'
 *
 * 
 * Given n pairs of parentheses, write a function to generate all combinations
 * of well-formed parentheses.
 * 
 * 
 * 
 * For example, given n = 3, a solution set is:
 * 
 * 
 * [
 * ⁠ "((()))",
 * ⁠ "(()())",
 * ⁠ "(())()",
 * ⁠ "()(())",
 * ⁠ "()()()"
 * ]
 * 
 */

#include <vector>

using namespace std;

class Solution {
public:

    void helper(int n, string cur, int left_count, int right_count, vector<string> &res) {
        if (right_count == n) {
            res.push_back(cur);
            return;
        }
        if (left_count < n)
            helper(n, cur + '(', left_count + 1, right_count, res);
        if (right_count < left_count)
            helper(n, cur + ')', left_count, right_count + 1, res);
    }

    // backtracking
    // 8ms, 17.1MB, 53.97%
    vector<string> generateParenthesis_my(int n) {
        if (n == 0)
            return {""};
        vector<string> res;
        helper(n, "(", 1, 0, res);
        return res;
    }


    void helper1(string &cur, int left_remain, int right_remain, vector<string> &res) {
        if (left_remain == 0 && right_remain == 0) {
            res.push_back(cur);
            return;
        }
        if (left_remain > 0) {
            cur += '(';
            helper1(cur, left_remain - 1, right_remain + 1, res);
            cur.pop_back();
        }
        if (right_remain > 0) {
            cur += ')';
            helper1(cur, left_remain, right_remain - 1, res);
            cur.pop_back();
        }
    }

    // more concise solution, reduce memory
    // 4ms, 13.8MB, 88.02%
    vector<string> generateParenthesis(int n) {
        vector<string> res;
        string cur = "";
        helper1(cur, n, 0, res);
        return res;
    }
};
