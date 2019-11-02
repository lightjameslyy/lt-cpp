/*
 * @lc app=leetcode id=267 lang=cpp
 *
 * [267] Palindrome Permutation II
 *
 * https://leetcode.com/problems/palindrome-permutation-ii/description/
 *
 * algorithms
 * Medium (34.70%)
 * Total Accepted:    30.2K
 * Total Submissions: 87.1K
 * Testcase Example:  '"aabb"'
 *
 * Given a string s, return all the palindromic permutations (without
 * duplicates) of it. Return an empty list if no palindromic permutation could
 * be form.
 * 
 * Example 1:
 * 
 * 
 * Input: "aabb"
 * Output: ["abba", "baab"]
 * 
 * Example 2:
 * 
 * 
 * Input: "abc"
 * Output: []
 * 
 */

#include <vector>

using namespace std;

class Solution {
public:
    void helper(const string &s, string &center, string cur, int len, vector<string> &res) {
        if (cur.length() == len) {
            res.push_back(cur + center + string(cur.rbegin(), cur.rend()));
            return;
        }
        for (int i = 0; i < s.length(); ++i) {
            cur += s[i];
            helper(s.substr(0, i) + s.substr(i + 1), center, cur, len, res);
            cur.pop_back();
            // NOTE: take care of duplicates
            while (i + 1 < s.length() && s[i] == s[i + 1])
                ++i;
        }
    }

    // backtracking
    // 0ms, 8.7MB, 100%
    vector<string> generatePalindromes(string s) {
        int len = s.length();
        vector<string> res;
        string center = "";
        // validate
        int charCount[128] = {0};
        for (char c : s)
            charCount[c]++;
        string minLeft = "";
        for (int i = 0; i < 128; ++i) {
            if (charCount[i] % 2) {
                center.append(1, i);
            }
            if (center.length() > 1)
                return res;
            minLeft.append(charCount[i] / 2, i);
        }
        // generate left side permutations from minLeft to maxLeft
        helper(minLeft, center, "", minLeft.length(), res);

        return res;
    }
};
