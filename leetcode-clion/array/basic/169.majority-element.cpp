/*
 * @lc app=leetcode id=169 lang=cpp
 *
 * [169] Majority Element
 *
 * https://leetcode.com/problems/majority-element/description/
 *
 * algorithms
 * Easy (54.64%)
 * Total Accepted:    454.5K
 * Total Submissions: 831.8K
 * Testcase Example:  '[3,2,3]'
 *
 * Given an array of size n, find the majority element. The majority element is
 * the element that appears more than ⌊ n/2 ⌋ times.
 * 
 * You may assume that the array is non-empty and the majority element always
 * exist in the array.
 * 
 * Example 1:
 * 
 * 
 * Input: [3,2,3]
 * Output: 3
 * 
 * Example 2:
 * 
 * 
 * Input: [2,2,1,1,1,2,2]
 * Output: 2
 * 
 * 
 */
#include <vector>

using namespace std;

class Solution {
public:
    int majorityElement(vector<int> &nums) {
        int count = 1;
        int val = nums[0];
        for (size_t i = 1; i < nums.size(); ++i) {
            if (nums[i] == val)
                count++;
            else {
                count--;
                if (!count) {
                    val = nums[i];
                    count = 1;
                }
            }
        }
        return val;
    }
};
