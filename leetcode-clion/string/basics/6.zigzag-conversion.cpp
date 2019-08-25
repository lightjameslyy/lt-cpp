/*
 * @lc app=leetcode id=6 lang=cpp
 *
 * [6] ZigZag Conversion
 *
 * https://leetcode.com/problems/zigzag-conversion/description/
 *
 * algorithms
 * Medium (31.83%)
 * Total Accepted:    318.4K
 * Total Submissions: 1M
 * Testcase Example:  '"PAYPALISHIRING"\n3'
 *
 * The string "PAYPALISHIRING" is written in a zigzag pattern on a given number
 * of rows like this: (you may want to display this pattern in a fixed font for
 * better legibility)
 * 
 * 
 * P   A   H   N
 * A P L S I I G
 * Y   I   R
 * 
 * 
 * And then read line by line: "PAHNAPLSIIGYIR"
 * 
 * Write the code that will take a string and make this conversion given a
 * number of rows:
 * 
 * 
 * string convert(string s, int numRows);
 * 
 * Example 1:
 * 
 * 
 * Input: s = "PAYPALISHIRING", numRows = 3
 * Output: "PAHNAPLSIIGYIR"
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: s = "PAYPALISHIRING", numRows = 4
 * Output: "PINALSIGYAHRPI"
 * Explanation:
 * 
 * P     I    N
 * A   L S  I G
 * Y A   H R
 * P     I
 * 
 */

/*
 * 思路：down and up
 * 1. down numRows
 * 2. up numRows-2
 */

#include <vector>

using namespace std;

class Solution {
public:
    string convert(string s, int numRows) {
        int len = s.length();
        if (len < 3 || numRows < 2)
            return s;
        vector<string> rows(numRows, "");
        for (int i = 0; i < len;) {
            for (int j = 0; j < numRows && i < len; ) {
                rows[j++] += s[i++];
            }
            for (int j = numRows - 2; j >= 1 && i < len;) {
                rows[j--] += s[i++];
            }
        }
        string res = "";
        for (auto &str : rows) {
            res += str;
        }
        return res;
    }
};
