/*
 * @lc app=leetcode id=352 lang=cpp
 *
 * [352] Data Stream as Disjoint Intervals
 *
 * https://leetcode.com/problems/data-stream-as-disjoint-intervals/description/
 *
 * algorithms
 * Hard (43.33%)
 * Total Accepted:    23.6K
 * Total Submissions: 54.4K
 * Testcase Example:  '["SummaryRanges","addNum","getIntervals","addNum","getIntervals","addNum","getIntervals","addNum","getIntervals","addNum","getIntervals"]\n[[],[1],[],[3],[],[7],[],[2],[],[6],[]]'
 *
 * Given a data stream input of non-negative integers a1, a2, ..., an, ...,
 * summarize the numbers seen so far as a list of disjoint intervals.
 *
 * For example, suppose the integers from the data stream are 1, 3, 7, 2, 6,
 * ..., then the summary will be:
 *
 *
 * [1, 1]
 * [1, 1], [3, 3]
 * [1, 1], [3, 3], [7, 7]
 * [1, 3], [7, 7]
 * [1, 3], [6, 7]
 *
 *
 * Follow up:
 * What if there are lots of merges and the number of disjoint intervals are
 * small compared to the data stream's size?
 *
 * NOTE: input types have been changed on April 15, 2019. Please reset to
 * default code definition to get new method signature.
 *
 */

#include <map>
#include <vector>
#include <iostream>

using namespace std;

class SummaryRanges {
  public:
    map<int, int> intervals;
    /** Initialize your data structure here. */
    SummaryRanges() {
        intervals.clear();
    }

    void addNum(int val) {
        // 0. intervals is empty
        if (intervals.empty()) {
            intervals[val] = val;
            return;
        }

        // 1. find the first interval[i, j] thar i > val
        auto pos = intervals.upper_bound(val);

        // 2. insert and merge
        if (pos == intervals.begin()) {
            if (val+1 == pos->first) {
                intervals[val] = pos->second;
                intervals.erase(pos);
            } else
                intervals[val] = val;
        } else if (pos == intervals.end()) {
            pos--;
            int left = pos->second;
            if (left < val-1) {
                intervals[val] = val;
            } else {
                pos->second = left > val ? left : val;
            }
        } else {
            auto prev = --pos;
            pos++;
            int left = prev->second;
            int right = pos->first;
            if (left >= val-1) {
                prev->second = left > val ? left : val;
                if (prev->second == pos->first-1) {
                    prev->second = pos->second;
                    intervals.erase(pos);
                }
            } else if (val+1 == right)  {
                intervals[val] = pos->second;
                intervals.erase(pos);
            } else 
                intervals[val] = val;
        }
    }

    vector<vector<int>> getIntervals() {
        vector<vector<int>> res;
        for (auto interval : intervals) {
            res.push_back({interval.first, interval.second});
        }
        return res;
    }
};

/**
 * Your SummaryRanges object will be instantiated and called as such:
 * SummaryRanges* obj = new SummaryRanges();
 * obj->addNum(val);
 * vector<vector<int>> param_2 = obj->getIntervals();
 */
