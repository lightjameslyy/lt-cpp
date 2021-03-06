/*
 * @lc app=leetcode id=276 lang=cpp
 *
 * [276] Paint Fence
 *
 * https://leetcode.com/problems/paint-fence/description/
 *
 * algorithms
 * Easy (37.16%)
 * Total Accepted:    46.8K
 * Total Submissions: 125.9K
 * Testcase Example:  '3\n2'
 *
 * There is a fence with n posts, each post can be painted with one of the k
 * colors.
 * 
 * You have to paint all the posts such that no more than two adjacent fence
 * posts have the same color.
 * 
 * Return the total number of ways you can paint the fence.
 * 
 * Note:
 * n and k are non-negative integers.
 * 
 * Example:
 * 
 * 
 * Input: n = 3, k = 2
 * Output: 6
 * Explanation: Take c1 as color 1, c2 as color 2. All possible ways
 * are:
 * 
 * post1  post2  post3      
 * ⁠-----      -----  -----  -----       
 * ⁠  1         c1     c1     c2 
 * 2         c1     c2     c1 
 * 3         c1     c2     c2 
 * 4         c2     c1     c1  
 * ⁠  5         c2     c1     c2
 * 6         c2     c2     c1
 * 
 * 
 */
#include <vector>

using namespace std;

class Solution {
public:
    int numWays(int n, int k) {
        vector<int> dp = {0, k, k * k, 0};
        if (n < 3) return dp[n];
        for (int i = 3; i <= n; ++i) {
            dp[3] = (k - 1) * (dp[1] + dp[2]);
            dp[1] = dp[2];
            dp[2] = dp[3];
        }
        return dp[3];
    }
};
