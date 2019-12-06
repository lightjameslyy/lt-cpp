/*
 * @lc app=leetcode id=15 lang=cpp
 *
 * [15] 3Sum
 *
 * https://leetcode.com/problems/3sum/description/
 *
 * algorithms
 * Medium (25.08%)
 * Total Accepted:    684.3K
 * Total Submissions: 2.7M
 * Testcase Example:  '[-1,0,1,2,-1,-4]'
 *
 * Given an array nums of n integers, are there elements a, b, c in nums such
 * that a + b + c = 0? Find all unique triplets in the array which gives the
 * sum of zero.
 * 
 * Note:
 * 
 * The solution set must not contain duplicate triplets.
 * 
 * Example:
 * 
 * 
 * Given array nums = [-1, 0, 1, 2, -1, -4],
 * 
 * A solution set is:
 * [
 * ⁠ [-1, 0, 1],
 * ⁠ [-1, -1, 2]
 * ]
 * 
 */

#include <algorithm>

using namespace std;

class Solution {
public:
    void twoSum(vector<int> &nums, int pos, int target, vector<vector<int>> &res) {
        int left = pos, right = nums.size() - 1;
        while (left < right) {
            int sum = nums[left] + nums[right];
            if (sum == target) {
                res.push_back({-target, nums[left], nums[right]});
                while (left < right && nums[left] == nums[left + 1]) ++left;
                while (left < right && nums[right] == nums[right - 1]) --right;
                ++left;
                --right;
            } else if (sum > target) {
                while (left < right && nums[right] == nums[right - 1]) --right;
                --right;
            } else {
                while (left < right && nums[left] == nums[left + 1]) ++left;
                ++left;
            }
        }
    }

    // 104ms, 14.5MB, 59.32%
    vector<vector<int>> threeSum(vector<int> &nums) {
        vector<vector<int>> res;
        if (nums.size() < 3) return res;
        sort(nums.begin(), nums.end());
        for (int i = 0; i < nums.size() - 2; ++i) {
            if (nums[i] > 0) break;
            twoSum(nums, i + 1, -nums[i], res);
            while (i < nums.size() - 2 && nums[i] == nums[i + 1])
                ++i;
        }
        return res;
    }
};
