/*
 * @lc app=leetcode id=316 lang=cpp
 *
 * [316] Remove Duplicate Letters
 *
 * https://leetcode.com/problems/remove-duplicate-letters/description/
 *
 * algorithms
 * Hard (31.91%)
 * Total Accepted:    61.5K
 * Total Submissions: 185K
 * Testcase Example:  '"bcabc"'
 *
 * Given a string which contains only lowercase letters, remove duplicate
 * letters so that every letter appears once and only once. You must make sure
 * your result is the smallest in lexicographical order among all possible
 * results.
 * 
 * Example 1:
 * 
 * 
 * Input: "bcabc"
 * Output: "abc"
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: "cbacdcbc"
 * Output: "acdb"
 * 
 * 
 */

#include <vector>
#include <bitset>

using namespace std;

class Solution {
public:
    string removeDuplicateLetters(string s) {
        string res = "";
        vector<int> count('a' + 26, 0);
        bitset<'a' + 26> used;
        for (char c : s)
            count[c]++;

        for (char c : s) {
            count[c]--;
            if (used[c])
                continue;
            while (!res.empty() && res.back() > c && count[res.back()] > 0) {
                used[res.back()] = false;
                res.pop_back();
            }
            res += c;
            used[c] = true;
        }
        return res;
    }

    string removeDuplicateLetters1(string s) {
        string res = "";
        // hash letters to their indexes
        vector<vector<int>> indexesMap('a' + 26);
        for (int i = 0; i < s.length(); ++i) {
            indexesMap[s[i]].push_back(i);
        }
        string allChars = "";
        for (char i = 'a'; i <= 'z'; ++i) {
            if (!indexesMap[i].empty())
                allChars += i;
        }
        int curPos = 0;
        while (!allChars.empty()) {
            int minPos = s.length();
            for (char c : allChars)
                minPos = min(minPos, indexesMap[c].back());
            for (int i = 0; i < allChars.length(); ++i) {
                char c = allChars[i];
                auto &vec = indexesMap[c];
                auto low = lower_bound(vec.begin(), vec.end(), curPos);
                if (*low <= minPos) {
                    curPos = *low;
                    res += c;
                    allChars.erase(i, 1);
                    break;
                }
            }
        }
        return res;
    }
};
