/*
 * @lc app=leetcode id=283 lang=cpp
 *
 * [283] Move Zeroes
 *
 * https://leetcode.com/problems/move-zeroes/description/
 *
 * algorithms
 * Easy (54.23%)
 * Total Accepted:    460.5K
 * Total Submissions: 849.2K
 * Testcase Example:  '[0,1,0,3,12]'
 *
 * Given an array nums, write a function to move all 0's to the end of it while
 * maintaining the relative order of the non-zero elements.
 * 
 * Example:
 * 
 * 
 * Input: [0,1,0,3,12]
 * Output: [1,3,12,0,0]
 * 
 * Note:
 * 
 * 
 * You must do this in-place without making a copy of the array.
 * Minimize the total number of operations.
 * 
 */

#include <vector>

using namespace std;

class Solution {
public:
    void moveZeroes(vector<int> &nums) {
        int size = nums.size();
        if (size < 2) return;
        int pos = 0;
        for (int i = 0; i < size; ++i) {
            if (nums[i] != 0)
                nums[pos++] = nums[i];
        }
        for (; pos < size; pos++) {
            nums[pos] = 0;
        }
    }
};
