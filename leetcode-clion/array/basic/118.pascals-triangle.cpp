/*
 * @lc app=leetcode id=118 lang=cpp
 *
 * [118] Pascal's Triangle
 *
 * https://leetcode.com/problems/pascals-triangle/description/
 *
 * algorithms
 * Easy (48.53%)
 * Total Accepted:    300K
 * Total Submissions: 618.2K
 * Testcase Example:  '5'
 *
 * Given a non-negative integer numRows, generate the first numRows of Pascal's
 * triangle.
 * 
 * 
 * In Pascal's triangle, each number is the sum of the two numbers directly
 * above it.
 * 
 * Example:
 * 
 * 
 * Input: 5
 * Output:
 * [
 * ⁠    [1],
 * ⁠   [1,1],
 * ⁠  [1,2,1],
 * ⁠ [1,3,3,1],
 * ⁠[1,4,6,4,1]
 * ]
 * 
 * 
 */
#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> res;
        if (!numRows) return res;
        vector<int> cur = {1};
        res.push_back(cur);
        for (int len = 2; len <= numRows; ++len) {
            cur.reserve(len);
            for (int i = 1; i < len - 1; ++i) {
                cur[i] = res[len - 2][i] + res[len - 2][i - 1];
            }
            cur.push_back(1);
            res.push_back(cur);
        }
        return res;
    }
};
