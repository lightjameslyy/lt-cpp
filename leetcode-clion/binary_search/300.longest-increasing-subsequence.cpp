/*
 * @lc app=leetcode id=300 lang=cpp
 *
 * [300] Longest Increasing Subsequence
 *
 * https://leetcode.com/problems/longest-increasing-subsequence/description/
 *
 * algorithms
 * Medium (41.60%)
 * Total Accepted:    276K
 * Total Submissions: 663.6K
 * Testcase Example:  '[10,9,2,5,3,7,101,18]'
 *
 * Given an unsorted array of integers, find the length of longest increasing
 * subsequence.
 * 
 * Example:
 * 
 * 
 * Input: [10,9,2,5,3,7,101,18]
 * Output: 4 
 * Explanation: The longest increasing subsequence is [2,3,7,101], therefore
 * the length is 4. 
 * 
 * Note: 
 * 
 * 
 * There may be more than one LIS combination, it is only necessary for you to
 * return the length.
 * Your algorithm should run in O(n^2) complexity.
 * 
 * 
 * Follow up: Could you improve it to O(n log n) time complexity?
 * 
 */
#include <vector>

using namespace std;

class Solution {
public:
    int lengthOfLIS(vector<int> &nums) {
        if (nums.size() < 2) return nums.size();
        int res = 1;
        vector<int> dp(nums.size(), 1);
        for (int i = 1; i < nums.size(); ++i) {
            int tmp = 0;
            for (int j = 0; j < i; ++j) {
                if (nums[j] < nums[i])
                    tmp = max(tmp, dp[j]);
            }
            dp[i] = tmp + 1;
            res = max(res, dp[i]);
        }
        return res;
    }
};
