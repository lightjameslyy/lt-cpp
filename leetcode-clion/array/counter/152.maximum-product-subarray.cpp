/*
 * @lc app=leetcode id=152 lang=cpp
 *
 * [152] Maximum Product Subarray
 *
 * https://leetcode.com/problems/maximum-product-subarray/description/
 *
 * algorithms
 * Medium (29.13%)
 * Total Accepted:    207.3K
 * Total Submissions: 711.5K
 * Testcase Example:  '[2,3,-2,4]'
 *
 * Given an integer array nums, find the contiguous subarray within an array
 * (containing at least one number) which has the largest product.
 * 
 * Example 1:
 * 
 * 
 * Input: [2,3,-2,4]
 * Output: 6
 * Explanation: [2,3] has the largest product 6.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: [-2,0,-1]
 * Output: 0
 * Explanation: The result cannot be 2, because [-2,-1] is not a subarray.
 * 
 */

/*
 * 思路：动态规划
 * 维护maxi[]和mini[]两个数组。
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxProduct(vector<int> &nums) {
        int size = nums.size();
        if (size == 0)
            return 0;
        int res = *max_element(nums.begin(), nums.end());
        vector<long long> maxi(size, 0), mini(size, 0);

        maxi[0] = max(0, nums[0]);
        mini[0] = min(0, nums[0]);

        for (int i = 1; i < size; ++i) {
            maxi[i] = max(max((long long) max(0, nums[i]), maxi[i - 1] * nums[i]), mini[i - 1] * nums[i]);
            mini[i] = min(min((long long) min(0, nums[i]), maxi[i - 1] * nums[i]), mini[i - 1] * nums[i]);
            if (maxi[i] > res)
                res = maxi[i];
        }
        return res;
    }
};


