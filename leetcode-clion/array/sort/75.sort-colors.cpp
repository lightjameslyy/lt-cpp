/*
 * @lc app=leetcode id=75 lang=cpp
 *
 * [75] Sort Colors
 *
 * https://leetcode.com/problems/sort-colors/description/
 *
 * algorithms
 * Medium (42.07%)
 * Total Accepted:    314.8K
 * Total Submissions: 748.2K
 * Testcase Example:  '[2,0,2,1,1,0]'
 *
 * Given an array with n objects colored red, white or blue, sort them in-place
 * so that objects of the same color are adjacent, with the colors in the order
 * red, white and blue.
 * 
 * Here, we will use the integers 0, 1, and 2 to represent the color red,
 * white, and blue respectively.
 * 
 * Note: You are not suppose to use the library's sort function for this
 * problem.
 * 
 * Example:
 * 
 * 
 * Input: [2,0,2,1,1,0]
 * Output: [0,0,1,1,2,2]
 * 
 * Follow up:
 * 
 * 
 * A rather straight forward solution is a two-pass algorithm using counting
 * sort.
 * First, iterate the array counting number of 0's, 1's, and 2's, then
 * overwrite array with total number of 0's, then 1's and followed by 2's.
 * Could you come up with a one-pass algorithm using only constant space?
 * 
 * 
 */

/*
 * 思路： two pointers
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    void sortColors(vector<int> &nums) {
        int size = nums.size();
        if (size < 2)
            return;
        int next_0_pos = 0, next_2_pos = size - 1;
        for (int i = 0; i < size;) {
            while (next_0_pos < size && nums[next_0_pos] == 0) {
                next_0_pos++;
            }
            if (next_0_pos >= size)
                return;
            i = max(i, next_0_pos);
            while (next_2_pos >= 0 && nums[next_2_pos] == 2) {
                next_2_pos--;
            }
            if (next_2_pos < 0 || i > next_2_pos)
                return;
            if (nums[i] == 0) {
                if (i > next_0_pos)
                    swap(nums[next_0_pos], nums[i]);
                else {
                    ++i;
                }
                ++next_0_pos;
            } else if (nums[i] == 2) {
                swap(nums[next_2_pos--], nums[i]);
            } else {
                ++i;
            }
        }
    }
};
