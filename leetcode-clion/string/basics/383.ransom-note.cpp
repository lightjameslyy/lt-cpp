/*
 * @lc app=leetcode id=383 lang=cpp
 *
 * [383] Ransom Note
 *
 * https://leetcode.com/problems/ransom-note/description/
 *
 * algorithms
 * Easy (49.82%)
 * Total Accepted:    111.1K
 * Total Submissions: 222.9K
 * Testcase Example:  '"a"\n"b"'
 *
 * 
 * Given an arbitrary ransom note string and another string containing letters
 * from all the magazines, write a function that will return true if the
 * ransom 
 * note can be constructed from the magazines ; otherwise, it will return
 * false. 
 * 
 * 
 * Each letter in the magazine string can only be used once in your ransom
 * note.
 * 
 * 
 * Note:
 * You may assume that both strings contain only lowercase letters.
 * 
 * 
 * 
 * canConstruct("a", "b") -> false
 * canConstruct("aa", "ab") -> false
 * canConstruct("aa", "aab") -> true
 * 
 * 
 */

/*
 * 思路：lowercase letters hash
 */

#include <vector>

using namespace std;

class Solution {
public:
    bool canConstruct(string ransomNote, string magazine) {
        vector<int> counts('z' + 1, 0);
        for (char c : magazine) {
            counts[c]++;
        }
        for (char c : ransomNote) {
            counts[c]--;
        }
        for (char i = 'a'; i <= 'z'; ++i) {
            if (counts[i] < 0) {
                return false;
            }
        }
        return true;
    }
};
