/*
 * @lc app=leetcode id=74 lang=cpp
 *
 * [74] Search a 2D Matrix
 *
 * https://leetcode.com/problems/search-a-2d-matrix/description/
 *
 * algorithms
 * Medium (35.43%)
 * Total Accepted:    259K
 * Total Submissions: 730.9K
 * Testcase Example:  '[[1,3,5,7],[10,11,16,20],[23,30,34,50]]\n3'
 *
 * Write an efficient algorithm that searches for a value in an m x n matrix.
 * This matrix has the following properties:
 * 
 * 
 * Integers in each row are sorted from left to right.
 * The first integer of each row is greater than the last integer of the
 * previous row.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input:
 * matrix = [
 * ⁠ [1,   3,  5,  7],
 * ⁠ [10, 11, 16, 20],
 * ⁠ [23, 30, 34, 50]
 * ]
 * target = 3
 * Output: true
 * 
 * 
 * Example 2:
 * 
 * 
 * Input:
 * matrix = [
 * ⁠ [1,   3,  5,  7],
 * ⁠ [10, 11, 16, 20],
 * ⁠ [23, 30, 34, 50]
 * ]
 * target = 13
 * Output: false
 * 
 */
#include <vector>

using namespace std;

class Solution {
public:
    // 2d -> 1d
    // index: i * n + j
    // i: index/n
    // j: index%n
    bool searchMatrix(vector<vector<int>> &matrix, int target) {
        int m = matrix.size();
        if (!m) return false;
        int n = matrix[0].size();
        if (!n) return false;
        int lhs = 0, rhs = m * n - 1;
        while (lhs <= rhs) {
            int mid = lhs + (rhs - lhs) / 2;
            int val = matrix[mid / n][mid % n];
            if (val == target)
                return true;
            else if (val > target)
                rhs = mid - 1;
            else
                lhs = mid + 1;
        }
        return false;
    }
};
