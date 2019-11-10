/*
 * @lc app=leetcode id=43 lang=cpp
 *
 * [43] Multiply Strings
 *
 * https://leetcode.com/problems/multiply-strings/description/
 *
 * algorithms
 * Medium (31.89%)
 * Total Accepted:    235.2K
 * Total Submissions: 737.5K
 * Testcase Example:  '"2"\n"3"'
 *
 * Given two non-negative integers num1 and num2 represented as strings, return
 * the product of num1 and num2, also represented as a string.
 * 
 * Example 1:
 * 
 * 
 * Input: num1 = "2", num2 = "3"
 * Output: "6"
 * 
 * Example 2:
 * 
 * 
 * Input: num1 = "123", num2 = "456"
 * Output: "56088"
 * 
 * 
 * Note:
 * 
 * 
 * The length of both num1 and num2 is < 110.
 * Both num1 and num2 contain only digits 0-9.
 * Both num1 and num2 do not contain any leading zero, except the number 0
 * itself.
 * You must not use any built-in BigInteger library or convert the inputs to
 * integer directly.
 * 
 * 
 */

using namespace std;

class Solution {
public:

    string multiply_digit(const string &num, int digit, int zeros) {
        if (digit == 0)
            return "0";
        string res = num;
        int carry = 0;
        for (int i = num.length() - 1; i >= 0; --i) {
            int prod = digit * (num[i] - '0') + carry;
            res[i] = '0' + prod % 10;
            carry = prod / 10;
        }
        res.append(zeros, '0');
        if (carry > 0)
            res.insert(res.begin(), '0' + carry);
        return res;
    }

    string sum(const string &a, const string &b) {
        int lena = a.length(), lenb = b.length();
        if (lena < lenb)
            return sum(b, a);
        string res = a;
        int ai = lena - 1, bi = lenb - 1;
        int carry = 0;
        while (bi >= 0) {
            int tmp = a[ai] - '0' + b[bi] - '0' + carry;
            res[ai] = '0' + tmp % 10;
            carry = tmp / 10;
            ai--;
            bi--;
        }
        while (ai >= 0) {
            if (carry == 0)
                break;
            int tmp = res[ai] - '0' + carry;
            res[ai] = '0' + tmp % 10;
            carry = tmp / 10;
            ai--;
        }
        return (carry == 0) ? res : "1" + res;
    }

    // 8ms, 11.4MB, 64.74%
    string multiply(string num1, string num2) {
        if (num1 == "0" || num2 == "0")
            return "0";
        int len1 = num1.length(), len2 = num2.length();
        // make len1 >= len2
        if (len1 < len2)
            return multiply(num2, num1);
        string res;
        for (int i = len2 - 1; i >= 0; --i) {
            res = sum(res, multiply_digit(num1, num2[i] - '0', len2 - i - 1));
        }
        return res;
    }
};
