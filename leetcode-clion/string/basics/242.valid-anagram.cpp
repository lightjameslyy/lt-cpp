/*
 * @lc app=leetcode id=242 lang=cpp
 *
 * [242] Valid Anagram
 *
 * https://leetcode.com/problems/valid-anagram/description/
 *
 * algorithms
 * Easy (52.11%)
 * Total Accepted:    337.5K
 * Total Submissions: 647.7K
 * Testcase Example:  '"anagram"\n"nagaram"'
 *
 * Given two strings s and t , write a function to determine if t is an anagram
 * of s.
 * 
 * Example 1:
 * 
 * 
 * Input: s = "anagram", t = "nagaram"
 * Output: true
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: s = "rat", t = "car"
 * Output: false
 * 
 * 
 * Note:
 * You may assume the string contains only lowercase alphabets.
 * 
 * Follow up:
 * What if the inputs contain unicode characters? How would you adapt your
 * solution to such case?
 * 
 */

#include <vector>

using namespace std;

class Solution {
public:
    bool isAnagram(string s, string t) {
        vector<int> count_s(256, 0), count_t(256, 0);
        for (char c : s) {
            count_s[c]++;
        }
        for (char c : t) {
            count_t[c]++;
        }
        for (int i = 'a'; i <= 'z'; ++i) {
            if (count_s[i] != count_t[i])
                return false;
        }
        return true;
    }
};
