/*
 * @lc app=leetcode id=59 lang=cpp
 *
 * [59] Spiral Matrix II
 *
 * https://leetcode.com/problems/spiral-matrix-ii/description/
 *
 * algorithms
 * Medium (49.44%)
 * Total Accepted:    158K
 * Total Submissions: 319.6K
 * Testcase Example:  '3'
 *
 * Given a positive integer n, generate a square matrix filled with elements
 * from 1 to n^2 in spiral order.
 * 
 * Example:
 * 
 * 
 * Input: 3
 * Output:
 * [
 * ⁠[ 1, 2, 3 ],
 * ⁠[ 8, 9, 4 ],
 * ⁠[ 7, 6, 5 ]
 * ]
 * 
 * 
 */
#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> matrix(n, vector<int>(n));
        int num = 0;
        int top = 0, right = n - 1, bottom = n - 1, left = 0;
        while (true) {
            int i = top, j = left;
            // move to right
            for (; j <= right; ++j)
                matrix[i][j] = ++num;
            if (num == n * n) break;
            i = ++top, j = right;
            // move to bottom
            for (; i <= bottom; ++i)
                matrix[i][j] = ++num;
            i = bottom, j = --right;
            // move to left
            for (; j >= left; --j)
                matrix[i][j] = ++num;
            if (num == n * n) break;
            i = --bottom, j = left;
            // move to top
            for (; i >= top; --i)
                matrix[i][j] = ++num;
            ++left;
        }
        return matrix;
    }
};
