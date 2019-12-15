/*
 * @lc app=leetcode id=243 lang=cpp
 *
 * [243] Shortest Word Distance
 *
 * https://leetcode.com/problems/shortest-word-distance/description/
 *
 * algorithms
 * Easy (58.97%)
 * Total Accepted:    78.7K
 * Total Submissions: 133.4K
 * Testcase Example:  '["practice", "makes", "perfect", "coding", "makes"]\n"coding"\n"practice"'
 *
 * Given a list of words and two words word1 and word2, return the shortest
 * distance between these two words in the list.
 * 
 * Example:
 * Assume that words = ["practice", "makes", "perfect", "coding", "makes"].
 * 
 * 
 * Input: word1 = “coding”, word2 = “practice”
 * Output: 3
 * 
 * 
 * 
 * Input: word1 = "makes", word2 = "coding"
 * Output: 1
 * 
 * 
 * Note:
 * You may assume that word1 does not equal to word2, and word1 and word2 are
 * both in the list.
 * 
 */
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int shortestDistance(vector<string> &words, string word1, string word2) {
        int pos1 = -1, pos2 = -1;
        int res = words.size();
        for (int i = 0; i < words.size(); ++i) {
            if (word1 == words[i]) {
                pos1 = i;
                if (pos2 != -1)
                    res = min(res, pos1 - pos2);
            }
            if (word2 == words[i]) {
                pos2 = i;
                if (pos1 != -1)
                    res = min(res, pos2 - pos1);
            }
        }
        return res;
    }
};
