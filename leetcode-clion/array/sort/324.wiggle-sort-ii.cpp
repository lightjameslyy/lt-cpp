/*
 * @lc app=leetcode id=324 lang=cpp
 *
 * [324] Wiggle Sort II
 *
 * https://leetcode.com/problems/wiggle-sort-ii/description/
 *
 * algorithms
 * Medium (27.90%)
 * Total Accepted:    58.7K
 * Total Submissions: 210.5K
 * Testcase Example:  '[1,5,1,1,6,4]'
 *
 * Given an unsorted array nums, reorder it such that nums[0] < nums[1] >
 * nums[2] < nums[3]....
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [1, 5, 1, 1, 6, 4]
 * Output: One possible answer is [1, 4, 1, 5, 1, 6].
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [1, 3, 2, 2, 3, 1]
 * Output: One possible answer is [2, 3, 1, 3, 1, 2].
 * 
 * Note:
 * You may assume all input has valid answer.
 * 
 * Follow Up:
 * Can you do it in O(n) time and/or in-place with O(1) extra space?
 */

/*
 * 思路：sort -> 中位数
 * 0 2 4 ... <= 中位数
 * 1 3 5 ... > 中位数
 *
 * e.g.
 * 1 2 3 4 5
 * 0 1 2 3 4    midpos=2, mid=3
 *
 * 1 2 3 4 5 6
 * 0 1 2 3 4 5  midpos=2, mid=3
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    void wiggleSort1(vector<int> &nums) {
        int size = nums.size();
        if (size < 2) return;
        sort(nums.begin(), nums.end());
        int midpos = (size - 1) / 2;
        int bigpos = size - 1;
        int smallpos = midpos;
        vector<int> tmp(size, 0);
        int j = 0;
        while (smallpos >= 0) {
            tmp[j++] = nums[smallpos--];
            if (bigpos > midpos) {
                tmp[j++] = nums[bigpos--];
            }
        }
        nums = tmp;
    }

    void wiggleSort(vector<int> &nums) {
        int n = nums.size();

        // Find a median.
        auto midptr = nums.begin() + n / 2;
        nth_element(nums.begin(), midptr, nums.end());
        int mid = *midptr;

        // Index-rewiring.
#define A(i) nums[(1+2*(i)) % (n|1)]

        // 3-way-partition-to-wiggly in O(n) time with O(1) space.
        int i = 0, j = 0, k = n - 1;
        while (j <= k) {
            if (A(j) > mid)
                swap(A(i++), A(j++));
            else if (A(j) < mid)
                swap(A(j), A(k--));
            else
                j++;
        }
    }
};
