/*
 * @lc app=leetcode id=452 lang=cpp
 *
 * [452] Minimum Number of Arrows to Burst Balloons
 *
 * https://leetcode.com/problems/minimum-number-of-arrows-to-burst-balloons/description/
 *
 * algorithms
 * Medium (47.51%)
 * Total Accepted:    46.7K
 * Total Submissions: 98.3K
 * Testcase Example:  '[[10,16],[2,8],[1,6],[7,12]]'
 *
 * There are a number of spherical balloons spread in two-dimensional space.
 * For each balloon, provided input is the start and end coordinates of the
 * horizontal diameter. Since it's horizontal, y-coordinates don't matter and
 * hence the x-coordinates of start and end of the diameter suffice. Start is
 * always smaller than end. There will be at most 10^4 balloons.
 *
 * An arrow can be shot up exactly vertically from different points along the
 * x-axis. A balloon with xstart and xend bursts by an arrow shot at x if
 * xstart ≤ x ≤ xend. There is no limit to the number of arrows that can be
 * shot. An arrow once shot keeps travelling up infinitely. The problem is to
 * find the minimum number of arrows that must be shot to burst all balloons.
 *
 * Example:
 *
 *
 * Input:
 * [[10,16], [2,8], [1,6], [7,12]]
 *
 * Output:
 * 2
 *
 * Explanation:
 * One way is to shoot one arrow for example at x = 6 (bursting the balloons
 * [2,8] and [1,6]) and another arrow at x = 11 (bursting the other two
 * balloons).
 *
 *
 *
 *
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
  public:
    int findMinArrowShots(vector<vector<int>> &points) {
        if (points.empty())
            return 0;
        // a interval: [start, end]
        // sort by end
        sort(points.begin(), points.end(), [&](const vector<int> &intv1, const vector<int> &intv2) {
            return intv1[1] < intv2[1];
        });
        // count: max number of non-overlapping points
        int count = 1;
        int min_end = points[0][1];
        for (auto &intv : points) {
            int start = intv[0];
            if (start > min_end) {
                ++count;
                min_end = intv[1];
            }
        }
        return count;
    }
};
