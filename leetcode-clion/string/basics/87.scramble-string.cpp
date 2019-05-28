/*
 * @lc app=leetcode id=87 lang=cpp
 *
 * [87] Scramble String
 *
 * https://leetcode.com/problems/scramble-string/description/
 *
 * algorithms
 * Hard (31.57%)
 * Total Accepted:    90.3K
 * Total Submissions: 285.9K
 * Testcase Example:  '"great"\n"rgeat"'
 *
 * Given a string s1, we may represent it as a binary tree by partitioning it
 * to two non-empty substrings recursively.
 * 
 * Below is one possible representation of s1 = "great":
 * 
 * 
 * ⁠   great
 * ⁠  /    \
 * ⁠ gr    eat
 * ⁠/ \    /  \
 * g   r  e   at
 * ⁠          / \
 * ⁠         a   t
 * 
 * 
 * To scramble the string, we may choose any non-leaf node and swap its two
 * children.
 * 
 * For example, if we choose the node "gr" and swap its two children, it
 * produces a scrambled string "rgeat".
 * 
 * 
 * ⁠   rgeat
 * ⁠  /    \
 * ⁠ rg    eat
 * ⁠/ \    /  \
 * r   g  e   at
 * ⁠          / \
 * ⁠         a   t
 * 
 * 
 * We say that "rgeat" is a scrambled string of "great".
 * 
 * Similarly, if we continue to swap the children of nodes "eat" and "at", it
 * produces a scrambled string "rgtae".
 * 
 * 
 * ⁠   rgtae
 * ⁠  /    \
 * ⁠ rg    tae
 * ⁠/ \    /  \
 * r   g  ta  e
 * ⁠      / \
 * ⁠     t   a
 * 
 * 
 * We say that "rgtae" is a scrambled string of "great".
 * 
 * Given two strings s1 and s2 of the same length, determine if s2 is a
 * scrambled string of s1.
 * 
 * Example 1:
 * 
 * 
 * Input: s1 = "great", s2 = "rgeat"
 * Output: true
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: s1 = "abcde", s2 = "caebd"
 * Output: false
 * 
 */

/*
 * 思路：递归
 */

using namespace std;

class Solution {
public:
    bool isAnagram(string &s, string &t) {
        vector<int> counts(26, 0);
        for (char c : s) {
            counts[c - 'a']++;
        }
        for (char c : t) {
            counts[c - 'a']--;
        }
        for (int i = 0; i < 26; ++i) {
            if (counts[i] != 0)
                return false;
        }
        return true;
    }

    bool isScramble(string s1, string s2) {
        if (s1.empty() || s2.empty() || s1.length() != s2.length()) return false;
        if (s1.length() == 1 && s1 == s2) return true;
        if (isAnagram(s1, s2) == false) return false;
        for (int len = 1; len < s1.length(); len++) {
            string str_left = s1.substr(0, len);
            string str_right = s1.substr(len);
            if ((isScramble(str_left, s2.substr(0, len)) && isScramble(str_right, s2.substr(len))) ||
                (isScramble(str_left, s2.substr(s2.length() - len)) &&
                 isScramble(str_right, s2.substr(0, s2.length() - len))))
                return true;
        }
        return false;
    }
};
