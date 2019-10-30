/*
 * @lc app=leetcode id=395 lang=cpp
 *
 * [395] Longest Substring with At Least K Repeating Characters
 *
 * https://leetcode.com/problems/longest-substring-with-at-least-k-repeating-characters/description/
 *
 * algorithms
 * Medium (39.66%)
 * Total Accepted:    57.5K
 * Total Submissions: 145K
 * Testcase Example:  '"aaabb"\n3'
 *
 * 
 * Find the length of the longest substring T of a given string (consists of
 * lowercase letters only) such that every character in T appears no less than
 * k times.
 * 
 * 
 * Example 1:
 * 
 * Input:
 * s = "aaabb", k = 3
 * 
 * Output:
 * 3
 * 
 * The longest substring is "aaa", as 'a' is repeated 3 times.
 * 
 * 
 * 
 * Example 2:
 * 
 * Input:
 * s = "ababbc", k = 2
 * 
 * Output:
 * 5
 * 
 * The longest substring is "ababb", as 'a' is repeated 2 times and 'b' is
 * repeated 3 times.
 * 
 * 
 */

/*
 * idea: hash + sliding window
 *      window size: ws = [k, sLen]
 */

#include <unordered_map>
#include <unordered_set>
#include <vector>

class Solution {
public:
    bool fit(const string &s, int startPos, int endPos, int k) {
        unordered_map<char, int> countMap;
        for (int i = startPos; i < endPos; ++i) {
            countMap[s[i]]++;
        }
        for (auto kv : countMap) {
            if (kv.second < k)
                return false;
        }
        return true;
    }

    // Time Limit Exceeded
    int longestSubstring_tle(string s, int k) {
        int res = 0;
        int sLen = s.length();
        if (k > sLen || sLen == 0)
            return 0;
        if (k < 2)
            return sLen;
        for (int ws = k; ws <= sLen; ++ws) {
            int startPos = 0;
            for (; startPos <= sLen - ws; ++startPos) {
                if (fit(s, startPos, startPos + ws, k) == true) {
                    res = ws;
                    break;
                }
            }
        }
        return res;
    }

    bool fit(const unordered_map<char, int> &countMap, int k) {
        for (auto kv : countMap) {
            if (kv.second > 0 && kv.second < k)
                return false;
        }
        return true;
    }

    // Time Limit Exceeded
    int longestSubstring_tle1(string s, int k) {
        int res = 0;
        int sLen = s.length();
        if (k > sLen || sLen == 0)
            return 0;
        if (k < 2)
            return sLen;
        for (int ws = k; ws <= sLen; ++ws) {
            int startPos = 0;
            unordered_map<char, int> countMap;
            for (int i = startPos; i < startPos + ws; ++i) {
                countMap[s[i]]++;
            }
            for (; startPos <= sLen - ws; ++startPos) {
                if (startPos > 0) {
                    char preChar = s[startPos - 1];
                    char nextChar = s[startPos + ws - 1];
                    countMap[preChar]--;
                    countMap[nextChar]++;
                }
                if (fit(countMap, k) == true) {
                    res = ws;
                    break;
                }
            }
        }
        return res;
    }

    void helper(const string &s, int pos, int len, int k, int &res) {
        if (k > len || res >= len)
            return;
        if (k < 2) {
            res = len;
            return;
        }
        // 1. statistics appearance for each char
        vector<int> countAllMap(26, 0);
        for (int i = pos; i < pos + len; ++i) {
            countAllMap[s[i] - 'a']++;
        }
        bool hasInsufficiency = false;
        for (int count : countAllMap) {
            if (count != 0 && count < k) {
                hasInsufficiency = true;
                break;
            }
        }
        if (hasInsufficiency == false) {
            res = len;
            return;
        }
        vector<int> splits;
        splits.push_back(pos - 1);
        for (int i = pos; i < pos + len; ++i) {
            if (countAllMap[s[i] - 'a'] < k)
                splits.push_back(i);
        }
        splits.push_back(pos + len);
        for (int i = 0; i < splits.size() - 1; ++i) {
            helper(s, splits[i] + 1, splits[i + 1] - splits[i] - 1, k, res);
        }
    }

    // 4 ms	8.7 MB 83.10%
    int longestSubstring_my(string s, int k) {
        int res = 0;
        int sLen = s.length();
        helper(s, 0, sLen, k, res);
        return res;
    }

    // copied: 0 ms 8.8 MB 100%
    int longestSubstring(string s, int k) {
        int n = (int) s.length();
        int count[26] = {0};
        for (char c : s) ++count[c - 'a'];
        int mid = 0;
        while (mid < n && count[s[mid] - 'a'] >= k) ++mid;
        if (mid == n) return n;
        int left = longestSubstring(s.substr(0, mid), k);
        while (mid < n && count[s[mid] - 'a'] < k) ++mid;
        int right = longestSubstring(s.substr(mid), k);
        return max(left, right);
    }

};
