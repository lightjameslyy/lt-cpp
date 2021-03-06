/*
 * @lc app=leetcode id=81 lang=cpp
 *
 * [81] Search in Rotated Sorted Array II
 *
 * https://leetcode.com/problems/search-in-rotated-sorted-array-ii/description/
 *
 * algorithms
 * Medium (32.81%)
 * Total Accepted:    195.3K
 * Total Submissions: 595.2K
 * Testcase Example:  '[2,5,6,0,0,1,2]\n0'
 *
 * Suppose an array sorted in ascending order is rotated at some pivot unknown
 * to you beforehand.
 * 
 * (i.e., [0,0,1,2,2,5,6] might become [2,5,6,0,0,1,2]).
 * 
 * You are given a target value to search. If found in the array return true,
 * otherwise return false.
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [2,5,6,0,0,1,2], target = 0
 * Output: true
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [2,5,6,0,0,1,2], target = 3
 * Output: false
 * 
 * Follow up:
 * 
 * 
 * This is a follow up problem to Search in Rotated Sorted Array, where nums
 * may contain duplicates.
 * Would this affect the run-time complexity? How and why?
 * 
 * 
 */
#include <vector>

using namespace std;

class Solution {
public:
    bool search(vector<int> &nums, int target) {
        int size = nums.size();
        int lhs = 0, rhs = size - 1;
        while (lhs <= rhs) {
            int mid = lhs + (rhs - lhs) / 2;
            if (target == nums[mid]) return true;
            if (nums[mid] < nums[rhs]) {    // right half sorted
                if (target > nums[mid] && target <= nums[rhs])
                    lhs = mid + 1;
                else
                    rhs = mid - 1;
            } else if (nums[mid] > nums[rhs]) { // left half sorted
                if (target >= nums[lhs] && target <= nums[mid])
                    rhs = mid - 1;
                else
                    lhs = mid + 1;
            } else  // skip duplicates at rhs
                --rhs;
        }
        return false;
    }
};
