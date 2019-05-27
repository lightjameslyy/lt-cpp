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

#include <cstring>
#include <string>
#include <vector>
#include <unordered_map>
#include <utility>

using namespace std;

static const int COUNT_SIZE = 26;
static int counts[COUNT_SIZE];

class Solution {
public:
    string getKey(string str) {
        memset(counts, 0, sizeof(int) * COUNT_SIZE);
        string key = "";
        for (char c : str) {
            counts[c - 'a']++;
        }
        for (int i = 0; i < COUNT_SIZE; ++i) {
            if (counts[i]) {
                key += to_string(counts[i]);
                key += 'a' + i;
            }
        }
        return key;
    }

    vector<vector<string>> groupAnagrams(vector<string> strs) {
        vector<vector<string>> res;
        unordered_map<string, vector<string>> mp;
        for (auto &s : strs) {
            mp[getKey(s)].push_back(s);
        }
        for (auto &kv : mp) {
            res.push_back(move(kv.second));
        }
        return res;
    }
};
