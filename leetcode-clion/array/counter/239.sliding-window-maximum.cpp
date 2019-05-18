/*
 * @lc app=leetcode id=239 lang=cpp
 *
 * [239] Sliding Window Maximum
 *
 * https://leetcode.com/problems/sliding-window-maximum/description/
 *
 * algorithms
 * Hard (37.96%)
 * Total Accepted:    154.5K
 * Total Submissions: 407K
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

/*
 * 思路：Monotonic Queue
 * deque
 */
class Solution {
  public:
    deque<pair<int, int>> mono_que; // pair<id, val>

    void push(int id, int val) {
        // pop_back values less than val 
        for (; !mono_que.empty() && mono_que.back().second < val ; mono_que.pop_back());
        mono_que.push_back(make_pair(id, val));
    }

    void pop(int id) {
        // pop the out-dated entry
        if (!mono_que.empty() && mono_que.front().first == id)
            mono_que.pop_front();
    }

    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> res;
        int size = nums.size();
        if (size == 0)
            return res;
        for (int i = 0; i < k; ++i) {
            push(i, nums[i]);
        }
        res.push_back(mono_que.front().second);
        for (int i = k; i < size; ++i) {
            pop(i-k);
            push(i, nums[i]);
            res.push_back(mono_que.front().second);
        }
        return res;
    }
};
