/*
 * @lc app=leetcode id=213 lang=cpp
 *
 * [213] House Robber II
 *
 * https://leetcode.com/problems/house-robber-ii/description/
 *
 * algorithms
 * Medium (35.69%)
 * Total Accepted:    135.4K
 * Total Submissions: 379.4K
 * Testcase Example:  '[2,3,2]'
 *
 * You are a professional robber planning to rob houses along a street. Each
 * house has a certain amount of money stashed. All houses at this place are
 * arranged in a circle. That means the first house is the neighbor of the last
 * one. Meanwhile, adjacent houses have security system connected and it will
 * automatically contact the police if two adjacent houses were broken into on
 * the same night.
 *
 * Given a list of non-negative integers representing the amount of money of
 * each house, determine the maximum amount of money you can rob tonight
 * without alerting the police.
 *
 * Example 1:
 *
 *
 * Input: [2,3,2]
 * Output: 3
 * Explanation: You cannot rob house 1 (money = 2) and then rob house 3 (money
 * = 2),
 * because they are adjacent houses.
 *
 *
 * Example 2:
 *
 *
 * Input: [1,2,3,1]
 * Output: 4
 * Explanation: Rob house 1 (money = 1) and then rob house 3 (money =
 * 3).
 * Total amount you can rob = 1 + 3 = 4.
 *
 */
class Solution {
  public:
    int robRange(vector<int> &nums, int start, int end) {
        int n = nums.size();
        int dp_i1 = 0, dp_i2 = 0;
        int dp_i = 0;
        for (int i = end; i >= start; --i) {
            dp_i = max(dp_i1, nums[i] + dp_i2);
            dp_i2 = dp_i1;
            dp_i1 = dp_i;
        }
        return dp_i;
    }

    int rob(vector<int> &nums) {
        int n = nums.size();
        if (n == 0)
            return 0;
        if (n == 1)
            return nums[0];
        return max(robRange(nums, 0, n - 2), robRange(nums, 1, n - 1));
    }
};
