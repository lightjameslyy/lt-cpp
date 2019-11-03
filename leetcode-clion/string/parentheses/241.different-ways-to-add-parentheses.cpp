/*
 * @lc app=leetcode id=241 lang=cpp
 *
 * [241] Different Ways to Add Parentheses
 *
 * https://leetcode.com/problems/different-ways-to-add-parentheses/description/
 *
 * algorithms
 * Medium (52.08%)
 * Total Accepted:    84.7K
 * Total Submissions: 162.6K
 * Testcase Example:  '"2-1-1"'
 *
 * Given a string of numbers and operators, return all possible results from
 * computing all the different possible ways to group numbers and operators.
 * The valid operators are +, - and *.
 * 
 * Example 1:
 * 
 * 
 * Input: "2-1-1"
 * Output: [0, 2]
 * Explanation: 
 * ((2-1)-1) = 0 
 * (2-(1-1)) = 2
 * 
 * Example 2:
 * 
 * 
 * Input: "2*3-4*5"
 * Output: [-34, -14, -10, -10, 10]
 * Explanation: 
 * (2*(3-(4*5))) = -34 
 * ((2*3)-(4*5)) = -14 
 * ((2*(3-4))*5) = -10 
 * (2*((3-4)*5)) = -10 
 * (((2*3)-4)*5) = 10
 * 
 */

#include <vector>
#include <cctype>
#include <cstdlib>

using namespace std;

class Solution {
public:
    int calculate(int a, int b, char op) {
        switch (op) {
            case '+':
                return a + b;
            case '-':
                return a - b;
            case '*':
                return a * b;
            default:
                return 0;
        }
    }

    vector<int> helper(const string &input, int left, int right) {
        vector<int> res;
        for (int i = left; i <= right; ++i) {
            if (!isdigit(input[i])) {   // input[i] is op
                vector<int> res_left = helper(input, left, i - 1);
                vector<int> res_right = helper(input, i + 1, right);
                for (int l : res_left) {
                    for (int r : res_right)
                        res.push_back(calculate(l, r, input[i]));
                }
            }
        }
        if (res.empty()) {  // no op wthin input[left, right]
            res.push_back(atoi(input.substr(left, right - left + 1).c_str()));
        }
        return res;
    }

    // divide and conquer
    // 8ms, 13.3MB, 41.77%
    vector<int> diffWaysToCompute(string input) {
        return helper(input, 0, input.length() - 1);
    }
};
