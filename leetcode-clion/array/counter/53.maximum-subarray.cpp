/*
 * @lc app=leetcode id=53 lang=cpp
 *
 * [53] Maximum Subarray
 *
 * https://leetcode.com/problems/maximum-subarray/description/
 *
 * algorithms
 * Easy (43.46%)
 * Total Accepted:    519.5K
 * Total Submissions: 1.2M
 * Testcase Example:  '[-2,1,-3,4,-1,2,1,-5,4]'
 *
 * Given an integer array nums, find the contiguous subarray (containing at
 * least one number) which has the largest sum and return its sum.
 * 
 * Example:
 * 
 * 
 * Input: [-2,1,-3,4,-1,2,1,-5,4],
 * Output: 6
 * Explanation: [4,-1,2,1] has the largest sum = 6.
 * 
 * 
 * Follow up:
 * 
 * If you have figured out the O(n) solution, try coding another solution using
 * the divide and conquer approach, which is more subtle.
 * 
 */
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxSubArray1(vector<int> &nums) {
        int size = nums.size();
        if (size == 0)
            return 0;
        int sum = nums[0], maxsum = nums[0];
        for (int i = 1; i < size; ++i) {
            if (sum < 0) {
                sum = nums[i];
            } else {
                if (sum + nums[i] >= 0) {
                    sum += nums[i];
                } else {
                    sum = nums[i];
                }
            }
            if (sum > maxsum)
                maxsum = sum;
        }
        return maxsum;
    }

    int maxSubArray2(vector<int> &nums) {
        if (nums.size() == 0)
            return 0;
        int sum = 0;
        int max = nums[0];
        for (int i = 0; i < nums.size(); i++) {
            sum += nums[i];
            if (sum > max) {
                max = sum;
            }
            if (sum <= 0) {
                sum = 0;
            }
        }
        return max;
    }

    int maxSubArray(vector<int> &nums) {
        int size = nums.size();
        if (!size) return 0;
        int res = nums[0];
        for (int i = 1; i < size; ++i) {
            if (nums[i - 1] > 0)
                nums[i] += nums[i - 1];
            res = max(res, nums[i]);
        }
        return res;
    }
};
