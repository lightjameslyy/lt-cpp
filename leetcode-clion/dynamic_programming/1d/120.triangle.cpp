/*
 * @lc app=leetcode id=120 lang=cpp
 *
 * [120] Triangle
 *
 * https://leetcode.com/problems/triangle/description/
 *
 * algorithms
 * Medium (41.21%)
 * Total Accepted:    206.3K
 * Total Submissions: 500.6K
 * Testcase Example:  '[[2],[3,4],[6,5,7],[4,1,8,3]]'
 *
 * Given a triangle, find the minimum path sum from top to bottom. Each step
 * you may move to adjacent numbers on the row below.
 * 
 * For example, given the following triangle
 * 
 * 
 * [
 * ⁠    [2],
 * ⁠   [3,4],
 * ⁠  [6,5,7],
 * ⁠ [4,1,8,3]
 * ]
 * 
 * 
 * The minimum path sum from top to bottom is 11 (i.e., 2 + 3 + 5 + 1 = 11).
 * 
 * Note:
 * 
 * Bonus point if you are able to do this using only O(n) extra space, where n
 * is the total number of rows in the triangle.
 * 
 */
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minimumTotal(vector<vector<int>> &triangle) {
        int rows = triangle.size();
        if (!rows) return 0;
        vector<int> dp(rows, 0);
        dp[0] = triangle[0][0];
        for (int row = 1; row < rows; ++row) {
            dp[row] = dp[row - 1] + triangle[row][row];
            for (int col = row - 1; col >= 1; --col) {
                dp[col] = min(dp[col], dp[col - 1]) + triangle[row][col];
            }
            dp[0] += triangle[row][0];
        }
        int res = dp[0];
        for (int val : dp) {
            if (val < res) res = val;
        }
        return res;
    }
};
