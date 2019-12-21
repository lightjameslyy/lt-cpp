/*
 * @lc app=leetcode id=215 lang=cpp
 *
 * [215] Kth Largest Element in an Array
 *
 * https://leetcode.com/problems/kth-largest-element-in-an-array/description/
 *
 * algorithms
 * Medium (50.57%)
 * Total Accepted:    461K
 * Total Submissions: 911.7K
 * Testcase Example:  '[3,2,1,5,6,4]\n2'
 *
 * Find the kth largest element in an unsorted array. Note that it is the kth
 * largest element in the sorted order, not the kth distinct element.
 * 
 * Example 1:
 * 
 * 
 * Input: [3,2,1,5,6,4] and k = 2
 * Output: 5
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: [3,2,3,1,2,4,5,5,6] and k = 4
 * Output: 4
 * 
 * Note: 
 * You may assume k is always valid, 1 ≤ k ≤ array's length.
 * 
 */
#include <queue>
#include <cstdlib>
#include <ctime>

using namespace std;

class Solution {
public:
    // using heap
    int findKthLargest1(vector<int> &nums, int k) {
        priority_queue<int, vector<int>, greater<int>> heap;
        for (int i = 0; i < k; ++i)
            heap.push(nums[i]);
        for (int i = k; i < nums.size(); ++i) {
            if (nums[i] > heap.top()) {
                heap.pop();
                heap.push(nums[i]);
            }
        }
        return heap.top();
    }

    int partition(vector<int> &nums, int lhs, int rhs) {
        int pivot = lhs + rand() % (rhs - lhs + 1);
        swap(nums[lhs], nums[pivot]);
        // slow: the last num < pivot
        int slow = lhs, fast = lhs + 1;
        pivot = nums[lhs];
        for (; fast <= rhs; ++fast) {
            if (nums[fast] < pivot) {
                slow++;
                if (fast > slow)
                    swap(nums[slow], nums[fast]);
            }
        }
        swap(nums[lhs], nums[slow]);
        return slow;
    }

    int helper(vector<int> &nums, int k, int lhs, int rhs) {
        int pos = partition(nums, lhs, rhs);
        if (k == nums.size() - pos)
            return nums[pos];
        else if (k < nums.size() - pos)   // move to right
            return helper(nums, k, pos + 1, rhs);
        else
            return helper(nums, k, lhs, pos - 1);
    }

    // using partition
    int findKthLargest(vector<int> &nums, int k) {
        return helper(nums, k, 0, nums.size() - 1);
    }
};
