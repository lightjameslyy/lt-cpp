/*
 * @lc app=leetcode id=179 lang=cpp
 *
 * [179] Largest Number
 *
 * https://leetcode.com/problems/largest-number/description/
 *
 * algorithms
 * Medium (25.78%)
 * Total Accepted:    129.2K
 * Total Submissions: 501.2K
 * Testcase Example:  '[10,2]'
 *
 * Given a list of non negative integers, arrange them such that they form the
 * largest number.
 * 
 * Example 1:
 * 
 * 
 * Input: [10,2]
 * Output: "210"
 * 
 * Example 2:
 * 
 * 
 * Input: [3,30,34,5,9]
 * Output: "9534330"
 * 
 * 
 * Note: The result may be very large, so you need to return a string instead
 * of an integer.
 * 
 */

#include <vector>
#include <algorithm>

using namespace std;

int count_comp = 0;

bool greater_string(const string &s1, const string &s2) {
    int len1 = s1.length(), len2 = s2.length();
    if (len1 > len2)
        return !greater_string(s2, s1);
    if (len1 == 0)
        return false;
    int j;
    for (int i = 0; i < len2; i += len1) {
        for (j = 0; j < len1; ++j) {
            int j2 = i + j;
            if (j2 >= len2)
                break;
            if (s1[j] > s2[j2])
                return true;
            if (s1[j] < s2[j2])
                return false;
        }
    }
//    cout << ++count_comp << " " << j << endl;
    for (int i = j; i < len1; ++i) {
        if (s1[i] > s1[i - j])
            return true;
        if (s1[i] < s1[i - j])
            return false;
    }
//    cout << "greater " << ++count_comp << endl;
    return false;
}

class Solution {
public:

    string largestNumber(vector<int> &nums) {
        int size = nums.size();
        if (size == 0)
            return "0";
        string res = "";
        for (int val : nums) {
            strs.push_back(to_string(val));
        }
        sort(strs.begin(), strs.end(), greater_string);
//        sort(strs.begin(), strs.end());
//        cout << "ok" << endl;
        for (string &s: strs)
            res += s;
        int nzpos = 0;
        while (nzpos < res.length() - 1) {
            if (res[nzpos] == '0')
                nzpos++;
            else break;
        }
        if (nzpos > 0)
            return res.substr(nzpos);
        return res;
    }

    vector<string> strs;
};
