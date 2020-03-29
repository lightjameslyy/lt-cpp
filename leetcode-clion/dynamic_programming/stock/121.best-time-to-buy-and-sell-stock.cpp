/*
 * @lc app=leetcode id=121 lang=cpp
 *
 * [121] Best Time to Buy and Sell Stock
 *
 * https://leetcode.com/problems/best-time-to-buy-and-sell-stock/description/
 *
 * algorithms
 * Easy (48.57%)
 * Total Accepted:    624.4K
 * Total Submissions: 1.3M
 * Testcase Example:  '[7,1,5,3,6,4]'
 *
 * Say you have an array for which the i^th element is the price of a given
 * stock on day i.
 *
 * If you were only permitted to complete at most one transaction (i.e., buy
 * one and sell one share of the stock), design an algorithm to find the
 * maximum profit.
 *
 * Note that you cannot sell a stock before you buy one.
 *
 * Example 1:
 *
 *
 * Input: [7,1,5,3,6,4]
 * Output: 5
 * Explanation: Buy on day 2 (price = 1) and sell on day 5 (price = 6), profit
 * = 6-1 = 5.
 * Not 7-1 = 6, as selling price needs to be larger than buying price.
 *
 *
 * Example 2:
 *
 *
 * Input: [7,6,4,3,1]
 * Output: 0
 * Explanation: In this case, no transaction is done, i.e. max profit = 0.
 *
 *
 */

#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

class Solution {
  public:
    int maxProfit1(vector<int> &prices) {
        if (prices.empty())
            return 0;
        int n = prices.size();
        vector<vector<int>> dp(n, vector<int>(2, 0));
        dp[0][1] = -prices[0];
        for (int i = 1; i < n; ++i) {
            dp[i][0] = max(
                           dp[i - 1][0],            // rest
                           dp[i - 1][1] + prices[i] // sell
                       );
            dp[i][1] = max(
                           -prices[i],  // buy (first buy)
                           dp[i - 1][1] // rest
                       );
        }
        return dp[n - 1][0];
    }

    int maxProfit(vector<int> &prices) {
        if (prices.empty())
            return 0;
        int n = prices.size();
        int dp_i_0 = 0, dp_i_1 = INT_MIN;
        for (int i = 0; i < n; ++i) {
            dp_i_0 = max(
                         dp_i_0,            // rest
                         dp_i_1 + prices[i] // sell
                     );
            dp_i_1 = max(
                         -prices[i], // buy (first buy)
                         dp_i_1      // rest
                     );
        }
        return dp_i_0;
    }
};
