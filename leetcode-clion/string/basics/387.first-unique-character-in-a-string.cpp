/*
 * @lc app=leetcode id=387 lang=cpp
 *
 * [387] First Unique Character in a String
 *
 * https://leetcode.com/problems/first-unique-character-in-a-string/description/
 *
 * algorithms
 * Easy (49.98%)
 * Total Accepted:    265.7K
 * Total Submissions: 531.6K
 * Testcase Example:  '"leetcode"'
 *
 * 
 * Given a string, find the first non-repeating character in it and return it's
 * index. If it doesn't exist, return -1.
 * 
 * Examples:
 * 
 * s = "leetcode"
 * return 0.
 * 
 * s = "loveleetcode",
 * return 2.
 * 
 * 
 * 
 * 
 * Note: You may assume the string contain only lowercase letters.
 * 
 */

#include <vector>

using namespace std;

class Solution {
public:
    int firstUniqChar1(string s) {
        long long res = 1LL << 40;
        vector<int> counts(128, 0), pos(128, 0);
        for (int i = s.length(); i >= 0; --i) {
            counts[s[i]]++;
            pos[s[i]] = i;
        }
        for (int i = 'a'; i <= 'z'; ++i) {
            if (counts[i] == 1 && pos[i] < res)
                res = pos[i];
        }
        if (res < 1LL << 40) {
            return res;
        }
        return -1;
    }

    int firstUniqChar(string s) {
        vector<int> counts('z'+1, 0);
        for (int i = 0; i < s.length(); ++i) {
            counts[s[i]]++;
        }
        for (int i = 0; i < s.length(); ++i) {
            if (counts[s[i]] == 1)
                return i;
        }
        return -1;
    }
};
