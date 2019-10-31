/*
 * @lc app=leetcode id=159 lang=cpp
 *
 * [159] Longest Substring with At Most Two Distinct Characters
 *
 * https://leetcode.com/problems/longest-substring-with-at-most-two-distinct-characters/description/
 *
 * algorithms
 * Hard (48.15%)
 * Total Accepted:    83.1K
 * Total Submissions: 172.6K
 * Testcase Example:  '"eceba"'
 *
 * Given a string s , find the length of the longest substring t  that contains
 * at most 2 distinct characters.
 * 
 * Example 1:
 * 
 * 
 * Input: "eceba"
 * Output: 3
 * Explanation: t is "ece" which its length is 3.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: "ccaabbb"
 * Output: 5
 * Explanation: t is "aabbb" which its length is 5.
 * 
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    // hash + sliding window
    // 8ms, 9.1MB, 75.44%
    int lengthOfLongestSubstringTwoDistinct(string s) {
        int maxLen = 0;
        int left = 0;
        vector<int> charMap(256, 0);
        int cnt = 0;
        for (int right = 0; right < s.length(); ++right) {
            if (charMap[s[right]]++ == 0)
                cnt++;
            while (cnt > 2) {
                if (--charMap[s[left]] == 0)
                    cnt--;
                left++;
            }
            maxLen = max(maxLen, right - left + 1);
        }
        return maxLen;
    }
};
