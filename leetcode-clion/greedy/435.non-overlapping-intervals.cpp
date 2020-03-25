/*
 * @lc app=leetcode id=435 lang=cpp
 *
 * [435] Non-overlapping Intervals
 *
 * https://leetcode.com/problems/non-overlapping-intervals/description/
 *
 * algorithms
 * Medium (41.84%)
 * Total Accepted:    49.8K
 * Total Submissions: 118.9K
 * Testcase Example:  '[[1,2]]'
 *
 * Given a collection of intervals, find the minimum number of intervals you
 * need to remove to make the rest of the intervals non-overlapping.
 *
 *
 *
 *
 *
 *
 * Example 1:
 *
 *
 * Input: [[1,2],[2,3],[3,4],[1,3]]
 * Output: 1
 * Explanation: [1,3] can be removed and the rest of intervals are
 * non-overlapping.
 *
 *
 * Example 2:
 *
 *
 * Input: [[1,2],[1,2],[1,2]]
 * Output: 2
 * Explanation: You need to remove two [1,2] to make the rest of intervals
 * non-overlapping.
 *
 *
 * Example 3:
 *
 *
 * Input: [[1,2],[2,3]]
 * Output: 0
 * Explanation: You don't need to remove any of the intervals since they're
 * already non-overlapping.
 *
 *
 *
 *
 * Note:
 *
 *
 * You may assume the interval's end point is always bigger than its start
 * point.
 * Intervals like [1,2] and [2,3] have borders "touching" but they don't
 * overlap each other.
 *
 *
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
  public:
    int eraseOverlapIntervals(vector<vector<int>> &intervals) {
        if (intervals.empty())
            return 0;
        // a interval: [start, end]
        // sort by end
        sort(intervals.begin(), intervals.end(), [&](const vector<int> &intv1, const vector<int> &intv2) {
            return intv1[1] < intv2[1];
        });
        // count: max number of non-overlapping intervals
        int count = 1;
        int min_end = intervals[0][1];
        for (auto &intv : intervals) {
            int start = intv[0];
            if (start >= min_end) {
                ++count;
                min_end = intv[1];
            }
        }
        return intervals.size() - count;
    }
};
