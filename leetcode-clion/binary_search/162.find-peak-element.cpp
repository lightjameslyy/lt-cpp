/*
 * @lc app=leetcode id=162 lang=cpp
 *
 * [162] Find Peak Element
 *
 * https://leetcode.com/problems/find-peak-element/description/
 *
 * algorithms
 * Medium (42.06%)
 * Total Accepted:    279K
 * Total Submissions: 663.4K
 * Testcase Example:  '[1,2,3,1]'
 *
 * A peak element is an element that is greater than its neighbors.
 * 
 * Given an input array nums, where nums[i] ≠ nums[i+1], find a peak element
 * and return its index.
 * 
 * The array may contain multiple peaks, in that case return the index to any
 * one of the peaks is fine.
 * 
 * You may imagine that nums[-1] = nums[n] = -∞.
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [1,2,3,1]
 * Output: 2
 * Explanation: 3 is a peak element and your function should return the index
 * number 2.
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [1,2,1,3,5,6,4]
 * Output: 1 or 5 
 * Explanation: Your function can return either index number 1 where the peak
 * element is 2, 
 * or index number 5 where the peak element is 6.
 * 
 * 
 * Note:
 * 
 * Your solution should be in logarithmic complexity.
 * 
 */

#include <vector>

using namespace std;

class Solution {
public:
    int findPeakElement(vector<int> &nums) {
        int size = nums.size();
        if (1 == size) return 0;
        int lhs = 0, rhs = size - 1;
        while (lhs < rhs) {
            int mid = lhs + (rhs - lhs) / 2;
            if (nums[mid] > nums[mid + 1]) {  // there must be a peak at [0, mid]
                rhs = mid;
            } else  // there must be a peak at [mid+1, size-1]
                lhs = mid + 1;
        }
        return lhs;
    }
};
