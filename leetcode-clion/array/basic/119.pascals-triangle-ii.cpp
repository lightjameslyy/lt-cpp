/*
 * @lc app=leetcode id=119 lang=cpp
 *
 * [119] Pascal's Triangle II
 *
 * https://leetcode.com/problems/pascals-triangle-ii/description/
 *
 * algorithms
 * Easy (45.71%)
 * Total Accepted:    232.3K
 * Total Submissions: 508.3K
 * Testcase Example:  '3'
 *
 * Given a non-negative index k where k ≤ 33, return the k^th index row of the
 * Pascal's triangle.
 * 
 * Note that the row index starts from 0.
 * 
 * 
 * In Pascal's triangle, each number is the sum of the two numbers directly
 * above it.
 * 
 * Example:
 * 
 * 
 * Input: 3
 * Output: [1,3,3,1]
 * 
 * 
 * Follow up:
 * 
 * Could you optimize your algorithm to use only O(k) extra space?
 * 
 */
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> getRow(int rowIndex) {
        vector<int> cur, next;
        cur.resize(rowIndex + 1, 1);
        next = cur;
        for (int i = 1; i <= rowIndex; ++i) {
            int len = i + 1;
            for (int j = 1; j < len - 1; ++j) {
                next[j] = cur[j] + cur[j - 1];
            }
            swap(cur, next);
        }
        cur.resize(rowIndex + 1);
        return cur;
    }
};
