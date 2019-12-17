/*
 * @lc app=leetcode id=221 lang=cpp
 *
 * [221] Maximal Square
 *
 * https://leetcode.com/problems/maximal-square/description/
 *
 * algorithms
 * Medium (34.47%)
 * Total Accepted:    160.1K
 * Total Submissions: 464.4K
 * Testcase Example:  '[["1","0","1","0","0"],["1","0","1","1","1"],["1","1","1","1","1"],["1","0","0","1","0"]]'
 *
 * Given a 2D binary matrix filled with 0's and 1's, find the largest square
 * containing only 1's and return its area.
 * 
 * Example:
 * 
 * 
 * Input: 
 * 
 * 1 0 1 0 0
 * 1 0 1 1 1
 * 1 1 1 1 1
 * 1 0 0 1 0
 * 
 * Output: 4
 * 
 */

/*
 * dp[i][j] = (matrix[i][j] ? min(dp[i-1][j-1], dp[i-1][j], dp[i][j-1]) + 1 :0)
 */

#include <vector>

using namespace std;

class Solution {
public:
    int maximalSquare(vector<vector<char>> &matrix) {
        int rows = matrix.size();
        if (!rows) return 0;
        int cols = matrix[0].size();
        if (!cols) return 0;
        int res = 0;
        vector<int> dp(cols);
        for (int i = 0; i < cols; ++i) {
            dp[i] = (matrix[0][i] == '1');
            if (dp[i] > res)
                res = dp[i];
        }
        for (int i = 1; i < rows; ++i) {
            int pre = dp[0];
            dp[0] = (matrix[i][0] == '1');
            if (dp[0] > res)
                res = dp[0];
            for (int j = 1; j < cols; ++j) {
                int tmp = dp[j];
                if (matrix[i][j] == '0') {
                    dp[j] = 0;
                } else {
                    dp[j] = 1 + min(pre, min(dp[j - 1], dp[j]));
                }
                pre = tmp;
                if (dp[j] > res)
                    res = dp[j];
            }
        }
        return res * res;
    }
};
