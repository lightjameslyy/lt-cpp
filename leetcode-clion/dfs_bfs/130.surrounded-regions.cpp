/*
 * @lc app=leetcode id=130 lang=cpp
 *
 * [130] Surrounded Regions
 *
 * https://leetcode.com/problems/surrounded-regions/description/
 *
 * algorithms
 * Medium (24.40%)
 * Total Accepted:    168.9K
 * Total Submissions: 692.1K
 * Testcase Example:  '[["X","X","X","X"],["X","O","O","X"],["X","X","O","X"],["X","O","X","X"]]'
 *
 * Given a 2D board containing 'X' and 'O' (the letter O), capture all regions
 * surrounded by 'X'.
 * 
 * A region is captured by flipping all 'O's into 'X's in that surrounded
 * region.
 * 
 * Example:
 * 
 * 
 * X X X X
 * X O O X
 * X X O X
 * X O X X
 * 
 * 
 * After running your function, the board should be:
 * 
 * 
 * X X X X
 * X X X X
 * X X X X
 * X O X X
 * 
 * 
 * Explanation:
 * 
 * Surrounded regions shouldn’t be on the border, which means that any 'O' on
 * the border of the board are not flipped to 'X'. Any 'O' that is not on the
 * border and it is not connected to an 'O' on the border will be flipped to
 * 'X'. Two cells are connected if they are adjacent cells connected
 * horizontally or vertically.
 * 
 */
#include <vector>

using namespace std;

class Solution {
public:
    void dfs(vector<vector<char>> &board, vector<vector<bool>> &visited, int i, int j) {
        if (i < 0 || i >= board.size() || j < 0 || j >= board[0].size()) return;
        if (board[i][j] == 'X' || visited[i][j]) return;
        visited[i][j] = true;
        dfs(board, visited, i - 1, j);
        dfs(board, visited, i + 1, j);
        dfs(board, visited, i, j - 1);
        dfs(board, visited, i, j + 1);
    }

    void solve(vector<vector<char>> &board) {
        int m = board.size();
        if (m < 2) return;
        int n = board[0].size();
        if (n < 2) return;
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        for (int i = 0; i < m; ++i) {
            if (board[i][0] == 'O' && !visited[i][0])
                dfs(board, visited, i, 0);
            if (board[i][n - 1] == 'O' && !visited[i][n - 1])
                dfs(board, visited, i, n - 1);
        }
        for (int j = 0; j < n; ++j) {
            if (board[0][j] == 'O' && !visited[0][j])
                dfs(board, visited, 0, j);
            if (board[m - 1][j] == 'O' && !visited[m - 1][j])
                dfs(board, visited, m - 1, j);
        }
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j)
                if (board[i][j] == 'O' && !visited[i][j])
                    board[i][j] = 'X';
        }
    }
};
