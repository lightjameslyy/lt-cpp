/*
 * @lc app=leetcode id=30 lang=cpp
 *
 * [30] Substring with Concatenation of All Words
 *
 * https://leetcode.com/problems/substring-with-concatenation-of-all-words/description/
 *
 * algorithms
 * Hard (23.57%)
 * Total Accepted:    143.8K
 * Total Submissions: 597.7K
 * Testcase Example:  '"barfoothefoobarman"\n["foo","bar"]'
 *
 * You are given a string, s, and a list of words, words, that are all of the
 * same length. Find all starting indices of substring(s) in s that is a
 * concatenation of each word in words exactly once and without any intervening
 * characters.
 * 
 * Example 1:
 * 
 * 
 * Input:
 * ⁠ s = "barfoothefoobarman",
 * ⁠ words = ["foo","bar"]
 * Output: [0,9]
 * Explanation: Substrings starting at index 0 and 9 are "barfoor" and "foobar"
 * respectively.
 * The output order does not matter, returning [9,0] is fine too.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input:
 * ⁠ s = "wordgoodgoodgoodbestword",
 * ⁠ words = ["word","good","best","word"]
 * Output: []
 * 
 * 
 */

/*
 * ideas: hash table + sliding window
 * see my leetcode submission for a better solution: inner i, outer j
 */

#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<int> findSubstring(string s, vector<string> &words) {
        vector<int> res;
        if (words.empty() || words[0].empty() || s.empty())
            return res;
        int kWordLen = words[0].length();
        int kWordCount = words.size();
        int kFitLen = kWordLen * kWordCount;
        int sLen = s.length();
        // 1. get word count
        unordered_map<string, int> wordsMap;
        for (const string &word: words)
            wordsMap[word]++;

        // 2. sliding window
        for (int i = 0; i <= sLen - kFitLen; ++i) {
            unordered_map<string, int> tmpMap;
            int j = 0;
            for (; j < kWordCount; ++j) {
                string curWord = s.substr(i+j*kWordLen, kWordLen);
                if (tmpMap[curWord] == wordsMap[curWord]) { // curWord exceeded
                    break;
                } else {
                    tmpMap[curWord]++;
                }
            }
            if (j == kWordCount) {
                res.push_back(i);
            }
        }
        return res;
    }
};
