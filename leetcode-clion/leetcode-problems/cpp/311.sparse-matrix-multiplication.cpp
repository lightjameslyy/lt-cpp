/*
 * @lc app=leetcode id=311 lang=cpp
 *
 * [311] Sparse Matrix Multiplication
 *
 * https://leetcode.com/problems/sparse-matrix-multiplication/description/
 *
 * algorithms
 * Medium (58.07%)
 * Total Accepted:    73.4K
 * Total Submissions: 126.4K
 * Testcase Example:  '[[1,0,0],[-1,0,3]]\n[[7,0,0],[0,0,0],[0,0,1]]'
 *
 * Given two sparse matrices A and B, return the result of AB.
 * 
 * You may assume that A's column number is equal to B's row number.
 * 
 * Example:
 * 
 * 
 * Input:
 * 
 * A = [
 * ⁠ [ 1, 0, 0],
 * ⁠ [-1, 0, 3]
 * ]
 * 
 * B = [
 * ⁠ [ 7, 0, 0 ],
 * ⁠ [ 0, 0, 0 ],
 * ⁠ [ 0, 0, 1 ]
 * ]
 * 
 * Output:
 * 
 * ⁠    |  1 0 0 |   | 7 0 0 |   |  7 0 0 |
 * AB = | -1 0 3 | x | 0 0 0 | = | -7 0 3 |
 * ⁠                 | 0 0 1 |
 * 
 * 
 */
class Solution {
public:
    vector<vector<int>> multiply(vector<vector<int>>& A, vector<vector<int>>& B) {
        
    }
};
