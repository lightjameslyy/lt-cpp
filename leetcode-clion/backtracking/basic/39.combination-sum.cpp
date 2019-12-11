/*
 * @lc app=leetcode id=39 lang=cpp
 *
 * [39] Combination Sum
 *
 * https://leetcode.com/problems/combination-sum/description/
 *
 * algorithms
 * Medium (51.49%)
 * Total Accepted:    414.6K
 * Total Submissions: 805.2K
 * Testcase Example:  '[2,3,6,7]\n7'
 *
 * Given a set of candidate numbers (candidates) (without duplicates) and a
 * target number (target), find all unique combinations in candidates where the
 * candidate numbers sums to target.
 * 
 * The same repeated number may be chosen from candidates unlimited number of
 * times.
 * 
 * Note:
 * 
 * 
 * All numbers (including target) will be positive integers.
 * The solution set must not contain duplicate combinations.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: candidates = [2,3,6,7], target = 7,
 * A solution set is:
 * [
 * ⁠ [7],
 * ⁠ [2,2,3]
 * ]
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: candidates = [2,3,5], target = 8,
 * A solution set is:
 * [
 * [2,2,2,2],
 * [2,3,3],
 * [3,5]
 * ]
 * 
 * 
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    void dfs(vector<int> &candidates, int target, int pos, vector<int> &cur, vector<vector<int>> &res) {
        if (target == 0) {
            res.push_back(cur);
            return;
        }
        if (target < 0)
            return;
        for (int i = pos; i < candidates.size(); ++i) {
            cur.push_back(candidates[i]);
            dfs(candidates, target - candidates[i], i, cur, res);
            cur.pop_back();
        }
    }

    vector<vector<int>> combinationSum(vector<int> &candidates, int target) {
        vector<vector<int>> res;
        vector<int> cur;
        dfs(candidates, target, 0, cur, res);
        return res;
    }
};
