/*
 * @lc app=leetcode id=79 lang=cpp
 *
 * [79] Word Search
 *
 * https://leetcode.com/problems/word-search/description/
 *
 * algorithms
 * Medium (32.77%)
 * Total Accepted:    346.7K
 * Total Submissions: 1.1M
 * Testcase Example:  '[["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]]\n"ABCCED"'
 *
 * Given a 2D board and a word, find if the word exists in the grid.
 * 
 * The word can be constructed from letters of sequentially adjacent cell,
 * where "adjacent" cells are those horizontally or vertically neighboring. The
 * same letter cell may not be used more than once.
 * 
 * Example:
 * 
 * 
 * board =
 * [
 * ⁠ ['A','B','C','E'],
 * ⁠ ['S','F','C','S'],
 * ⁠ ['A','D','E','E']
 * ]
 * 
 * Given word = "ABCCED", return true.
 * Given word = "SEE", return true.
 * Given word = "ABCB", return false.
 * 
 * 
 */
#include <vector>

using namespace std;

class Solution {
public:
    bool helper(vector<vector<char>> &board, const string &word, int pos, vector<vector<bool>> &visited, int x, int y) {
        if (pos == word.length()) return true;
        // validate x and y
        if (x < 0 || x >= board.size() || y < 0 || y >= board[0].size())
            return false;
        if (visited[x][y]) return false;
        if (board[x][y] != word[pos]) return false;
        visited[x][y] = true;
        bool res = helper(board, word, pos + 1, visited, x - 1, y)
                   || helper(board, word, pos + 1, visited, x + 1, y)
                   || helper(board, word, pos + 1, visited, x, y - 1)
                   || helper(board, word, pos + 1, visited, x, y + 1);
        visited[x][y] = false;
        return res;
    }

    bool exist(vector<vector<char>> &board, string word) {
        int m = board.size();
        if (!m) return false;
        int n = board[0].size();
        if (!n) return false;
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        for (int i = 0; i < m; ++i)
            for (int j = 0; j < n; ++j)
                if (helper(board, word, 0, visited, i, j)) return true;
        return false;
    }
};
