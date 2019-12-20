/*
 * @lc app=leetcode id=51 lang=cpp
 *
 * [51] N-Queens
 *
 * https://leetcode.com/problems/n-queens/description/
 *
 * algorithms
 * Hard (42.10%)
 * Total Accepted:    164.6K
 * Total Submissions: 391K
 * Testcase Example:  '4'
 *
 * The n-queens puzzle is the problem of placing n queens on an n×n chessboard
 * such that no two queens attack each other.
 * 
 * 
 * 
 * Given an integer n, return all distinct solutions to the n-queens puzzle.
 * 
 * Each solution contains a distinct board configuration of the n-queens'
 * placement, where 'Q' and '.' both indicate a queen and an empty space
 * respectively.
 * 
 * Example:
 * 
 * 
 * Input: 4
 * Output: [
 * ⁠[".Q..",  // Solution 1
 * ⁠ "...Q",
 * ⁠ "Q...",
 * ⁠ "..Q."],
 * 
 * ⁠["..Q.",  // Solution 2
 * ⁠ "Q...",
 * ⁠ "...Q",
 * ⁠ ".Q.."]
 * ]
 * Explanation: There exist two distinct solutions to the 4-queens puzzle as
 * shown above.
 * 
 * 
 */
#include <vector>

using namespace std;

class Solution {
public:
    void dfs(vector<string> &board, int n, int x, int y) {
        if (y == n) return;
        if (x == n) {
            res.push_back(board);
            return;
        }
        if (!row[x] && !col[y] && !diag[x + y] && !vdiag[y - x + n - 1]) {
            board[x][y] = 'Q';
            row[x] = col[y] = diag[x + y] = vdiag[y - x + n - 1] = true;
            dfs(board, n, x + 1, 0);
            board[x][y] = '.';
            row[x] = col[y] = diag[x + y] = vdiag[y - x + n - 1] = false;
        }
        dfs(board, n, x, y + 1);
    }

    vector<vector<string>> solveNQueens(int n) {
        if (n < 1) return res;
        row = vector<bool>(n, false);
        col = vector<bool>(n, false);
        diag = vector<bool>(2 * n - 1, false);
        vdiag = vector<bool>(2 * n - 1, false);
        vector<string> board(n, string(n, '.'));
        dfs(board, n, 0, 0);
        return res;
    }

private:
    vector<vector<string>> res;
    vector<bool> row, col, diag, vdiag;
};
