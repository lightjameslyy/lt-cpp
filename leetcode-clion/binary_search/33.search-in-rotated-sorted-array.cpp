/*
 * @lc app=leetcode id=33 lang=cpp
 *
 * [33] Search in Rotated Sorted Array
 *
 * https://leetcode.com/problems/search-in-rotated-sorted-array/description/
 *
 * algorithms
 * Medium (33.31%)
 * Total Accepted:    506.2K
 * Total Submissions: 1.5M
 * Testcase Example:  '[4,5,6,7,0,1,2]\n0'
 *
 * Suppose an array sorted in ascending order is rotated at some pivot unknown
 * to you beforehand.
 * 
 * (i.e., [0,1,2,4,5,6,7] might become [4,5,6,7,0,1,2]).
 * 
 * You are given a target value to search. If found in the array return its
 * index, otherwise return -1.
 * 
 * You may assume no duplicate exists in the array.
 * 
 * Your algorithm's runtime complexity must be in the order of O(log n).
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [4,5,6,7,0,1,2], target = 0
 * Output: 4
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [4,5,6,7,0,1,2], target = 3
 * Output: -1
 * 
 */
#include <vector>

using namespace std;

class Solution {
public:
    int search(vector<int> &nums, int target) {
        int size = nums.size();
        if (!size) return -1;
        int lhs = 0, rhs = size - 1;
        while (lhs <= rhs) {
            int mid = lhs + (rhs - lhs) / 2;
            if (nums[mid] == target) return mid;
            if (lhs == mid) {
                lhs = mid + 1;
                continue;
            }
            // check the sorted half
            if (nums[lhs] < nums[mid]) {
                if (target == nums[lhs]) return lhs;
                if (target > nums[lhs] && target < nums[mid]) {
                    rhs = mid - 1;
                } else {
                    lhs = mid + 1;
                }
                continue;
            }
            if (nums[mid] < nums[rhs]) {
                if (target == nums[rhs]) return rhs;
                if (target > nums[mid] && target < nums[rhs]) {
                    lhs = mid + 1;
                } else {
                    rhs = mid - 1;
                }
                continue;
            }
        }
        return -1;
    }
};
