/*
 * @lc app=leetcode id=886 lang=cpp
 *
 * [886] Possible Bipartition
 *
 * https://leetcode.com/problems/possible-bipartition/description/
 *
 * algorithms
 * Medium (41.53%)
 * Total Accepted:    16.5K
 * Total Submissions: 39.6K
 * Testcase Example:  '4\n[[1,2],[1,3],[2,4]]'
 *
 * Given a set of N people (numbered 1, 2, ..., N), we would like to split
 * everyone into two groups of any size.
 *
 * Each person may dislike some other people, and they should not go into the
 * same group. 
 *
 * Formally, if dislikes[i] = [a, b], it means it is not allowed to put the
 * people numbered a and b into the same group.
 *
 * Return true if and only if it is possible to split everyone into two groups
 * in this way.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 * Example 1:
 *
 *
 * Input: N = 4, dislikes = [[1,2],[1,3],[2,4]]
 * Output: true
 * Explanation: group1 [1,4], group2 [2,3]
 *
 *
 *
 * Example 2:
 *
 *
 * Input: N = 3, dislikes = [[1,2],[1,3],[2,3]]
 * Output: false
 *
 *
 *
 * Example 3:
 *
 *
 * Input: N = 5, dislikes = [[1,2],[2,3],[3,4],[4,5],[1,5]]
 * Output: false
 *
 *
 *
 *
 * Note:
 *
 *
 * 1 <= N <= 2000
 * 0 <= dislikes.length <= 10000
 * 1 <= dislikes[i][j] <= N
 * dislikes[i][0] < dislikes[i][1]
 * There does not exist i != j for which dislikes[i] == dislikes[j].
 *
 *
 *
 *
 *
 */

#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
  public:
    bool possibleBipartition(int N, vector<vector<int>> &dislikes) {
        // adjacent list
        unordered_map<int, vector<int>> mp;
        for (auto dislike : dislikes) {
            mp[dislike[0]].push_back(dislike[1]);
            mp[dislike[1]].push_back(dislike[0]);
        }
        // initialize: each people a group
        vector<int> root(N + 1);
        for (int i = 1; i <= N; ++i) {
            root[i] = i;
        }
        // union find
        for (int i = 1; i <= N; ++i) {
            if (mp.find(i) == mp.end())
                continue;
            // get the two groups
            int g1 = find(root, i), g2 = find(root, mp[i][0]);
            for (int j = 1; j < mp[i].size(); ++j) {
                int gj = find(root, mp[i][j]);
                // j in g1, return false
                if (gj == g1)
                    return false;
                root[gj] = g2;
            }
        }
        return true;
    }

    int find(vector<int> &root, int i) {
        return root[i] == i ? i : find(root, root[i]);
    }
};
