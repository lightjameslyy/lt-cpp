/*
 * @lc app=leetcode id=286 lang=cpp
 *
 * [286] Walls and Gates
 *
 * https://leetcode.com/problems/walls-and-gates/description/
 *
 * algorithms
 * Medium (51.04%)
 * Total Accepted:    89.4K
 * Total Submissions: 175.1K
 * Testcase Example:  '[[2147483647,-1,0,2147483647],[2147483647,2147483647,2147483647,-1],[2147483647,-1,2147483647,-1],[0,-1,2147483647,2147483647]]'
 *
 * You are given a m x n 2D grid initialized with these three possible
 * values.
 * 
 * 
 * -1 - A wall or an obstacle.
 * 0 - A gate.
 * INF - Infinity means an empty room. We use the value 2^31 - 1 = 2147483647
 * to represent INF as you may assume that the distance to a gate is less than
 * 2147483647.
 * 
 * 
 * Fill each empty room with the distance to its nearest gate. If it is
 * impossible to reach a gate, it should be filled with INF.
 * 
 * Example: 
 * 
 * Given the 2D grid:
 * 
 * 
 * INF  -1  0  INF
 * INF INF INF  -1
 * INF  -1 INF  -1
 * ⁠ 0  -1 INF INF
 * 
 * 
 * After running your function, the 2D grid should be:
 * 
 * 
 * ⁠ 3  -1   0   1
 * ⁠ 2   2   1  -1
 * ⁠ 1  -1   2  -1
 * ⁠ 0  -1   3   4
 * 
 * 
 */
#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    void bfs(vector<vector<int>> &rooms, queue<pair<int, int>> &q) {
        int distance = 0;
        while (!q.empty()) {
            for (int size = q.size(); size > 0; --size) {
                int i = q.front().first, j = q.front().second;
                q.pop();
                if (!distance || rooms[i][j] > distance) {
                    rooms[i][j] = distance;
                    if (i > 0)
                        q.push(make_pair(i - 1, j));
                    if (i < rooms.size() - 1)
                        q.push(make_pair(i + 1, j));
                    if (j > 0)
                        q.push(make_pair(i, j - 1));
                    if (j < rooms[0].size() - 1)
                        q.push(make_pair(i, j + 1));
                }
            }
            ++distance;
        }
    }

    void wallsAndGates(vector<vector<int>> &rooms) {
        int m = rooms.size();
        if (!m) return;
        int n = rooms[0].size();
        if (!n) return;
        queue<pair<int, int>> q;
        for (int i = 0; i < m; ++i)
            for (int j = 0; j < n; ++j) {
                if (rooms[i][j] == 0) {
                    q.push(make_pair(i, j));
                    bfs(rooms, q);
                }
            }
    }
};
