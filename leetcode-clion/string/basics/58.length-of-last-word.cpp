/*
 * @lc app=leetcode id=58 lang=cpp
 *
 * [58] Length of Last Word
 *
 * https://leetcode.com/problems/length-of-last-word/description/
 *
 * algorithms
 * Easy (32.26%)
 * Total Accepted:    266.3K
 * Total Submissions: 825.5K
 * Testcase Example:  '"Hello World"'
 *
 * Given a string s consists of upper/lower-case alphabets and empty space
 * characters ' ', return the length of last word in the string.
 * 
 * If the last word does not exist, return 0.
 * 
 * Note: A word is defined as a character sequence consists of non-space
 * characters only.
 * 
 * Example:
 * 
 * 
 * Input: "Hello World"
 * Output: 5
 * 
 * 
 * 
 * 
 */

using namespace std;

class Solution {
public:
    int lengthOfLastWord(string s) {
        int res = 0;
        int i = s.length() - 1;
        while (s[i] == ' ') {
            --i;
        }
        for (; i >= 0; --i) {
            if (s[i] == ' ') {
                return res;
            } else {
                res++;
            }
        }
        return res;
    }
};
