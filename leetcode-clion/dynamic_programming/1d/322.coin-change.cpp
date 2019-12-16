/*
 * @lc app=leetcode id=322 lang=cpp
 *
 * [322] Coin Change
 *
 * https://leetcode.com/problems/coin-change/description/
 *
 * algorithms
 * Medium (32.32%)
 * Total Accepted:    262.7K
 * Total Submissions: 812.6K
 * Testcase Example:  '[1,2,5]\n11'
 *
 * You are given coins of different denominations and a total amount of money
 * amount. Write a function to compute the fewest number of coins that you need
 * to make up that amount. If that amount of money cannot be made up by any
 * combination of the coins, return -1.
 * 
 * Example 1:
 * 
 * 
 * Input: coins = [1, 2, 5], amount = 11
 * Output: 3 
 * Explanation: 11 = 5 + 5 + 1
 * 
 * Example 2:
 * 
 * 
 * Input: coins = [2], amount = 3
 * Output: -1
 * 
 * 
 * Note:
 * You may assume that you have an infinite number of each kind of coin.
 * 
 */

/*
 * 思路： bfs
 */

#include <queue>

using namespace std;

class Solution {
public:
    // MLE
    int coinChange1(vector<int> &coins, int amount) {
        queue<int> q;
        int level = 0;
        q.push(0);
        while (!q.empty()) {
            int size = q.size();
            for (int i = 0; i < size; ++i) {
                int cur = q.front();
                q.pop();
                if (cur == amount) return level;
                for (int c : coins) {
                    int tmp = cur + c;
                    if (tmp == amount) return level + 1;
                    if (tmp < amount)
                        q.push(tmp);
                }
            }
            ++level;
        }
        return -1;
    }

    int coinChange(vector<int> &coins, int amount) {
        // dp[i] = min coins to make up to amount i
        vector<int> dp(amount + 1, INT_MAX);
        dp[0] = 0;
        for (int coin : coins) {
            for (int i = coin; i <= amount; ++i)
                if (dp[i - coin] != INT_MAX)
                    dp[i] = min(dp[i], dp[i - coin] + 1);
        }

        return dp[amount] == INT_MAX ? -1 : dp[amount];
    }
};
