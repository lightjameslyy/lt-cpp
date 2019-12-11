/*
 * @lc app=leetcode id=78 lang=cpp
 *
 * [78] Subsets
 *
 * https://leetcode.com/problems/subsets/description/
 *
 * algorithms
 * Medium (55.96%)
 * Total Accepted:    436.2K
 * Total Submissions: 779.5K
 * Testcase Example:  '[1,2,3]'
 *
 * Given a set of distinct integers, nums, return all possible subsets (the
 * power set).
 * 
 * Note: The solution set must not contain duplicate subsets.
 * 
 * Example:
 * 
 * 
 * Input: nums = [1,2,3]
 * Output:
 * [
 * ⁠ [3],
 * [1],
 * [2],
 * [1,2,3],
 * [1,3],
 * [2,3],
 * [1,2],
 * []
 * ]
 * 
 */
#include <vector>

using namespace std;

class Solution {
public:

    void dfs(const vector<int> &nums, int pos, vector<int> &cur, vector<vector<int>> &res) {
        if (pos == nums.size()) {
            res.push_back(cur);
            return;
        }
        for (int i = pos; i < nums.size(); ++i) {
            cur.push_back(nums[pos]);
            dfs(nums, i + 1, cur, res);
            cur.pop_back();
        }
    }

    vector<vector<int>> subsets(vector<int> &nums) {
        vector<vector<int>> res;
        vector<int> cur;
        for (int pos = 0; pos <= nums.size(); ++pos)
            dfs(nums, pos, cur, res);
        return res;
    }
};
