/*
 * @lc app=leetcode id=259 lang=cpp
 *
 * [259] 3Sum Smaller
 *
 * https://leetcode.com/problems/3sum-smaller/description/
 *
 * algorithms
 * Medium (45.91%)
 * Total Accepted:    56.2K
 * Total Submissions: 122.4K
 * Testcase Example:  '[-2,0,1,3]\n2'
 *
 * Given an array of n integers nums and a target, find the number of index
 * triplets i, j, k with 0 <= i < j < k < n that satisfy the condition nums[i]
 * + nums[j] + nums[k] < target.
 * 
 * Example:
 * 
 * 
 * Input: nums = [-2,0,1,3], and target = 2
 * Output: 2 
 * Explanation: Because there are two triplets which sums are less than
 * 2:
 * [-2,0,1]
 * ⁠            [-2,0,3]
 * 
 * 
 * Follow up: Could you solve it in O(n^2) runtime?
 * 
 */

/*
 * sort + two pointers
 */

#include <algorithm>

using namespace std;

class Solution {
public:
    // 12ms, 8.5MB, 26.92%
    int threeSumSmaller(vector<int> &nums, int target) {
        int size = nums.size();
        if (size < 3) return 0;
        sort(nums.begin(), nums.end());
        int res = 0;
        for (int i = 0; i < size - 2; ++i) {
            int lhs = i + 1, rhs = size - 1;
            while (lhs < rhs) {
                while (lhs < rhs && nums[i] + nums[lhs] + nums[rhs] >= target) --rhs;
                res += (rhs - lhs);
                while (lhs < rhs && nums[lhs] == nums[lhs + 1]) {
                    ++lhs;
                    res += (rhs - lhs);
                }
                ++lhs;
            }
        }
        return res;
    }
};
