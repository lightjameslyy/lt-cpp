/*
 * @lc app=leetcode id=370 lang=cpp
 *
 * [370] Range Addition
 *
 * https://leetcode.com/problems/range-addition/description/
 *
 * algorithms
 * Medium (61.37%)
 * Total Accepted:    27.2K
 * Total Submissions: 44.3K
 * Testcase Example:  '5\n[[1,3,2],[2,4,3],[0,2,-2]]'
 *
 * Assume you have an array of length n initialized with all 0's and are given
 * k update operations.
 * 
 * Each operation is represented as a triplet: [startIndex, endIndex, inc]
 * which increments each element of subarray A[startIndex ... endIndex]
 * (startIndex and endIndex inclusive) with inc.
 * 
 * Return the modified array after all k operations were executed.
 * 
 * Example:
 * 
 * 
 * Input: length = 5, updates = [[1,3,2],[2,4,3],[0,2,-2]]
 * Output: [-2,0,3,5,3]
 * 
 * 
 * Explanation:
 * 
 * 
 * Initial state:
 * [0,0,0,0,0]
 * 
 * After applying operation [1,3,2]:
 * [0,2,2,2,0]
 * 
 * After applying operation [2,4,3]:
 * [0,2,5,5,3]
 * 
 * After applying operation [0,2,-2]:
 * [-2,0,3,5,3]
 * 
 */
#include <vector>

using namespace std;

class Solution {
public:
    // tle
    vector<int> getModifiedArray1(int length, vector<vector<int>> &updates) {
        vector<int> res(length, 0);
        for (const auto &ops: updates) {
            for (int i = ops[0]; i <= ops[1]; ++i)
                res[i] += ops[2];
        }
        return res;
    }

    // copied
    // 建立累加和数组
    vector<int> getModifiedArray(int length, vector<vector<int>> &updates) {
        vector<int> res(length + 1, 0);
        for (auto &op : updates) {
            res[op[0]] += op[2];
            res[op[1] + 1] -= op[2];
        }
        int sum = res[0];
        for (int i = 1; i < length; ++i) {
            res[i] = (sum += res[i]);
        }
        res.pop_back();
        return res;
    }
};
