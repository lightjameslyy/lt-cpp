/*
 * @lc app=leetcode id=12 lang=cpp
 *
 * [12] Integer to Roman
 *
 * https://leetcode.com/problems/integer-to-roman/description/
 *
 * algorithms
 * Medium (50.91%)
 * Total Accepted:    256.1K
 * Total Submissions: 493.8K
 * Testcase Example:  '3'
 *
 * Roman numerals are represented by seven different symbols: I, V, X, L, C, D
 * and M.
 * 
 * 
 * Symbol       Value
 * I             1
 * V             5
 * X             10
 * L             50
 * C             100
 * D             500
 * M             1000
 * 
 * For example, two is written as II in Roman numeral, just two one's added
 * together. Twelve is written as, XII, which is simply X + II. The number
 * twenty seven is written as XXVII, which is XX + V + II.
 * 
 * Roman numerals are usually written largest to smallest from left to right.
 * However, the numeral for four is not IIII. Instead, the number four is
 * written as IV. Because the one is before the five we subtract it making
 * four. The same principle applies to the number nine, which is written as IX.
 * There are six instances where subtraction is used:
 * 
 * 
 * I can be placed before V (5) and X (10) to make 4 and 9. 
 * X can be placed before L (50) and C (100) to make 40 and 90. 
 * C can be placed before D (500) and M (1000) to make 400 and 900.
 * 
 * 
 * Given an integer, convert it to a roman numeral. Input is guaranteed to be
 * within the range from 1 to 3999.
 * 
 * Example 1:
 * 
 * 
 * Input: 3
 * Output: "III"
 * 
 * Example 2:
 * 
 * 
 * Input: 4
 * Output: "IV"
 * 
 * Example 3:
 * 
 * 
 * Input: 9
 * Output: "IX"
 * 
 * Example 4:
 * 
 * 
 * Input: 58
 * Output: "LVIII"
 * Explanation: L = 50, V = 5, III = 3.
 * 
 * 
 * Example 5:
 * 
 * 
 * Input: 1994
 * Output: "MCMXCIV"
 * Explanation: M = 1000, CM = 900, XC = 90 and IV = 4.
 * 
 */

#include <string>
#include <cassert>

using namespace std;

class Solution {
public:

    string intToRoman(int num) {
        string res = "";
        string dict[4][10] = {
                {"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"},
                {"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"},
                {"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"},
                {"", "M", "MM", "MMM"}
        };
        res += dict[3][num / 1000];
        res += dict[2][num / 100 % 10];
        res += dict[1][num / 10 % 10];
        res += dict[0][num % 10];
        return res;
    }

    string decode(int base, int val) {
        assert(base == 1 || base == 10 || base == 100 || base == 1000);
        assert(val >= 0 && val <= 9);
        string res = "";
        string one, two, three, five, ten;
        switch (base) {
            case 1:
                one = "I", two = "II", three = "III", five = 'V', ten = 'X';
                break;
            case 10:
                one = "X", two = "XX", three = "XXX", five = 'L', ten = 'C';
                break;
            case 100:
                one = "C", two = "CC", three = "CCC", five = 'D', ten = 'M';
                break;
            case 1000:
                one = 'M', two = "MM", three = "MMM";
                break;
        }
        switch (val) {
            case 0:
                return res;
            case 1:
                return res + one;
            case 2:
                return res + two;
            case 3:
                return res + three;
            case 4:
                return res + one + five;
            case 5:
                return res + five;
            case 6:
                return res + five + one;
            case 7:
                return res + five + two;
            case 8:
                return res + five + three;
            case 9:
                return res + one + ten;
        }
        return res;
    }

    string intToRoman1(int num) {
        string res = "";
        for (int base = 1000; base >= 1; base /= 10) {
            int val = num / base;
            num -= val * base;
            res += decode(base, val);
        }
        return res;
    }
};
