/*
 * @lc app=leetcode id=238 lang=cpp
 *
 * [238] Product of Array Except Self
 *
 * https://leetcode.com/problems/product-of-array-except-self/description/
 *
 * algorithms
 * Medium (54.83%)
 * Total Accepted:    252.4K
 * Total Submissions: 460.3K
 * Testcase Example:  '[1,2,3,4]'
 *
 * Given an array nums of n integers where n > 1,  return an array output such
 * that output[i] is equal to the product of all the elements of nums except
 * nums[i].
 * 
 * Example:
 * 
 * 
 * Input:  [1,2,3,4]
 * Output: [24,12,8,6]
 * 
 * 
 * Note: Please solve it without division and in O(n).
 * 
 * Follow up:
 * Could you solve it with constant space complexity? (The output array does
 * not count as extra space for the purpose of space complexity analysis.)
 * 
 */

/*
 * 思路：双向计算
 * 对每个res[i]，先算nums[0]*nums[1]*...*nums[i-1]，再算nums[i+1]*nums[i+2]*...*nums[size-1]
 */
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int size = nums.size();
        vector<int> res(size, 1);

        int tmp = 1;
        // left side
        for (int i = 1; i < size; ++i) {
            tmp *= nums[i-1];
            res[i] = tmp;
        }

        tmp = 1;
        // right side
        for (int i = size-2; i >= 0; --i) {
            tmp *= nums[i+1];
            res[i] *= tmp;
        }

        return res;
    }
};
