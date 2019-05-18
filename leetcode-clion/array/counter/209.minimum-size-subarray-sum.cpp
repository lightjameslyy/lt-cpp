/*
 * @lc app=leetcode id=209 lang=cpp
 *
 * [209] Minimum Size Subarray Sum
 *
 * https://leetcode.com/problems/minimum-size-subarray-sum/description/
 *
 * algorithms
 * Medium (34.77%)
 * Total Accepted:    174.6K
 * Total Submissions: 502.1K
 * Testcase Example:  '7\n[2,3,1,2,4,3]'
 *
 * Given an array of n positive integers and a positive integer s, find the
 * minimal length of a contiguous subarray of which the sum ≥ s. If there isn't
 * one, return 0 instead.
 * 
 * Example: 
 * 
 * 
 * Input: s = 7, nums = [2,3,1,2,4,3]
 * Output: 2
 * Explanation: the subarray [4,3] has the minimal length under the problem
 * constraint.
 * 
 * Follow up:
 * 
 * If you have figured out the O(n) solution, try coding another solution of
 * which the time complexity is O(n log n). 
 * 
 */

/*
 * 思路：two pointers, decreasing sliding window
*/
class Solution {
public:
    int minSubArrayLen(int s, vector<int>& nums) {
        int res = INT_MAX;
        int sum = 0;
        int left = 0, right = 0;
        for (; right < nums.size();) {
            if (right-left+1 >= res) {
                sum -= nums[left++];
                continue;
            }
            sum += nums[right];
            //cout << left << " " << right << " " << sum << endl;
            if (sum >= s) {
                while (sum - nums[left] >= s) {
                    sum -= nums[left++];
                }
                res = min(res, right-left+1);
            }
            right++;
        }
        if (res == INT_MAX)
            return 0;
        return res;
    }
};
