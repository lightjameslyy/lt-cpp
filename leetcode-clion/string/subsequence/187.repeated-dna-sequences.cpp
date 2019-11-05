/*
 * @lc app=leetcode id=187 lang=cpp
 *
 * [187] Repeated DNA Sequences
 *
 * https://leetcode.com/problems/repeated-dna-sequences/description/
 *
 * algorithms
 * Medium (37.19%)
 * Total Accepted:    139.3K
 * Total Submissions: 374.5K
 * Testcase Example:  '"AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT"'
 *
 * All DNA is composed of a series of nucleotides abbreviated as A, C, G, and
 * T, for example: "ACGAATTCCG". When studying DNA, it is sometimes useful to
 * identify repeated sequences within the DNA.
 * 
 * Write a function to find all the 10-letter-long sequences (substrings) that
 * occur more than once in a DNA molecule.
 * 
 * Example:
 * 
 * 
 * Input: s = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT"
 * 
 * Output: ["AAAAACCCCC", "CCCCCAAAAA"]
 * 
 * 
 */

#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:

    // quaternary conversion
    // A C G T
    // 0 1 2 3
    // 32ms, 16.6MB, 95.88%
    vector<string> findRepeatedDnaSequences(string s) {
        int val['T' + 1];
        val['A'] = 0;
        val['C'] = 1;
        val['G'] = 2;
        val['T'] = 3;
        vector<string> res;
        if (s.length() <= 10)
            return res;
        // init dnaMap
        unordered_map<int, int> dnaMap;
        int quatVal = 0;
        for (int i = 0; i < 10; ++i) {
            quatVal = (quatVal << 2) | val[s[i]];
        }
        dnaMap[quatVal]++;
        // update dnaMap
        for (int i = 10; i < s.length(); ++i) {
            quatVal = (quatVal << 2) & 0x000FFFFF | val[s[i]];
            if (++dnaMap[quatVal] == 2) {
                res.push_back(s.substr(i - 9, 10));
            }
        }
        return res;
    }
};
