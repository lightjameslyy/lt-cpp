/*
 * @lc app=leetcode id=3 lang=cpp
 *
 * [3] Longest Substring Without Repeating Characters
 *
 * https://leetcode.com/problems/longest-substring-without-repeating-characters/description/
 *
 * algorithms
 * Medium (29.04%)
 * Total Accepted:    1.2M
 * Total Submissions: 4M
 * Testcase Example:  '"abcabcbb"'
 *
 * Given a string, find the length of the longest substring without repeating
 * characters.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: "abcabcbb"
 * Output: 3 
 * Explanation: The answer is "abc", with the length of 3. 
 * 
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: "bbbbb"
 * Output: 1
 * Explanation: The answer is "b", with the length of 1.
 * 
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: "pwwkew"
 * Output: 3
 * Explanation: The answer is "wke", with the length of 3. 
 * ⁠            Note that the answer must be a substring, "pwke" is a
 * subsequence and not a substring.
 * 
 * 
 * 
 * 
 * 
 */

/*
 * ideas: sliding window
 */

#include <unordered_set>
#include <vector>
#include <algorithm>

class Solution {
public:
    // faster: using hash to store last position of a char
    int lengthOfLongestSubstring(string s) {
        int maxLen = 0;
        int sLen = s.length();
        vector<int> posMap(256, -1);
        int startPos = 0;
        for (int i = 0; i < sLen; ++i) {
            if (posMap[s[i]] != -1 && posMap[s[i]] >= startPos) {
                maxLen = max(maxLen, i - startPos);
                startPos = posMap[s[i]] + 1;
            }
            posMap[s[i]] = i;
        }
        maxLen = max(maxLen, sLen - startPos);
        return maxLen;
    }

    // slower: using unordered_set to store current window
    int lengthOfLongestSubstring1(string s) {
        int maxLen = 0;
        unordered_set<char> charSet;
        int startPos = 0;
        for (int i = 0; i < s.length(); ++i) {
            if (charSet.find(s[i]) != charSet.end()) {
                maxLen = (maxLen > charSet.size()) ? maxLen : charSet.size();
                for (int j = startPos; j < i; ++j) {
                    charSet.erase(s[j]);
                    if (s[j] == s[i]) {
                        startPos = j + 1;
                        break;
                    }
                }
            }
            charSet.insert(s[i]);
        }
        maxLen = (maxLen > charSet.size()) ? maxLen : charSet.size();
        return maxLen;
    }
};
