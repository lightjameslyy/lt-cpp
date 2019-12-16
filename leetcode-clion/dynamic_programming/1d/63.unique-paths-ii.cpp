/*
 * @lc app=leetcode id=63 lang=cpp
 *
 * [63] Unique Paths II
 *
 * https://leetcode.com/problems/unique-paths-ii/description/
 *
 * algorithms
 * Medium (33.75%)
 * Total Accepted:    234.3K
 * Total Submissions: 694.1K
 * Testcase Example:  '[[0,0,0],[0,1,0],[0,0,0]]'
 *
 * A robot is located at the top-left corner of a m x n grid (marked 'Start' in
 * the diagram below).
 * 
 * The robot can only move either down or right at any point in time. The robot
 * is trying to reach the bottom-right corner of the grid (marked 'Finish' in
 * the diagram below).
 * 
 * Now consider if some obstacles are added to the grids. How many unique paths
 * would there be?
 * 
 * 
 * 
 * An obstacle and empty space is marked as 1 and 0 respectively in the grid.
 * 
 * Note: m and n will be at most 100.
 * 
 * Example 1:
 * 
 * 
 * Input:
 * [
 * [0,0,0],
 * [0,1,0],
 * [0,0,0]
 * ]
 * Output: 2
 * Explanation:
 * There is one obstacle in the middle of the 3x3 grid above.
 * There are two ways to reach the bottom-right corner:
 * 1. Right -> Right -> Down -> Down
 * 2. Down -> Down -> Right -> Right
 * 
 * 
 */
#include <vector>

using namespace std;

class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>> &obstacleGrid) {
        int rows = obstacleGrid.size();
        if (!rows) return 0;
        int cols = obstacleGrid[0].size();
        if (!cols) return 0;
        vector<long long> dp(cols, 1);
        for (int i = 0; i < cols; ++i)
            if (obstacleGrid[0][i]) {
                for (int j = i; j < cols; ++j) {
                    dp[j] = 0;
                }
                break;
            }
        for (int i = 1; i < rows; ++i) {
            if (obstacleGrid[i][0]) dp[0] = 0;
            for (int j = 1; j < cols; ++j) {
                dp[j] = (obstacleGrid[i][j] ? 0 : dp[j - 1] + dp[j]);
            }
        }
        return dp.back();
    }
};
