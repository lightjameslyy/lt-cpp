/*
 * @lc app=leetcode id=150 lang=cpp
 *
 * [150] Evaluate Reverse Polish Notation
 *
 * https://leetcode.com/problems/evaluate-reverse-polish-notation/description/
 *
 * algorithms
 * Medium (33.80%)
 * Total Accepted:    186.9K
 * Total Submissions: 553.1K
 * Testcase Example:  '["2","1","+","3","*"]'
 *
 * Evaluate the value of an arithmetic expression in Reverse Polish Notation.
 * 
 * Valid operators are +, -, *, /. Each operand may be an integer or another
 * expression.
 * 
 * Note:
 * 
 * 
 * Division between two integers should truncate toward zero.
 * The given RPN expression is always valid. That means the expression would
 * always evaluate to a result and there won't be any divide by zero
 * operation.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: ["2", "1", "+", "3", "*"]
 * Output: 9
 * Explanation: ((2 + 1) * 3) = 9
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: ["4", "13", "5", "/", "+"]
 * Output: 6
 * Explanation: (4 + (13 / 5)) = 6
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: ["10", "6", "9", "3", "+", "-11", "*", "/", "*", "17", "+", "5", "+"]
 * Output: 22
 * Explanation: 
 * ⁠ ((10 * (6 / ((9 + 3) * -11))) + 17) + 5
 * = ((10 * (6 / (12 * -11))) + 17) + 5
 * = ((10 * (6 / -132)) + 17) + 5
 * = ((10 * 0) + 17) + 5
 * = (0 + 17) + 5
 * = 17 + 5
 * = 22
 * 
 * 
 */
#include <stack>
#include <string>
#include <unordered_map>

using namespace std;

class Solution {
public:
    // my first try
    int evalRPN1(vector <string> &tokens) {
        stack<int> res;
        for (string &str : tokens) {
            if (str == "+" || str == "-" || str == "*" || str == "/") {
                int b = res.top();
                res.pop();
                int a = res.top();
                res.pop();
                if (str == "+")
                    res.push(a + b);
                else if (str == "-")
                    res.push(a - b);
                else if (str == "*")
                    res.push(a * b);
                else
                    res.push(a / b);
            } else
                res.push(stoi(str));
        }
        return res.top();
    }

    // a subtle way
    int evalRPN(vector <string> &tokens) {
        unordered_map<string, function < int(int, int)>>
        op{
                {"+", [](int a, int b) { return a + b; }},
                {"-", [](int a, int b) { return a - b; }},
                {"*", [](int a, int b) { return a * b; }},
                {"/", [](int a, int b) { return a / b; }}
        };
        stack<int> s;
        for (int i = 0; i < tokens.size(); i++) {
            if (op.find(tokens[i]) == op.end()) {
                s.push(stoi(tokens[i]));
            } else {
                int a = s.top();
                s.pop();
                int b = s.top();
                s.pop();
                s.push(op[tokens[i]](b, a));
            }
        }
        return s.top();
    }
};
