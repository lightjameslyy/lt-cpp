/*
 * @lc app=leetcode id=16 lang=cpp
 *
 * [16] 3Sum Closest
 *
 * https://leetcode.com/problems/3sum-closest/description/
 *
 * algorithms
 * Medium (45.72%)
 * Total Accepted:    393.3K
 * Total Submissions: 860.4K
 * Testcase Example:  '[-1,2,1,-4]\n1'
 *
 * Given an array nums of n integers and an integer target, find three integers
 * in nums such that the sum is closest to target. Return the sum of the three
 * integers. You may assume that each input would have exactly one solution.
 * 
 * Example:
 * 
 * 
 * Given array nums = [-1, 2, 1, -4], and target = 1.
 * 
 * The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).
 * 
 * 
 */

#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    void twoSum(vector<int> &nums, int pos, int num, int target, long long &res) {
        if (res == target) return;
        int left = pos, right = nums.size() - 1;
        while (left < right) {
            long long sum = nums[left] + nums[right] + num;
            long long curSub = sum - target;
            long long globalSub = res - target;
            if (abs(curSub) < abs(globalSub))
                res = sum;
            if (curSub == 0) return;
            if (curSub > 0) {
                while (left < right && nums[right] == nums[right - 1]) --right;
                --right;
            } else {
                while (left < right && nums[left] == nums[left + 1]) ++left;
                ++left;
            }
        }
    }

    // 8ms, 8.8MB, 81.01%
    int threeSumClosest(vector<int> &nums, int target) {
        long long res = 1LL << 33;
        if (nums.size() < 3) return res;
        sort(nums.begin(), nums.end());
        for (int i = 0; i < nums.size() - 2; ++i) {
            twoSum(nums, i + 1, nums[i], target, res);
            if (res == target)
                return res;
            while (i < nums.size() - 2 && nums[i] == nums[i + 1])
                ++i;
        }
        return res;
    }
};
