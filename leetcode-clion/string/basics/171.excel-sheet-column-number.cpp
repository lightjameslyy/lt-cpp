/*
 * @lc app=leetcode id=171 lang=cpp
 *
 * [171] Excel Sheet Column Number
 *
 * https://leetcode.com/problems/excel-sheet-column-number/description/
 *
 * algorithms
 * Easy (51.49%)
 * Total Accepted:    234.4K
 * Total Submissions: 449.6K
 * Testcase Example:  '"A"'
 *
 * Given a column title as appear in an Excel sheet, return its corresponding
 * column number.
 * 
 * For example:
 * 
 * 
 * ⁠   A -> 1
 * ⁠   B -> 2
 * ⁠   C -> 3
 * ⁠   ...
 * ⁠   Z -> 26
 * ⁠   AA -> 27
 * ⁠   AB -> 28 
 * ⁠   ...
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: "A"
 * Output: 1
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: "AB"
 * Output: 28
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: "ZY"
 * Output: 701
 * 
 */
#include <cassert>

using namespace std;

class Solution {
public:
    // more neat code: forwards
    int titleToNumber(string s) {
        assert(!s.empty());
        int res = 0;
        for (int i = 0; i < s.length(); ++i) {
            res += s[i] - 'A' + 1;
            if (i != s.length() - 1)
                res *= 26;
        }
        return res;
    }

    // backwards
    int titleToNumber1(string s) {
        assert(!s.empty());
        int res = 0;
        long long base = 1;
        for (int i = s.length() - 1; i >= 0; --i) {
            int num = s[i] - 'A' + 1;
            res += num * base;
            base *= 26;
        }
        return res;
    }
};
