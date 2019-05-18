/*
 * @lc app=leetcode id=228 lang=cpp
 *
 * [228] Summary Ranges
 *
 * https://leetcode.com/problems/summary-ranges/description/
 *
 * algorithms
 * Medium (35.83%)
 * Total Accepted:    130.3K
 * Total Submissions: 363.7K
 * Testcase Example:  '[0,1,2,4,5,7]'
 *
 * Given a sorted integer array without duplicates, return the summary of its
 * ranges.
 * 
 * Example 1:
 * 
 * 
 * Input:  [0,1,2,4,5,7]
 * Output: ["0->2","4->5","7"]
 * Explanation: 0,1,2 form a continuous range; 4,5 form a continuous range.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input:  [0,2,3,4,6,8,9]
 * Output: ["0","2->4","6","8->9"]
 * Explanation: 2,3,4 form a continuous range; 8,9 form a continuous range.
 * 
 * 
 */

#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    vector<string> summaryRanges(vector<int> &nums) {
        int size = nums.size();
        vector<string> res;
        if (size == 0)
            return res;

        int prev = nums[0];
        int left = nums[0];
        for (int i = 1; i < size; ++i) {
            int cur = nums[i];
            if (prev + 1 != cur) {
                if (left == prev) {
                    res.push_back(to_string(left));
                } else {
                    res.push_back(to_string(left) + "->" + to_string(prev));
                }
                left = cur;
            }
            prev = cur;
        }
        if (left == prev) {
            res.push_back(to_string(left));
        } else {
            res.push_back(to_string(left) + "->" + to_string(prev));
        }

        return res;
    }
};
