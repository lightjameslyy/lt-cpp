/*
 * @lc app=leetcode id=28 lang=cpp
 *
 * [28] Implement strStr()
 *
 * https://leetcode.com/problems/implement-strstr/description/
 *
 * algorithms
 * Easy (31.93%)
 * Total Accepted:    423.9K
 * Total Submissions: 1.3M
 * Testcase Example:  '"hello"\n"ll"'
 *
 * Implement strStr().
 * 
 * Return the index of the first occurrence of needle in haystack, or -1 if
 * needle is not part of haystack.
 * 
 * Example 1:
 * 
 * 
 * Input: haystack = "hello", needle = "ll"
 * Output: 2
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: haystack = "aaaaa", needle = "bba"
 * Output: -1
 * 
 * 
 * Clarification:
 * 
 * What should we return when needle is an empty string? This is a great
 * question to ask during an interview.
 * 
 * For the purpose of this problem, we will return 0 when needle is an empty
 * string. This is consistent to C's strstr() and Java's indexOf().
 * 
 */

/*
 * 思路：KMP算法。
 * 参考《编程之法》p131-p151
 */

#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    vector<int> getNext(string P) {
        int len = P.length();
        if (len == 0)
            return vector<int>();
        vector<int> next(len, 0);
        next[0] = -1;
        int k = -1, j = 1;
        while (j < len) {
            if (k == -1 || P[j - 1] == P[k]) {
                next[j] = ++k;
                if (P[j] == P[k]) {
                    next[j] = next[k];
                }
                j++;
            } else {
                k = next[k];
            }
        }
        return next;
    }

    int strStr(string haystack, string needle) {
        int lenh = haystack.length();
        int lenn = needle.length();
        if (lenn > lenh)
            return -1;
        vector<int> next = getNext(needle);
        int i = 0, j = 0;
        while (i < lenh && j < lenn) {
            if (j == -1 || haystack[i] == needle[j]) {
                i++;
                j++;
            } else {
                j = next[j];
            }
        }
        if (j == lenn)
            return i - j;
        return -1;
    }
};
