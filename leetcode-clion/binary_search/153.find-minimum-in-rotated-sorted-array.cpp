/*
 * @lc app=leetcode id=153 lang=cpp
 *
 * [153] Find Minimum in Rotated Sorted Array
 *
 * https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/description/
 *
 * algorithms
 * Medium (43.79%)
 * Total Accepted:    336.6K
 * Total Submissions: 768.5K
 * Testcase Example:  '[3,4,5,1,2]'
 *
 * Suppose an array sorted in ascending order is rotated at some pivot unknown
 * to you beforehand.
 * 
 * (i.e.,  [0,1,2,4,5,6,7] might become  [4,5,6,7,0,1,2]).
 * 
 * Find the minimum element.
 * 
 * You may assume no duplicate exists in the array.
 * 
 * Example 1:
 * 
 * 
 * Input: [3,4,5,1,2] 
 * Output: 1
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: [4,5,6,7,0,1,2]
 * Output: 0
 * 
 * 
 */
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

class Solution {
public:
    int findMin(vector<int> &nums) {
        int res = INT_MAX;
        int size = nums.size();
        if (!size) return 0;
        int lhs = 0, rhs = size - 1;
        while (lhs <= rhs) {
            int mid = lhs + (rhs - lhs) / 2;
            if (nums[mid] < nums[rhs]) {    // right half sorted
                res = min(res, nums[mid]);
                rhs = mid - 1;
            } else {    // left half sorted
                res = min(res, nums[lhs]);
                lhs = mid + 1;
            }
        }
        return res;
    }
};
