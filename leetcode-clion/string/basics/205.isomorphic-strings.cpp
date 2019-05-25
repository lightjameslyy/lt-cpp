/*
 * @lc app=leetcode id=205 lang=cpp
 *
 * [205] Isomorphic Strings
 *
 * https://leetcode.com/problems/isomorphic-strings/description/
 *
 * algorithms
 * Easy (37.30%)
 * Total Accepted:    202.3K
 * Total Submissions: 542.2K
 * Testcase Example:  '"egg"\n"add"'
 *
 * Given two strings s and t, determine if they are isomorphic.
 * 
 * Two strings are isomorphic if the characters in s can be replaced to get t.
 * 
 * All occurrences of a character must be replaced with another character while
 * preserving the order of characters. No two characters may map to the same
 * character but a character may map to itself.
 * 
 * Example 1:
 * 
 * 
 * Input: s = "egg", t = "add"
 * Output: true
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: s = "foo", t = "bar"
 * Output: false
 * 
 * Example 3:
 * 
 * 
 * Input: s = "paper", t = "title"
 * Output: true
 * 
 * Note:
 * You may assume both s and t have the same length.
 * 
 */

#include <vector>
#include <cassert>

using namespace std;

class Solution {
public:
    bool isIsomorphic(string s, string t) {
        assert(s.length() == t.length());
        vector<char> s_map(256, '\0'), t_map(256, '\0');
        for (size_t i = 0; i < s.length(); ++i) {
            if (s_map[s[i]] == '\0' && t_map[t[i]] == '\0') {
                s_map[s[i]] = t[i];
                t_map[t[i]] = s[i];
            } else if (s_map[s[i]] != t[i] || t_map[t[i]] != s[i]) {
                return false;
            }
        }
        return true;
    }
};
