/*
 * @lc app=leetcode id=168 lang=cpp
 *
 * [168] Excel Sheet Column Title
 *
 * https://leetcode.com/problems/excel-sheet-column-title/description/
 *
 * algorithms
 * Easy (28.96%)
 * Total Accepted:    181.5K
 * Total Submissions: 617K
 * Testcase Example:  '1'
 *
 * Given a positive integer, return its corresponding column title as appear in
 * an Excel sheet.
 * 
 * For example:
 * 
 * 
 * ⁠   1 -> A
 * ⁠   2 -> B
 * ⁠   3 -> C
 * ⁠   ...
 * ⁠   26 -> Z
 * ⁠   27 -> AA
 * ⁠   28 -> AB 
 * ⁠   ...
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: 1
 * Output: "A"
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: 28
 * Output: "AB"
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: 701
 * Output: "ZY"
 * 
 */

#include <string>
#include <algorithm>
#include <cassert>


using namespace std;

class Solution {
public:
    // neat code: convert to zero based
    string convertToTitle(int n) {
        string res;
        while (n) {
            n--;
            res += 'A' + n%26;
            n /= 26;
        }
        reverse(res.begin(), res.end());
        return res;
    }

    string convertToTitle1(int n) {
        assert(n > 0);
        string res = "";
        while (true) {
            if (n <= 26) {
                res += n - 1 + 'A';
                break;
            }
            int remainder = n % 26;
            if (!remainder) {
                res += 'Z';
                n -= 26;
            } else {
                res += (n % 26 - 1) + 'A';
            }
            n /= 26;
        }
        reverse(res.begin(), res.end());
        return res;
    }
};
