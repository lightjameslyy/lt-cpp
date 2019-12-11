/*
 * @lc app=leetcode id=90 lang=cpp
 *
 * [90] Subsets II
 *
 * https://leetcode.com/problems/subsets-ii/description/
 *
 * algorithms
 * Medium (44.16%)
 * Total Accepted:    231.2K
 * Total Submissions: 523.5K
 * Testcase Example:  '[1,2,2]'
 *
 * Given a collection of integers that might contain duplicates, nums, return
 * all possible subsets (the power set).
 * 
 * Note: The solution set must not contain duplicate subsets.
 * 
 * Example:
 * 
 * 
 * Input: [1,2,2]
 * Output:
 * [
 * ⁠ [2],
 * ⁠ [1],
 * ⁠ [1,2,2],
 * ⁠ [2,2],
 * ⁠ [1,2],
 * ⁠ []
 * ]
 * 
 * 
 */
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    void dfs(const vector<int> &nums, int pos, vector<int> &cur, vector<vector<int>> &res) {
        res.push_back(cur);

        for (int i = pos; i < nums.size(); ++i) {
            if (i > pos && nums[i] == nums[i - 1])
                continue;
            cur.push_back(nums[i]);
            dfs(nums, i + 1, cur, res);
            cur.pop_back();
        }
    }

    vector<vector<int>> subsetsWithDup(vector<int> &nums) {
        vector<vector<int>> res;
        vector<int> cur;
        sort(nums.begin(), nums.end());
        dfs(nums, 0, cur, res);
        return res;
    }
};
