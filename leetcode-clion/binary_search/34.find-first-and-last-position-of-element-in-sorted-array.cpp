/*
 * @lc app=leetcode id=34 lang=cpp
 *
 * [34] Find First and Last Position of Element in Sorted Array
 *
 * https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/description/
 *
 * algorithms
 * Medium (34.47%)
 * Total Accepted:    369.9K
 * Total Submissions: 1.1M
 * Testcase Example:  '[5,7,7,8,8,10]\n8'
 *
 * Given an array of integers nums sorted in ascending order, find the starting
 * and ending position of a given target value.
 * 
 * Your algorithm's runtime complexity must be in the order of O(log n).
 * 
 * If the target is not found in the array, return [-1, -1].
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [5,7,7,8,8,10], target = 8
 * Output: [3,4]
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [5,7,7,8,8,10], target = 6
 * Output: [-1,-1]
 * 
 */
#include <vector>

using namespace std;

class Solution {
public:
    int lower(vector<int> &nums, int target, int lhs, int rhs) {
        while (lhs < rhs) {
            int mid = lhs + (rhs - lhs) / 2;
            if (nums[mid] == target) {
                rhs = mid;
            } else {
                lhs = mid + 1;
            }
        }
        return lhs;
    }

    int upper(vector<int> &nums, int target, int lhs, int rhs) {
        while (lhs < rhs) {
            int mid = lhs + (rhs - lhs + 1) / 2;
            if (nums[mid] == target) {
                lhs = mid;
            } else
                rhs = mid - 1;
        }
        return rhs;
    }

    vector<int> searchRange(vector<int> &nums, int target) {
        vector<int> res = {-1, -1};
        int lhs = 0, rhs = nums.size() - 1;
        while (lhs <= rhs) {
            int mid = lhs + (rhs - lhs) / 2;
            if (nums[mid] == target) {
                // find lower pos
                res[0] = lower(nums, target, lhs, mid);
                // find upper pos
                res[1] = upper(nums, target, mid, rhs);
                break;
            } else if (nums[mid] > target) {
                rhs = mid - 1;
            } else
                lhs = mid + 1;
        }
        return res;
    }
};
