/*
 * @lc app=leetcode id=214 lang=cpp
 *
 * [214] Shortest Palindrome
 *
 * https://leetcode.com/problems/shortest-palindrome/description/
 *
 * algorithms
 * Hard (28.37%)
 * Total Accepted:    83.1K
 * Total Submissions: 293.1K
 * Testcase Example:  '"aacecaaa"'
 *
 * Given a string s, you are allowed to convert it to a palindrome by adding
 * characters in front of it. Find and return the shortest palindrome you can
 * find by performing this transformation.
 * 
 * Example 1:
 * 
 * 
 * Input: "aacecaaa"
 * Output: "aaacecaaa"
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: "abcd"
 * Output: "dcbabcd"
 */

/*
 * idea:
 * 1. find longest palindrome substring s[0,pos]
 * 2. prepend with reverse(s.substr(pos+1))
 */

#include <algorithm>

using namespace std;

class Solution {
public:

    bool isPalindrom(const string &s, int left, int right) {
        while (left < right) {
            if (s[left++] != s[right--])
                return false;
        }
        return true;
    }

    string shortestPalindrome_tle(string s) {
        int slen = s.length();
        if (slen < 2) return s;
        int maxLen = 0;
        for (int i = 0; i < slen; ++i) {
            while (isPalindrom(s, 0, i)) {
                ++i;
            }
            maxLen = i;
        }
        string preStr = s.substr(maxLen);
        reverse(preStr.begin(), preStr.end());
        return preStr + s;
    }

    bool equal(const string &s1, const string &s2, int pos1, int pos2, int len) {
        for (int i = 0; i < len; ++i) {
            if (s1[pos1 + i] != s2[pos2 + i])
                return false;
        }
        return true;
    }

    // using reverse string
    string shortestPalindrome(string s) {
        int slen = s.length();
        if (slen < 2) return s;
        string rev = s;
        reverse(rev.begin(), rev.end());
        for (int i = 0; i < slen; ++i) {
            //if (s.substr(0, slen - i) == rev.substr(i))
            if (equal(s, rev, 0, i, slen - i))
                return rev.substr(0, i) + s;
        }
        return "";
    }
};
