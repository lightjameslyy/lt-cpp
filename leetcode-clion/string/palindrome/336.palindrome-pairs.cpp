/*
 * @lc app=leetcode id=336 lang=cpp
 *
 * [336] Palindrome Pairs
 *
 * https://leetcode.com/problems/palindrome-pairs/description/
 *
 * algorithms
 * Hard (32.15%)
 * Total Accepted:    82.7K
 * Total Submissions: 257.2K
 * Testcase Example:  '["abcd","dcba","lls","s","sssll"]'
 *
 * Given a list of unique words, find all pairs of distinct indices (i, j) in
 * the given list, so that the concatenation of the two words, i.e. words[i] +
 * words[j] is a palindrome.
 * 
 * Example 1:
 * 
 * 
 * 
 * Input: ["abcd","dcba","lls","s","sssll"]
 * Output: [[0,1],[1,0],[3,2],[2,4]] 
 * Explanation: The palindromes are
 * ["dcbaabcd","abcddcba","slls","llssssll"]
 * 
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: ["bat","tab","cat"]
 * Output: [[0,1],[1,0]] 
 * Explanation: The palindromes are ["battab","tabbat"]
 * 
 * 
 * 
 * 
 */

#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    bool isPalindrome(const string &lhs, const string &rhs) {
        int llen = lhs.length(), rlen = rhs.length();
        int left = 0, right = rlen - 1;
        while (left < llen && right >= 0) {
            if (lhs[left++] != rhs[right--])
                return false;
        }
        if (left < llen) {
            right = llen - 1;
            while (left < right) {
                if (lhs[left++] != lhs[right--])
                    return false;
            }
        } else if (right >= 0) {
            left = 0;
            while (left < right) {
                if (rhs[left++] != rhs[right--])
                    return false;
            }
        }
        return true;
    }

    // brute force
    // 580ms, 18.4MB, 9.86%
    vector<vector<int>> palindromePairs_bf(vector<string> &words) {
        vector<vector<int>> res;
        for (int i = 0; i < words.size(); ++i) {
            for (int j = i + 1; j < words.size(); ++j) {
                if (i == j) continue;
                if (isPalindrome(words[i], words[j]))
                    res.push_back({i, j});
                if (isPalindrome(words[j], words[i]))
                    res.push_back({j, i});
            }
        }
        return res;
    }

    bool isPalindrome(const string &s) {
        int left = 0, right = s.length() - 1;
        while (left < right) {
            if (s[left++] != s[right--])
                return false;
        }
        return true;
    }

    // hash reversed string
    // 252ms, 45.8MB, 53.2%
    vector<vector<int>> palindromePairs(vector<string> &words) {
        unordered_map<string, int> indexMap;
        for (int i = 0; i < words.size(); ++i) {
            indexMap[string(words[i].rbegin(), words[i].rend())] = i;
        }

        vector<vector<int>> res;
        if (indexMap.find("") != indexMap.end()) {
            int emptyIndex = indexMap[""];
            for (int i = 0; i < words.size(); ++i) {
                if (i == emptyIndex) continue;
                if (isPalindrome(words[i])) {
                    res.push_back({emptyIndex, i});
                }
            }
        }

        for (int i = 0; i < words.size(); ++i) {
            for (int llen = 0; llen < words[i].size(); ++llen) {
                // r is not empty
                string l = words[i].substr(0, llen), r = words[i].substr(llen);
                if (indexMap.find(l) != indexMap.end() && isPalindrome(r) && indexMap[l] != i)
                    res.push_back({i, indexMap[l]});
                if (indexMap.find(r) != indexMap.end() && isPalindrome(l) && indexMap[r] != i)
                    res.push_back({indexMap[r], i});
            }
        }
        return res;
    }
};
