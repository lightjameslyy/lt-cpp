/*
 * @lc app=leetcode id=216 lang=cpp
 *
 * [216] Combination Sum III
 *
 * https://leetcode.com/problems/combination-sum-iii/description/
 *
 * algorithms
 * Medium (53.50%)
 * Total Accepted:    139.2K
 * Total Submissions: 260.1K
 * Testcase Example:  '3\n7'
 *
 * 
 * Find all possible combinations of k numbers that add up to a number n, given
 * that only numbers from 1 to 9 can be used and each combination should be a
 * unique set of numbers.
 * 
 * Note:
 * 
 * 
 * All numbers will be positive integers.
 * The solution set must not contain duplicate combinations.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: k = 3, n = 7
 * Output: [[1,2,4]]
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: k = 3, n = 9
 * Output: [[1,2,6], [1,3,5], [2,3,4]]
 * 
 * 
 */
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    void dfs(int n, int k, int pos, vector<int> &cur, vector<vector<int>> &res) {
        if (k < 0 || n < 0)
            return;
        if (!k && !n) {
            res.push_back(cur);
            return;
        }
        for (int i = pos; i <= 9; ++i) {
            cur.push_back(i);
            dfs(n - i, k - 1, i + 1, cur, res);
            cur.pop_back();
        }
    }

    vector<vector<int>> combinationSum3(int k, int n) {
        vector<vector<int>> res;
        vector<int> cur;
        dfs(n, k, 1, cur, res);
        return res;
    }
};
