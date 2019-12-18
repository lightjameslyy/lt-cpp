/*
 * @lc app=leetcode id=54 lang=cpp
 *
 * [54] Spiral Matrix
 *
 * https://leetcode.com/problems/spiral-matrix/description/
 *
 * algorithms
 * Medium (31.87%)
 * Total Accepted:    281.7K
 * Total Submissions: 883.9K
 * Testcase Example:  '[[1,2,3],[4,5,6],[7,8,9]]'
 *
 * Given a matrix of m x n elements (m rows, n columns), return all elements of
 * the matrix in spiral order.
 * 
 * Example 1:
 * 
 * 
 * Input:
 * [
 * ⁠[ 1, 2, 3 ],
 * ⁠[ 4, 5, 6 ],
 * ⁠[ 7, 8, 9 ]
 * ]
 * Output: [1,2,3,6,9,8,7,4,5]
 * 
 * 
 * Example 2:
 * 
 * Input:
 * [
 * ⁠ [1, 2, 3, 4],
 * ⁠ [5, 6, 7, 8],
 * ⁠ [9,10,11,12]
 * ]
 * Output: [1,2,3,4,8,12,11,10,9,5,6,7]
 * 
 */
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>> &matrix) {
        vector<int> res;
        int m = matrix.size();
        if (!m) return res;
        int n = matrix[0].size();
        if (!n) return res;
        int size = m * n;
        res.reserve(size);
        int top = 0, right = n - 1, bottom = m - 1, left = 0;
        while (true) {
            int i = top, j = left;
            // move to right
            for (; j <= right; ++j)
                res.push_back(matrix[i][j]);
            if (res.size() == size) break;
            i = ++top, j = right;
            // move to bottom
            for (; i <= bottom; ++i)
                res.push_back(matrix[i][j]);
            i = bottom, j = --right;
            // move to left
            for (; j >= left; --j)
                res.push_back(matrix[i][j]);
            if (res.size() == size) break;
            i = --bottom, j = left;
            // move to top
            for (; i >= top; --i)
                res.push_back(matrix[i][j]);
            ++left;
        }
        return res;
    }
};
