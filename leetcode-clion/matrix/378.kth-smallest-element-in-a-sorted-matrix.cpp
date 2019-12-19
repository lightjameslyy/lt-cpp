/*
 * @lc app=leetcode id=378 lang=cpp
 *
 * [378] Kth Smallest Element in a Sorted Matrix
 *
 * https://leetcode.com/problems/kth-smallest-element-in-a-sorted-matrix/description/
 *
 * algorithms
 * Medium (51.16%)
 * Total Accepted:    135.5K
 * Total Submissions: 264.9K
 * Testcase Example:  '[[1,5,9],[10,11,13],[12,13,15]]\n8'
 *
 * Given a n x n matrix where each of the rows and columns are sorted in
 * ascending order, find the kth smallest element in the matrix.
 * 
 * 
 * Note that it is the kth smallest element in the sorted order, not the kth
 * distinct element.
 * 
 * 
 * Example:
 * 
 * matrix = [
 * ⁠  [ 1,  5,  9],
 * ⁠  [10, 11, 13],
 * ⁠  [12, 13, 15]
 * ],
 * k = 8,
 * 
 * return 13.
 * 
 * 
 * 
 * Note: 
 * You may assume k is always valid, 1 ≤ k ≤ n^2.
 */
#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    typedef pair<int, int> Coord;

    // my
    int kthSmallest1(vector<vector<int>> &matrix, int k) {
        int n = matrix.size();
        auto cmp = [&](const Coord &a, const Coord &b) {
            return matrix[a.first][a.second] > matrix[b.first][b.second];
        };
        priority_queue<Coord, vector<Coord>, decltype(cmp)> heap(cmp);
        for (int i = 0; i < n; ++i)
            heap.push(make_pair(i, 0));
        for (int i = 0; i < k - 1; ++i) {
            Coord cur = heap.top();
            heap.pop();
            if (cur.second < n - 1)
                heap.push(make_pair(cur.first, cur.second + 1));
        }
        Coord res = heap.top();
        return matrix[res.first][res.second];
    }

    // copied, binary search
    int kthSmallest(vector<vector<int>> &matrix, int k) {
        const int n = matrix.size();
        // scope: [l, r)
        long l = matrix[0][0], r = matrix[n - 1][n - 1] + 1;
        while (l < r) {
            long m = l + (r - l) / 2;
            int total = 0;
            int s = n;
            // count each row: matrix[i][j] <= m
            // s is shrinking
            for (const auto &row : matrix)
                total += (s = distance(begin(row), upper_bound(begin(row), begin(row) + s, m)));
            if (total >= k)
                r = m;
            else
                l = m + 1;
        }
        return l;
    }
};
