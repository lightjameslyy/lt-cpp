/*
 * @lc app=leetcode id=345 lang=cpp
 *
 * [345] Reverse Vowels of a String
 *
 * https://leetcode.com/problems/reverse-vowels-of-a-string/description/
 *
 * algorithms
 * Easy (41.43%)
 * Total Accepted:    154.7K
 * Total Submissions: 373.3K
 * Testcase Example:  '"hello"'
 *
 * Write a function that takes a string as input and reverse only the vowels of
 * a string.
 * 
 * Example 1:
 * 
 * 
 * Input: "hello"
 * Output: "holle"
 * 
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: "leetcode"
 * Output: "leotcede"
 * 
 * 
 * Note:
 * The vowels does not include the letter "y".
 * 
 * 
 * 
 */

/*
 * 思路：two-pointers
 */

#include <vector>

using namespace std;

class Solution {
public:
    string reverseVowels(string s) {
        int len = s.length();
        if (len < 2)
            return s;
        // O(1) hash
        vector<bool> is_vowel(256, false);
        is_vowel['a'] = true;
        is_vowel['e'] = true;
        is_vowel['i'] = true;
        is_vowel['o'] = true;
        is_vowel['u'] = true;
        is_vowel['A'] = true;
        is_vowel['E'] = true;
        is_vowel['I'] = true;
        is_vowel['O'] = true;
        is_vowel['U'] = true;
        int left = 0, right = len-1;
        while (left < right) {
            while (is_vowel[s[left]] == false)
                left++;
            while (is_vowel[s[right]] == false)
                right--;
            if (left < right)
                swap(s[left++], s[right--]);
        }
        return s;
    }
};
