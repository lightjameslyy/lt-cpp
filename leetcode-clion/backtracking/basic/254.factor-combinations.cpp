/*
 * @lc app=leetcode id=254 lang=cpp
 *
 * [254] Factor Combinations
 *
 * https://leetcode.com/problems/factor-combinations/description/
 *
 * algorithms
 * Medium (45.35%)
 * Total Accepted:    60.8K
 * Total Submissions: 134K
 * Testcase Example:  '1'
 *
 * Numbers can be regarded as product of its factors. For example,
 * 
 * 
 * 8 = 2 x 2 x 2;
 * ⁠ = 2 x 4.
 * 
 * 
 * Write a function that takes an integer n and return all possible
 * combinations of its factors.
 * 
 * Note:
 * 
 * 
 * You may assume that n is always positive.
 * Factors should be greater than 1 and less than n.
 * 
 * 
 * Example 1: 
 * 
 * 
 * Input: 1
 * Output: []
 * 
 * 
 * Example 2: 
 * 
 * 
 * Input: 37
 * Output:[]
 * 
 * Example 3: 
 * 
 * 
 * Input: 12
 * Output:
 * [
 * ⁠ [2, 6],
 * ⁠ [2, 2, 3],
 * ⁠ [3, 4]
 * ]
 * 
 * Example 4: 
 * 
 * 
 * Input: 32
 * Output:
 * [
 * ⁠ [2, 16],
 * ⁠ [2, 2, 8],
 * ⁠ [2, 2, 2, 4],
 * ⁠ [2, 2, 2, 2, 2],
 * ⁠ [2, 4, 4],
 * ⁠ [4, 8]
 * ]
 * 
 * 
 */
#include <vector>

using namespace std;

class Solution {
public:
    void dfs(int n, long long prod, int pos, vector<int> &cur, vector<vector<int>> &res) {
        if (n == prod) {
            res.push_back(cur);
            return;
        }
        if (prod > n)
            return;
        for (int i = pos; i <= n / prod; ++i) {
            if (n % i)
                continue;
            cur.push_back(i);
            dfs(n, prod * i, i, cur, res);
            cur.pop_back();
        }
    }

    vector<vector<int>> getFactors(int n) {
        vector<vector<int>> res;
        if (n < 4) return res;
        vector<int> cur;
        long long prod = 1;
        dfs(n, 1, 2, cur, res);
        return res;
    }
};
