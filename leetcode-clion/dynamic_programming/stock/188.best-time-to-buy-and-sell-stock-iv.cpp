/*
 * @lc app=leetcode id=188 lang=cpp
 *
 * [188] Best Time to Buy and Sell Stock IV
 *
 * https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iv/description/
 *
 * algorithms
 * Hard (27.05%)
 * Total Accepted:    102.6K
 * Total Submissions: 379.3K
 * Testcase Example:  '2\n[2,4,1]'
 *
 * Say you have an array for which the i-th element is the price of a given
 * stock on day i.
 *
 * Design an algorithm to find the maximum profit. You may complete at most k
 * transactions.
 *
 * Note:
 * You may not engage in multiple transactions at the same time (ie, you must
 * sell the stock before you buy again).
 *
 * Example 1:
 *
 *
 * Input: [2,4,1], k = 2
 * Output: 2
 * Explanation: Buy on day 1 (price = 2) and sell on day 2 (price = 4), profit
 * = 4-2 = 2.
 *
 *
 * Example 2:
 *
 *
 * Input: [3,2,6,5,0,3], k = 2
 * Output: 7
 * Explanation: Buy on day 2 (price = 2) and sell on day 3 (price = 6), profit
 * = 6-2 = 4.
 * Then buy on day 5 (price = 0) and sell on day 6 (price = 3), profit = 3-0 =
 * 3.
 *
 *
 */

#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

/*
 * state transmission:
 *      dp[i][k][0] = max(dp[i-1][k][0], dp[i-1][k][1] + prices[i])
 *      dp[i][k][1] = max(dp[i-1][k][1], dp[i-1][k-1][0] - prices[i])
 */

class Solution {
  public:
    int maxProfit_k_inf(vector<int> &prices) {
        int n = prices.size();
        int dp_i_0 = 0, dp_i_1 = INT_MIN;
        for (int i = 0; i < n; ++i) {
            int tmp = dp_i_0;
            dp_i_0 = max(
                         dp_i_0,            // rest
                         dp_i_1 + prices[i] // sell
                     );
            dp_i_1 = max(
                         dp_i_1,         // rest
                         tmp - prices[i] // buy
                     );
        }
        return dp_i_0;
    }

    int maxProfit(int k, vector<int> &prices) {
        int n = prices.size();
        if (k > n / 2)
            return maxProfit_k_inf(prices);
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(k + 1, vector<int>(2, 0)));
        for (int i = 0; i < n; ++i) {
            for (int kk = k; kk > 0; --kk) {
                if (i == 0) {
                    // base case
                    dp[i][kk][0] = 0;
                    dp[i][kk][1] = -prices[i];
                    continue;
                }
                dp[i][kk][0] = max(dp[i - 1][kk][0], dp[i - 1][kk][1] + prices[i]);
                dp[i][kk][1] = max(dp[i - 1][kk][1], dp[i - 1][kk - 1][0] - prices[i]);
            }
        }
        return dp[n - 1][k][0];
    }
};
