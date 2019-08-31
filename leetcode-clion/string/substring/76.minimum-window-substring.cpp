/*
 * @lc app=leetcode id=76 lang=cpp
 *
 * [76] Minimum Window Substring
 *
 * https://leetcode.com/problems/minimum-window-substring/description/
 *
 * algorithms
 * Hard (30.76%)
 * Total Accepted:    265.6K
 * Total Submissions: 837.5K
 * Testcase Example:  '"ADOBECODEBANC"\n"ABC"'
 *
 * Given a string S and a string T, find the minimum window in S which will
 * contain all the characters in T in complexity O(n).
 * 
 * Example:
 * 
 * 
 * Input: S = "ADOBECODEBANC", T = "ABC"
 * Output: "BANC"
 * 
 * 
 * Note:
 * 
 * 
 * If there is no such window in S that covers all characters in T, return the
 * empty string "".
 * If there is such window, you are guaranteed that there will always be only
 * one unique minimum window in S.
 * 
 * 
 */

#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    string minWindow(string s, string t) {
        if (s.length() < t.length() || t.empty()) return "";
        vector<int> tmap(128, 0), smap(128, 0);
        int uniqs = 0, included = 0;
        // build map for t
        for (char c : t) tmap[c]++;
        for (int count : tmap) uniqs += (count != 0);
        // find first right pos that s[0, right] holds t
        int right = -1;
        for (int i = 0; i < s.length(); ++i) {
            smap[s[i]]++;
            if (smap[s[i]] == tmap[s[i]] && ++included == uniqs) {
                right = i;
                break;
            }
        }
        if (right == -1) return "";
        int left = 0;
        int res_left = left, res_right = right;
        // slide window
        for (; right < s.length();) {
            // move left forward to shrink
            for (; left <= right; ++left) {
                if (tmap[s[left]]) {
                    if (smap[s[left]] > tmap[s[left]]) {
                        smap[s[left]]--;
                    } else // ==
                        break;
                }
            }
            // update window
            if (right - left < res_right - res_left)
                res_left = left, res_right = right;
            // if optimal, return
            if (res_right - res_left + 1 == t.length())
                return s.substr(res_left, res_right - res_left + 1);
            char lost = s[left++];
            // move right forward to find lost
            for (++right; right < s.length(); ++right) {
                if (s[right] == lost)
                    break;
                smap[s[right]]++;
            }
        }
        return s.substr(res_left, res_right - res_left + 1);
    }
};
