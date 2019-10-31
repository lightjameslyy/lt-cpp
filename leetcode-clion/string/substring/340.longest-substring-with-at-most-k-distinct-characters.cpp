/*
 * @lc app=leetcode id=340 lang=cpp
 *
 * [340] Longest Substring with At Most K Distinct Characters
 *
 * https://leetcode.com/problems/longest-substring-with-at-most-k-distinct-characters/description/
 *
 * algorithms
 * Hard (41.48%)
 * Total Accepted:    93.3K
 * Total Submissions: 224.9K
 * Testcase Example:  '"eceba"\n2'
 *
 * Given a string, find the length of the longest substring T that contains at
 * most k distinct characters.
 * 
 * Example 1:
 * 
 * 
 * 
 * Input: s = "eceba", k = 2
 * Output: 3
 * Explanation: T is "ece" which its length is 3.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: s = "aa", k = 1
 * Output: 2
 * Explanation: T is "aa" which its length is 2.
 * 
 * 
 * 
 */

#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
public:
    // 16 ms 9.7 MB 72.13%
    int lengthOfLongestSubstringKDistinct_my(string s, int k) {
        int sLen = s.length();
        if (sLen == 0 || k == 0) {
            return 0;
        }
        if (sLen <= k || k >= 256)
            return sLen;
        int res = 0;
        unordered_map<char, int> charMap;
        int startPos = 0, endPos = 0;
        while (endPos < sLen) {
            if (res >= sLen - startPos)
                break;
            while (endPos < sLen) {
                charMap[s[endPos]]++;
                if (charMap.size() > k)
                    break;
                endPos++;
            }
            res = max(res, endPos - startPos);
//            cout << "\"" << s.substr(startPos, res) << "\"" << endl;
            if (endPos == sLen)
                break;
            endPos++;
            while (endPos - startPos < res && endPos < sLen) {
                charMap[s[endPos++]]++;
            }
            while (startPos < endPos) {
                char delChar = s[startPos++];
                if (--charMap[delChar] == 0) {
                    charMap.erase(delChar);
                }
                if (charMap.size() <= k)
                    break;
            }
        }
        return res;
    }

    // copied: 8 ms 9.1 MB 93.03%
    int lengthOfLongestSubstringKDistinct(string s, int k) {
        int left = 0;
        vector<int> map(128, 0);
        int maxLen = 0;
        int cnt = 0;
        for (int right = 0; right < s.size(); right++) {
            if (map[s[right]]++ == 0) cnt++;
            while (cnt > k) {
                if (--map[s[left]] == 0) cnt--;
                left++;
            }
            maxLen = max(maxLen, (right - left + 1));
        }
        return maxLen;
    }
};
