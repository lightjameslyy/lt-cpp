/*
 * @lc app=leetcode id=256 lang=cpp
 *
 * [256] Paint House
 *
 * https://leetcode.com/problems/paint-house/description/
 *
 * algorithms
 * Easy (50.38%)
 * Total Accepted:    65.2K
 * Total Submissions: 129.5K
 * Testcase Example:  '[[17,2,17],[16,16,5],[14,3,19]]'
 *
 * There are a row of n houses, each house can be painted with one of the three
 * colors: red, blue or green. The cost of painting each house with a certain
 * color is different. You have to paint all the houses such that no two
 * adjacent houses have the same color.
 * 
 * The cost of painting each house with a certain color is represented by a n x
 * 3 cost matrix. For example, costs[0][0] is the cost of painting house 0 with
 * color red; costs[1][2] is the cost of painting house 1 with color green, and
 * so on... Find the minimum cost to paint all houses.
 * 
 * Note:
 * All costs are positive integers.
 * 
 * Example:
 * 
 * 
 * Input: [[17,2,17],[16,16,5],[14,3,19]]
 * Output: 10
 * Explanation: Paint house 0 into blue, paint house 1 into green, paint house
 * 2 into blue. 
 * Minimum cost: 2 + 5 + 3 = 10.
 * 
 * 
 */
#include <vector>
#include <climits>

using namespace std;

class Solution {
public:
    int minCost(vector<vector<int>> &costs) {
        int rows = costs.size();
        if (!rows) return 0;
        vector<vector<int>> dp(rows, vector<int>(3));
        dp[0] = costs[0];
        for (int i = 1; i < rows; ++i) {
            for (int j = 0; j < 3; ++j) {
                int preMin;
                if (j == 0)
                    preMin = min(dp[i - 1][1], dp[i - 1][2]);
                else if (j == 1)
                    preMin = min(dp[i - 1][0], dp[i - 1][2]);
                else
                    preMin = min(dp[i - 1][0], dp[i - 1][1]);
                dp[i][j] = costs[i][j] + preMin;
            }
        }
        int res = INT_MAX;
        for (int val : dp.back())
            if (val < res)
                res = val;
        return res;
    }
};
