/*
 * @lc app=leetcode id=198 lang=cpp
 *
 * [198] House Robber
 *
 * https://leetcode.com/problems/house-robber/description/
 *
 * algorithms
 * Easy (41.41%)
 * Total Accepted:    387.4K
 * Total Submissions: 935.4K
 * Testcase Example:  '[1,2,3,1]'
 *
 * You are a professional robber planning to rob houses along a street. Each
 * house has a certain amount of money stashed, the only constraint stopping
 * you from robbing each of them is that adjacent houses have security system
 * connected and it will automatically contact the police if two adjacent
 * houses were broken into on the same night.
 *
 * Given a list of non-negative integers representing the amount of money of
 * each house, determine the maximum amount of money you can rob tonight
 * without alerting the police.
 *
 * Example 1:
 *
 *
 * Input: [1,2,3,1]
 * Output: 4
 * Explanation: Rob house 1 (money = 1) and then rob house 3 (money =
 * 3).
 * Total amount you can rob = 1 + 3 = 4.
 *
 * Example 2:
 *
 *
 * Input: [2,7,9,3,1]
 * Output: 12
 * Explanation: Rob house 1 (money = 2), rob house 3 (money = 9) and rob house
 * 5 (money = 1).
 * Total amount you can rob = 2 + 9 + 1 = 12.
 *
 *
 */
#include <vector>
#include <algorithm>

using namespace std;

/*
 * state definition:
 *      dp[i]: max money if rob from nums[i]
 * state transmission:
 *      dp[i] = max(
 *              dp[i+1], // don't rob nums[i]
 *              nums[i] + dp[i+2], // rob nums[i]
 *              )
 */

class Solution {
  public:
    int rob(vector<int> &nums) {
        int n = nums.size();
        int dp_i1 = 0, dp_i2 = 0;
        int dp_i = 0;
        for (int i = n - 1; i >= 0; --i) {
            dp_i = max(dp_i1, nums[i] + dp_i2);
            dp_i2 = dp_i1;
            dp_i1 = dp_i;
        }
        return dp_i;
    }
};
