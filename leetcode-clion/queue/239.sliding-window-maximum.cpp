/*
 * @lc app=leetcode id=239 lang=cpp
 *
 * [239] Sliding Window Maximum
 *
 * https://leetcode.com/problems/sliding-window-maximum/description/
 *
 * algorithms
 * Hard (39.80%)
 * Total Accepted:    195.9K
 * Total Submissions: 492.2K
 * Testcase Example:  '[1,3,-1,-3,5,3,6,7]\n3'
 *
 * Given an array nums, there is a sliding window of size k which is moving
 * from the very left of the array to the very right. You can only see the k
 * numbers in the window. Each time the sliding window moves right by one
 * position. Return the max sliding window.
 *
 * Example:
 *
 *
 * Input: nums = [1,3,-1,-3,5,3,6,7], and k = 3
 * Output: [3,3,5,5,6,7]
 * Explanation:
 *
 * Window position                Max
 * ---------------               -----
 * [1  3  -1] -3  5  3  6  7       3
 * ⁠1 [3  -1  -3] 5  3  6  7       3
 * ⁠1  3 [-1  -3  5] 3  6  7       5
 * ⁠1  3  -1 [-3  5  3] 6  7       5
 * ⁠1  3  -1  -3 [5  3  6] 7       6
 * ⁠1  3  -1  -3  5 [3  6  7]      7
 *
 *
 * Note:
 * You may assume k is always valid, 1 ≤ k ≤ input array's size for non-empty
 * array.
 *
 * Follow up:
 * Could you solve it in linear time?
 */

#include <vector>
#include <deque>

using namespace std;

// monotonic queue in descending order
class MonotonicQueue {
  private:
    deque<int> data;

  public:
    void push(int n) {
        while (!data.empty() && data.back() < n)
            data.pop_back();
        data.push_back(n);
    }

    void pop(int n) {
        if (!data.empty() && data.front() == n)
            data.pop_front();
    }

    int max() {
        return data.front();
    }
};

class Solution {
  public:
    vector<int> maxSlidingWindow(vector<int> &nums, int k) {
        MonotonicQueue window;
        vector<int> res;
        for (int i = 0; i < nums.size(); ++i) {
            if (i < k - 1) {    // initialize sliding window
                window.push(nums[i]);
            } else {
                window.push(nums[i]);
                res.push_back(window.max());
                window.pop(nums[i - k + 1]);    // delete expired data
            }
        }
        return res;
    }
};
