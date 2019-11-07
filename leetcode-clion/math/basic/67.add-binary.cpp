/*
 * @lc app=leetcode id=67 lang=cpp
 *
 * [67] Add Binary
 *
 * https://leetcode.com/problems/add-binary/description/
 *
 * algorithms
 * Easy (41.10%)
 * Total Accepted:    353.8K
 * Total Submissions: 860.7K
 * Testcase Example:  '"11"\n"1"'
 *
 * Given two binary strings, return their sum (also a binary string).
 * 
 * The input strings are both non-empty and contains only characters 1 or 0.
 * 
 * Example 1:
 * 
 * 
 * Input: a = "11", b = "1"
 * Output: "100"
 * 
 * Example 2:
 * 
 * 
 * Input: a = "1010", b = "1011"
 * Output: "10101"
 * 
 */

using namespace std;

class Solution {
public:
    // 4ms, 8.4MB, 80.62%
    string addBinary(string a, string b) {
        int alen = a.length(), blen = b.length();
        if (alen < blen)
            return addBinary(b, a);
        int carry = 0;
        int ai = alen - 1, bi = blen - 1;
        int sum = 0;
        for (; bi >= 0; --bi, --ai) {
            sum = a[ai] - '0' + b[bi] - '0' + carry;
            if (sum == 1) {
                carry = 0;
                a[ai] = '1';
            } else if (sum == 2) {
                carry = 1;
                a[ai] = '0';
            }
        }
        for (; ai >= 0; --ai) {
            sum = a[ai] - '0' + carry;
            if (sum == 2) {
                a[ai] = '0';
            } else {
                a[ai] = '0' + sum;
                carry = 0;
                break;
            }
        }
        return (carry == 1) ? "1" + a : a;
    }
};
