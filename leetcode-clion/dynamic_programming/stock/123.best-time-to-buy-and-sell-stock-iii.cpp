/*
 * @lc app=leetcode id=123 lang=cpp
 *
 * [123] Best Time to Buy and Sell Stock III
 *
 * https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/description/
 *
 * algorithms
 * Hard (35.20%)
 * Total Accepted:    173.1K
 * Total Submissions: 491.6K
 * Testcase Example:  '[3,3,5,0,0,3,1,4]'
 *
 * Say you have an array for which the i^th element is the price of a given
 * stock on day i.
 *
 * Design an algorithm to find the maximum profit. You may complete at most two
 * transactions.
 *
 * Note: You may not engage in multiple transactions at the same time (i.e.,
 * you must sell the stock before you buy again).
 *
 * Example 1:
 *
 *
 * Input: [3,3,5,0,0,3,1,4]
 * Output: 6
 * Explanation: Buy on day 4 (price = 0) and sell on day 6 (price = 3), profit
 * = 3-0 = 3.
 * Then buy on day 7 (price = 1) and sell on day 8 (price = 4), profit = 4-1 =
 * 3.
 *
 * Example 2:
 *
 *
 * Input: [1,2,3,4,5]
 * Output: 4
 * Explanation: Buy on day 1 (price = 1) and sell on day 5 (price = 5), profit
 * = 5-1 = 4.
 * Note that you cannot buy on day 1, buy on day 2 and sell them later, as you
 * are
 * engaging multiple transactions at the same time. You must sell before buying
 * again.
 *
 *
 * Example 3:
 *
 *
 * Input: [7,6,4,3,1]
 * Output: 0
 * Explanation: In this case, no transaction is done, i.e. max profit = 0.
 *
 */
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

/*
 * using 3D dp
 * dp[n][k][0/1]
 * state transmisson (k-1 at buy):
 *      dp[i][k][0] = max(dp[i-1][k][0], dp[i-1][k][1] + prices[i])
 *      dp[i][k][1] = max(dp[i-1][k][1], dp[i-1][k-1][0] - prices[i])
 * enumeration for k=1,2
 *      dp[i][2][0] = max(dp[i-1][2][0], dp[i-1][2][1] + prices[i])
 *      dp[i][2][1] = max(dp[i-1][2][1], dp[i-1][1][0] - prices[i])
 *      dp[i][1][0] = max(dp[i-1][1][0], dp[i-1][1][1] + prices[i])
 *      dp[i][1][1] = max(dp[i-1][1][1], - prices[i])
 */

class Solution {
  public:
    int maxProfit(vector<int> &prices) {
        int dp_i10 = 0, dp_i11 = INT_MIN;
        int dp_i20 = 0, dp_i21 = INT_MIN;
        for (int price : prices) {
            // update k=2
            dp_i20 = max(dp_i20, dp_i21 + price);
            dp_i21 = max(dp_i21, dp_i10 - price);
            // update k=1
            dp_i10 = max(dp_i10, dp_i11 + price);
            dp_i11 = max(dp_i11, -price);
        }
        return dp_i20;
    }
};
