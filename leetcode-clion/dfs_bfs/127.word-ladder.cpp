/*
 * @lc app=leetcode id=127 lang=cpp
 *
 * [127] Word Ladder
 *
 * https://leetcode.com/problems/word-ladder/description/
 *
 * algorithms
 * Medium (26.15%)
 * Total Accepted:    315.8K
 * Total Submissions: 1.2M
 * Testcase Example:  '"hit"\n"cog"\n["hot","dot","dog","lot","log","cog"]'
 *
 * Given two words (beginWord and endWord), and a dictionary's word list, find
 * the length of shortest transformation sequence from beginWord to endWord,
 * such that:
 * 
 * 
 * Only one letter can be changed at a time.
 * Each transformed word must exist in the word list. Note that beginWord is
 * not a transformed word.
 * 
 * 
 * Note:
 * 
 * 
 * Return 0 if there is no such transformation sequence.
 * All words have the same length.
 * All words contain only lowercase alphabetic characters.
 * You may assume no duplicates in the word list.
 * You may assume beginWord and endWord are non-empty and are not the same.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input:
 * beginWord = "hit",
 * endWord = "cog",
 * wordList = ["hot","dot","dog","lot","log","cog"]
 * 
 * Output: 5
 * 
 * Explanation: As one shortest transformation is "hit" -> "hot" -> "dot" ->
 * "dog" -> "cog",
 * return its length 5.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input:
 * beginWord = "hit"
 * endWord = "cog"
 * wordList = ["hot","dot","dog","lot","log"]
 * 
 * Output: 0
 * 
 * Explanation: The endWord "cog" is not in wordList, therefore no possible
 * transformation.
 * 
 * 
 * 
 * 
 * 
 */
#include <vector>
#include <unordered_set>
#include <queue>

using namespace std;

class Solution {
public:
    bool canTransfer(const string &cur, const string &next) {
        int flag = false;
        for (int i = 0; i < cur.length(); ++i) {
            if (cur[i] != next[i]) {
                if (flag) return false;
                flag = true;
            }
        }
        return true;
    }

    // first try, compare word distance
    int ladderLength1(string beginWord, string endWord, vector<string> &wordList) {
        unordered_set<string> sset;
        for (const string &word : wordList)
            sset.insert(word);
        if (sset.find(endWord) == sset.end()) return 0;
        queue<string> q;
        q.push(beginWord);
        int level = 1;
        while (!q.empty()) {
            level++;
            for (int size = q.size(); size > 0; --size) {
                string cur = q.front();
                q.pop();
                for (auto it = sset.begin(); it != sset.end();)
                    if (canTransfer(cur, *it)) {
                        if (*it == endWord)
                            return level;
                        q.push(*it);
                        it = sset.erase(it);
                    } else
                        ++it;
            }
        }
        return 0;
    }

    // second try, searching for word with distance=1
    int ladderLength(string beginWord, string endWord, vector<string> &wordList) {
        unordered_set<string> sset;
        for (const string &word : wordList)
            sset.insert(word);
        if (sset.find(endWord) == sset.end()) return 0;
        queue<string> q;
        q.push(beginWord);
        int level = 1;
        int len = beginWord.length();
        while (!q.empty()) {
            level++;
            for (int size = q.size(); size > 0; --size) {
                string cur = q.front();
                q.pop();
                sset.erase(cur);
                for (int i = 0; i < len; ++i) {
                    int tmp = cur[i] - 'a';
                    for (int j = 0; j < 26; ++j) {
                        if (j == tmp) continue;
                        cur[i] = 'a' + j;
                        auto it = sset.find(cur);
                        if (it != sset.end()) {
                            if (cur == endWord)
                                return level;
                            q.push(cur);
                            sset.erase(it);
                        }
                    }
                    cur[i] = 'a' + tmp;
                }
            }
        }
        return 0;
    }
};
