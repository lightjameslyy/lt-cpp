/*
 * @lc app=leetcode id=18 lang=cpp
 *
 * [18] 4Sum
 *
 * https://leetcode.com/problems/4sum/description/
 *
 * algorithms
 * Medium (31.78%)
 * Total Accepted:    272.3K
 * Total Submissions: 856.8K
 * Testcase Example:  '[1,0,-1,0,-2,2]\n0'
 *
 * Given an array nums of n integers and an integer target, are there elements
 * a, b, c, and d in nums such that a + b + c + d = target? Find all unique
 * quadruplets in the array which gives the sum of target.
 * 
 * Note:
 * 
 * The solution set must not contain duplicate quadruplets.
 * 
 * Example:
 * 
 * 
 * Given array nums = [1, 0, -1, 0, -2, 2], and target = 0.
 * 
 * A solution set is:
 * [
 * ⁠ [-1,  0, 0, 1],
 * ⁠ [-2, -1, 1, 2],
 * ⁠ [-2,  0, 0, 2]
 * ]
 * 
 * 
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    // 8ms, 9MB, 98.31%
    vector<vector<int>> fourSum(vector<int> &nums, int target) {
        vector<vector<int>> res;
        int size = nums.size();
        if (size < 4) return res;
        sort(nums.begin(), nums.end());
        for (int i = 0; i < size - 3; ++i) { // 4sum
            for (int j = i + 1; j < size - 2; ++j) { // 3sum
                int lhs = j + 1, rhs = size - 1;
                // check min sum from i
                if (nums[i] + nums[j] + nums[lhs] + nums[lhs + 1] > target) break;
                // check max sum from j
                if (nums[i] + nums[j] + nums[rhs - 1] + nums[rhs] < target) continue;
                while (lhs < rhs) {
                    int sum = nums[i] + nums[j] + nums[lhs] + nums[rhs];
                    if (sum == target) {
                        res.push_back({nums[i], nums[j], nums[lhs], nums[rhs]});
                        while (lhs < rhs && nums[lhs] == nums[lhs + 1]) ++lhs;
                        while (lhs < rhs && nums[rhs] == nums[rhs - 1]) --rhs;
                        ++lhs;
                        --rhs;
                    } else if (sum > target) {
                        while (lhs < rhs && nums[rhs] == nums[rhs - 1]) --rhs;
                        --rhs;
                    } else {
                        while (lhs < rhs && nums[lhs] == nums[lhs + 1]) ++lhs;
                        ++lhs;
                    }
                }
                while (j < size - 2 && nums[j] == nums[j + 1]) ++j;
            }
            while (i < size - 3 && nums[i] == nums[i + 1]) ++i;
        }
        return res;
    }
};
