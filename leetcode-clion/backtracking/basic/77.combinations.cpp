/*
 * @lc app=leetcode id=77 lang=cpp
 *
 * [77] Combinations
 *
 * https://leetcode.com/problems/combinations/description/
 *
 * algorithms
 * Medium (50.48%)
 * Total Accepted:    236K
 * Total Submissions: 467.5K
 * Testcase Example:  '4\n2'
 *
 * Given two integers n and k, return all possible combinations of k numbers
 * out of 1 ... n.
 * 
 * Example:
 * 
 * 
 * Input: n = 4, k = 2
 * Output:
 * [
 * ⁠ [2,4],
 * ⁠ [3,4],
 * ⁠ [2,3],
 * ⁠ [1,2],
 * ⁠ [1,3],
 * ⁠ [1,4],
 * ]
 * 
 * 
 */
#include <vector>

using namespace std;

class Solution {
public:

    void dfs(int n, int k, int pos, vector<int> &cur, vector<vector<int>> &res) {
        if (k == cur.size()) {
            res.push_back(cur);
            return;
        }
        // start from num pos
        for (int i = pos; i <= n; ++i) {
            cur.push_back(i);
            dfs(n, k, i + 1, cur, res);
            cur.pop_back();
        }
    }

    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> res;
        vector<int> cur;
        dfs(n, k, 1, cur, res);
        return res;
    }
};
