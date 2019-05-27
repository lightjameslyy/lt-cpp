/*
 * @lc app=leetcode id=49 lang=cpp
 *
 * [49] Group Anagrams
 *
 * https://leetcode.com/problems/group-anagrams/description/
 *
 * algorithms
 * Medium (46.64%)
 * Total Accepted:    334.4K
 * Total Submissions: 716.8K
 * Testcase Example:  '["eat","tea","tan","ate","nat","bat"]'
 *
 * Given an array of strings, group anagrams together.
 * 
 * Example:
 * 
 * 
 * Input: ["eat", "tea", "tan", "ate", "nat", "bat"],
 * Output:
 * [
 * ⁠ ["ate","eat","tea"],
 * ⁠ ["nat","tan"],
 * ⁠ ["bat"]
 * ]
 * 
 * Note:
 * 
 * 
 * All inputs will be in lowercase.
 * The order of your output does not matter.
 * 
 * 
 */

#include <vector>

using namespace std;

class Solution {
public:
    bool isAnagram(string s, string t) {
        vector<int> count_s(26, 0), count_t(26, 0);
        for (char c : s) {
            count_s[c - 'a']++;
        }
        for (char c : t) {
            count_t[c - 'a']++;
        }
        for (int i = 0; i < 26; ++i) {
            if (count_s[i] != count_t[i])
                return false;
        }
        return true;
    }

    vector<vector<string>> groupAnagrams(vector<string> strs) {
        vector<vector<string>> res;
        for (int i = 0; i < strs.size(); ++i) {
            bool flag = false;
            for (int j = 0; j < res.size(); ++j) {
                if (isAnagram(strs[i], res[j][0])) {
                    res[j].push_back(strs[i]);
                    flag = true;
                }
            }
            if (flag == false) {
                res.push_back({strs[i]});
            }
        }
        return res;
    }
};
