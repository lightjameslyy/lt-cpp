/*
 * @lc app=leetcode id=20 lang=cpp
 *
 * [20] Valid Parentheses
 *
 * https://leetcode.com/problems/valid-parentheses/description/
 *
 * algorithms
 * Easy (37.47%)
 * Total Accepted:    738.9K
 * Total Submissions: 2M
 * Testcase Example:  '"()"'
 *
 * Given a string containing just the characters '(', ')', '{', '}', '[' and
 * ']', determine if the input string is valid.
 * 
 * An input string is valid if:
 * 
 * 
 * Open brackets must be closed by the same type of brackets.
 * Open brackets must be closed in the correct order.
 * 
 * 
 * Note that an empty string is also considered valid.
 * 
 * Example 1:
 * 
 * 
 * Input: "()"
 * Output: true
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: "()[]{}"
 * Output: true
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: "(]"
 * Output: false
 * 
 * 
 * Example 4:
 * 
 * 
 * Input: "([)]"
 * Output: false
 * 
 * 
 * Example 5:
 * 
 * 
 * Input: "{[]}"
 * Output: true
 * 
 * 
 */

#include <stack>

using namespace std;

class Solution {
public:
    bool isLeft(char c) {
        return c == '(' || c == '[' || c == '{';
    }

    bool isRight(char c) {
        return c == ')' || c == ']' || c == '}';
    }

    char getLeft(char c) {
        switch (c) {
            case ')':
                return '(';
            case ']':
                return '[';
            case '}':
                return '{';
            default:
                return 0;
        }
    }

    // stack
    // 0ms, 8.4MB, 100%
    bool isValid(string s) {
        stack<char> parStack;
        for (char c : s) {
            if (isLeft(c)) {
                parStack.push(c);
            } else if (isRight(c)) {
                // in case of more right brackets
                if (parStack.empty() || getLeft(c) != parStack.top())
                    return false;
                parStack.pop();
            } else {
                return false;
            }
        }
        // in case of more left brackets
        return parStack.empty();
    }
};
