/*
 * @lc app=leetcode id=252 lang=cpp
 *
 * [252] Meeting Rooms
 *
 * https://leetcode.com/problems/meeting-rooms/description/
 *
 * algorithms
 * Easy (53.24%)
 * Total Accepted:    103.2K
 * Total Submissions: 193.9K
 * Testcase Example:  '[[0,30],[5,10],[15,20]]'
 *
 * Given an array of meeting time intervals consisting of start and end times
 * [[s1,e1],[s2,e2],...] (si < ei), determine if a person could attend all
 * meetings.
 * 
 * Example 1:
 * 
 * 
 * Input: [[0,30],[5,10],[15,20]]
 * Output: false
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: [[7,10],[2,4]]
 * Output: true
 * 
 * 
 * NOTE: input types have been changed on April 15, 2019. Please reset to
 * default code definition to get new method signature.
 * 
 */
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    bool canAttendMeetings(vector<vector<int>> &intervals) {
        int size = intervals.size();
        if (size < 2) return true;
        sort(intervals.begin(), intervals.end(),
             [](const vector<int> &a, const vector<int> &b) { return a[0] < b[0]; });
        for (int i = 1; i < size; ++i) {
            if (intervals[i][0] < intervals[i - 1][1])
                return false;
        }
        return true;
    }
};
