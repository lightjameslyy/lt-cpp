/*
 * @lc app=leetcode id=65 lang=cpp
 *
 * [65] Valid Number
 *
 * https://leetcode.com/problems/valid-number/description/
 *
 * algorithms
 * Hard (13.99%)
 * Total Accepted:    133.1K
 * Total Submissions: 933.1K
 * Testcase Example:  '"0"'
 *
 * Validate if a given string can be interpreted as a decimal number.
 * 
 * Some examples:
 * "0" => true
 * " 0.1 " => true
 * "abc" => false
 * "1 a" => false
 * "2e10" => true
 * " -90e3   " => true
 * " 1e" => false
 * "e3" => false
 * " 6e-1" => true
 * " 99e2.5 " => false
 * "53.5e93" => true
 * " --6 " => false
 * "-+3" => false
 * "95a54e53" => false
 * 
 * Note: It is intended for the problem statement to be ambiguous. You should
 * gather all requirements up front before implementing one. However, here is a
 * list of characters that can be in a valid decimal number:
 * 
 * 
 * Numbers 0-9
 * Exponent - "e"
 * Positive/negative sign - "+"/"-"
 * Decimal point - "."
 * 
 * 
 * Of course, the context of these characters also matters in the input.
 * 
 * Update (2015-02-10):
 * The signature of the C++ function had been updated. If you still see your
 * function signature accepts a const char * argument, please click the reload
 * button to reset your code definition.
 * 
 */

#include <string>
#include <cctype>

using namespace std;

class Solution {
public:

    string trim(const string &s) {
        int pos = s.find_first_not_of(" \r\n\t");
        if (pos == string::npos)
            return "";
        int len = s.find_last_not_of(" \r\n\t") - pos + 1;
        return s.substr(pos, len);
    }

    bool isNumber(string s) {
        enum State {
            START,
            SIGN,
            INT,
            POINT,
            INTPOINT,
            FLOAT,
            HALFE,
            HALFESIGN,
            E
        };
        State state = START;
        for (char c : trim(s)) {
            switch (state) {
                case START: {
                    if (c == '+' | c == '-') {
                        state = SIGN;
                    } else if (isdigit(c)) {
                        state = INT;
                    } else if (c == '.') {
                        state = POINT;
                    } else
                        return false;
                    break;
                }
                case SIGN: {
                    if (c == '.') {
                        state = POINT;
                    } else if (isdigit(c)) {
                        state = INT;
                    } else
                        return false;
                    break;
                }
                case INT: {
                    if (isdigit(c)) {
                        break;
                    } else if (c == '.') {
                        state = INTPOINT;
                    } else if (c == 'e') {
                        state = HALFE;
                    } else
                        return false;
                    break;
                }
                case POINT: {
                    if (isdigit(c)) {
                        state = FLOAT;
                    } else
                        return false;
                    break;
                }
                case INTPOINT: {
                    if (isdigit(c)) {
                        state = FLOAT;
                    } else if (c == 'e') {
                        state = HALFE;
                    } else
                        return false;
                    break;
                }
                case FLOAT: {
                    if (isdigit(c)) {
                        break;
                    } else if (c == 'e') {
                        state = HALFE;
                    } else
                        return false;
                    break;
                }
                case HALFE: {
                    if (c == '+' || c == '-') {
                        state = HALFESIGN;
                    } else if (isdigit(c)) {
                        state = E;
                    } else
                        return false;
                    break;
                }
                case HALFESIGN: {
                    if (isdigit(c)) {
                        state = E;
                    } else
                        return false;
                    break;
                }
                case E: {
                    if (!isdigit(c))
                        return false;
                    break;
                }
            }
        }
        switch (state) {
            case INT:
            case INTPOINT:
            case FLOAT:
            case E:
                return true;
            default:
                break;
        }
        return false;
    }
};
