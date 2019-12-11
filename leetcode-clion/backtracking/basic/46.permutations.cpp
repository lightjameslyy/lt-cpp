/*
 * @lc app=leetcode id=46 lang=cpp
 *
 * [46] Permutations
 *
 * https://leetcode.com/problems/permutations/description/
 *
 * algorithms
 * Medium (58.25%)
 * Total Accepted:    458.3K
 * Total Submissions: 786.8K
 * Testcase Example:  '[1,2,3]'
 *
 * Given a collection of distinct integers, return all possible permutations.
 * 
 * Example:
 * 
 * 
 * Input: [1,2,3]
 * Output:
 * [
 * ⁠ [1,2,3],
 * ⁠ [1,3,2],
 * ⁠ [2,1,3],
 * ⁠ [2,3,1],
 * ⁠ [3,1,2],
 * ⁠ [3,2,1]
 * ]
 * 
 * 
 */
#include <vector>

using namespace std;

class Solution {
public:
    void dfs(vector<int> &nums, vector<int> &path,
             vector<bool> &used, vector<vector<int>> &res) {
        if (path.size() == nums.size()) {
            res.push_back(path);
            return;
        }
        for (int i = 0; i < nums.size(); ++i) {
            if (used[i]) continue;
            used[i] = true;
            path.push_back(nums[i]);
            dfs(nums, path, used, res);
            path.pop_back();
            used[i] = false;
        }
    }

    vector<vector<int>> permute(vector<int> &nums) {
        vector<vector<int>> res;
        vector<int> path;
        path.reserve(nums.size());
        vector<bool> used(nums.size(), false);
        dfs(nums, path, used, res);
        return res;
    }
};
