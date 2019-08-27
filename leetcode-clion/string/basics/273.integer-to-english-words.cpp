/*
 * @lc app=leetcode id=273 lang=cpp
 *
 * [273] Integer to English Words
 *
 * https://leetcode.com/problems/integer-to-english-words/description/
 *
 * algorithms
 * Hard (24.33%)
 * Total Accepted:    113.9K
 * Total Submissions: 460K
 * Testcase Example:  '123'
 *
 * Convert a non-negative integer to its english words representation. Given
 * input is guaranteed to be less than 231 - 1.
 * 
 * Example 1:
 * 
 * 
 * Input: 123
 * Output: "One Hundred Twenty Three"
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: 12345
 * Output: "Twelve Thousand Three Hundred Forty Five"
 * 
 * Example 3:
 * 
 * 
 * Input: 1234567
 * Output: "One Million Two Hundred Thirty Four Thousand Five Hundred Sixty
 * Seven"
 * 
 * 
 * Example 4:
 * 
 * 
 * Input: 1234567891
 * Output: "One Billion Two Hundred Thirty Four Million Five Hundred Sixty
 * Seven Thousand Eight Hundred Ninety One"
 * 
 * 
 */

#include <string>
#include <cassert>

using namespace std;

class Solution {
public:
    string base[4] = {"", "Thousand", "Million", "Billion"};
    string ones[20] = {"", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Eleven",
                       "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
    string tens[10] = {"", "Ten", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
    string hundreds[10] = {"", "One Hundred", "Two Hundred", "Three Hundred", "Four Hundred", "Five Hundred",
                           "Six Hundred", "Seven Hundred", "Eight Hundred", "Nine Hundred"};

    string trim(const string &s) {
        int pos = s.find_first_not_of(' ');
        int len = s.find_last_not_of(' ') - pos + 1;
        return s.substr(pos, len);
    }

    string decode(int val, int magnitude) {
        string res = "";
        if (val == 0)
            return res;
        int hundred = val / 100;
        int ten = val / 10 % 10;
        int one = val % 10;
        if (hundred)
            res += hundreds[hundred] + " ";
        if (ten == 1)
            res += ones[ten * 10 + one] + " ";
        else {
            if (ten)
                res += tens[ten] + " ";
            if (one)
                res += ones[one] + " ";
        }
        res += base[magnitude];
        return trim(res);
    }

    // decode each 3 digits
    string numberToWords(int num) {
        if (num == 0)
            return "Zero";
        string res = "";
        int base = 1e9;
        for (int i = 3; i >= 0; --i) {
            if (num == 0) break;
            int val = num / base;
            string tmp = decode(val, i);
            if (!tmp.empty())
                res += decode(val, i) + " ";
            num -= val * base;
            base /= 1000;
        }
        return trim(res);
    }
};
