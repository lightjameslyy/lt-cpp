/*
 * @lc app=leetcode id=240 lang=cpp
 *
 * [240] Search a 2D Matrix II
 *
 * https://leetcode.com/problems/search-a-2d-matrix-ii/description/
 *
 * algorithms
 * Medium (41.74%)
 * Total Accepted:    223.4K
 * Total Submissions: 535.1K
 * Testcase Example:  '[[1,4,7,11,15],[2,5,8,12,19],[3,6,9,16,22],[10,13,14,17,24],[18,21,23,26,30]]\n' +
  '5'
 *
 * Write an efficient algorithm that searches for a value in an m x n matrix.
 * This matrix has the following properties:
 * 
 * 
 * Integers in each row are sorted in ascending from left to right.
 * Integers in each column are sorted in ascending from top to bottom.
 * 
 * 
 * Example:
 * 
 * Consider the following matrix:
 * 
 * 
 * [
 * ⁠ [1,   4,  7, 11, 15],
 * ⁠ [2,   5,  8, 12, 19],
 * ⁠ [3,   6,  9, 16, 22],
 * ⁠ [10, 13, 14, 17, 24],
 * ⁠ [18, 21, 23, 26, 30]
 * ]
 * 
 * 
 * Given target = 5, return true.
 * 
 * Given target = 20, return false.
 * 
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    // my
    bool searchMatrix1(vector<vector<int>> &matrix, int target) {
        int m = matrix.size();
        if (!m) return false;
        int n = matrix[0].size();
        if (!n) return false;
        int end = n;
        for (const auto &row : matrix) {
            end = distance(row.begin(), upper_bound(row.begin(), row.begin() + end, target));
            if (end == 0)
                break;
            if (row[end - 1] == target)
                return true;
        }
        return false;
    }

    // copied
    // from top-right to bottom-left
    bool searchMatrix(vector<vector<int>> &matrix, int target) {
        int m = matrix.size();
        if (!m) return false;
        int n = matrix[0].size();
        if (!n) return false;
        for (int i = 0, j = n - 1; i < m && j >= 0;) {
            if (matrix[i][j] == target)
                return true;
            else if (matrix[i][j] < target)
                j++;
            else
                i--;
        }
        return false;
    }
};
