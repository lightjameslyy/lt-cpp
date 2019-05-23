/*
 * @lc app=leetcode id=14 lang=cpp
 *
 * [14] Longest Common Prefix
 *
 * https://leetcode.com/problems/longest-common-prefix/description/
 *
 * algorithms
 * Easy (33.45%)
 * Total Accepted:    462.1K
 * Total Submissions: 1.4M
 * Testcase Example:  '["flower","flow","flight"]'
 *
 * Write a function to find the longest common prefix string amongst an array
 * of strings.
 * 
 * If there is no common prefix, return an empty string "".
 * 
 * Example 1:
 * 
 * 
 * Input: ["flower","flow","flight"]
 * Output: "fl"
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: ["dog","racecar","car"]
 * Output: ""
 * Explanation: There is no common prefix among the input strings.
 * 
 * 
 * Note:
 * 
 * All given inputs are in lowercase letters a-z.
 *
 */

#include <vector>

using namespace std;

class Solution {
public:
    string longestCommonPrefix1(vector<string> &strs) {
        int size = strs.size();
        if (size == 0)
            return "";
        if (size == 1)
            return strs[0];
        int count = 0;
        for (int i = 0; i < strs[0].length(); ++i) {
            for (int j = 1; j < size; ++j) {
                if (i >= strs[j].length() || strs[j][i] != strs[0][i]) {
                    return strs[0].substr(0, count);
                }
            }
            count++;
        }
        return strs[0].substr(0, count);
    }

    string longestCommonPrefix(vector<string> &strs) {
        if (strs.empty())
            return "";
        char *res = const_cast<char *>(strs[0].c_str());
        for (int i = 1; i < strs.size(); ++i) {
            int j = 0;
            for (; res[j] && strs[i][j]; ++j) {
                if (res[j] != strs[i][j])
                    break;
            }
            res[j] = '\0';
        }
        return res;
    }
};
