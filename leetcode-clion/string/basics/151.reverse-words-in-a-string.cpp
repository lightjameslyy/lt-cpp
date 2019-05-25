/*
 * @lc app=leetcode id=151 lang=cpp
 *
 * [151] Reverse Words in a String
 *
 * https://leetcode.com/problems/reverse-words-in-a-string/description/
 *
 * algorithms
 * Medium (16.70%)
 * Total Accepted:    279.6K
 * Total Submissions: 1.7M
 * Testcase Example:  '"the sky is blue"'
 *
 * Given an input string, reverse the string word by word.
 * 
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: "the sky is blue"
 * Output: "blue is sky the"
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: "  hello world!  "
 * Output: "world! hello"
 * Explanation: Your reversed string should not contain leading or trailing
 * spaces.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: "a good   example"
 * Output: "example good a"
 * Explanation: You need to reduce multiple spaces between two words to a
 * single space in the reversed string.
 * 
 * 
 * 
 * 
 * Note:
 * 
 * 
 * A word is defined as a sequence of non-space characters.
 * Input string may contain leading or trailing spaces. However, your reversed
 * string should not contain leading or trailing spaces.
 * You need to reduce multiple spaces between two words to a single space in
 * the reversed string.
 * 
 * 
 * 
 * 
 * Follow up:
 * 
 * For C programmers, try to solve it in-place in O(1) extra space.
 */

/*
 * 思路：先整体reverse，然后逐个reverse
 */

using namespace std;

#include <cctype>
#include <cstring>

class Solution {
public:
    void reverse(string &s, int left, int right) {
        for (int i = 0; i <= (right - left - 1) / 2; ++i) {
            swap(s[left + i], s[right - i]);
        }
    }

    void getNextWordPos(const string &s, int &start, int &end) {
        while (start < s.length() && isspace(s[start]))
            start++;
        end = start + 1;
        while (end < s.length() && !isspace(s[end]))
            end++;
    }

    string reverseWords(string s) {
        // 1. 将所有连续space字符变为一个空格
        int start = 0, end = 0;
        int new_len = -1;
        while (start < s.length()) {
            getNextWordPos(s, start, end);
            if (start >= s.length()) {
                break;
            }
            new_len++;
            if (start > new_len) {
                for (int j = start; j < end; ++j) {
                    s[new_len++] = s[j];
                }
                for (int j = new_len; j < end; ++j)
                    s[j] = ' ';
            } else {
                new_len += end - start;
            }
            start = end+1;
        }
        if (new_len == -1) {
            return "";
        } else {
            s = s.substr(0, new_len);
        }

        // 2. 整体reverse
        reverse(s, 0, s.length() - 1);

        // 3. 对每个单词reverse
        start = 0;
        while (start < s.length()) {
            getNextWordPos(s, start, end);
            reverse(s, start, end - 1);
            start = end;
        }
        return s;
    }
};
