/*
 * @lc app=leetcode id=38 lang=cpp
 *
 * [38] Count and Say
 *
 * https://leetcode.com/problems/count-and-say/description/
 *
 * algorithms
 * Easy (40.59%)
 * Total Accepted:    285K
 * Total Submissions: 702.2K
 * Testcase Example:  '1'
 *
 * The count-and-say sequence is the sequence of integers with the first five
 * terms as following:
 * 
 * 
 * 1.     1
 * 2.     11
 * 3.     21
 * 4.     1211
 * 5.     111221
 * 
 * 
 * 1 is read off as "one 1" or 11.
 * 11 is read off as "two 1s" or 21.
 * 21 is read off as "one 2, then one 1" or 1211.
 * 
 * Given an integer n where 1 ≤ n ≤ 30, generate the nth term of the
 * count-and-say sequence.
 * 
 * Note: Each term of the sequence of integers will be represented as a
 * string.
 * 
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: 1
 * Output: "1"
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: 4
 * Output: "1211"
 * 
 */

/*
 * 思路：挨个生成
 */

#include <vector>

using namespace std;

class Solution {
public:
    string countAndSay(int n) {
        vector<string> res(n + 1, "");
        res[1] = "1";
        for (int i = 2; i <= n; ++i) {
            int count = 1;
            int start = 0;
            for (int j = 1; j < res[i - 1].length(); ++j) {
                if (res[i - 1][j] != res[i - 1][start]) {
                    res[i] += to_string(count);
                    res[i] += res[i - 1][start];
                    count = 1;
                    start = j;
                } else {
                    count++;
                }
            }
            res[i] += to_string(count);
            res[i] += res[i - 1][start];
        }
        return res[n];
    }
};
