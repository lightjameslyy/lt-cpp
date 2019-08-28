/*
 * @lc app=leetcode id=68 lang=cpp
 *
 * [68] Text Justification
 *
 * https://leetcode.com/problems/text-justification/description/
 *
 * algorithms
 * Hard (23.27%)
 * Total Accepted:    103.9K
 * Total Submissions: 430.6K
 * Testcase Example:  '["This", "is", "an", "example", "of", "text", "justification."]\n16'
 *
 * Given an array of words and a width maxWidth, format the text such that each
 * line has exactly maxWidth characters and is fully (left and right)
 * justified.
 * 
 * You should pack your words in a greedy approach; that is, pack as many words
 * as you can in each line. Pad extra spaces ' ' when necessary so that each
 * line has exactly maxWidth characters.
 * 
 * Extra spaces between words should be distributed as evenly as possible. If
 * the number of spaces on a line do not divide evenly between words, the empty
 * slots on the left will be assigned more spaces than the slots on the right.
 * 
 * For the last line of text, it should be left justified and no extra space is
 * inserted between words.
 * 
 * Note:
 * 
 * 
 * A word is defined as a character sequence consisting of non-space characters
 * only.
 * Each word's length is guaranteed to be greater than 0 and not exceed
 * maxWidth.
 * The input array words contains at least one word.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input:
 * words = ["This", "is", "an", "example", "of", "text", "justification."]
 * maxWidth = 16
 * Output:
 * [
 * "This    is    an",
 * "example  of text",
 * "justification.  "
 * ]
 * 
 * 
 * Example 2:
 * 
 * 
 * Input:
 * words = ["What","must","be","acknowledgment","shall","be"]
 * maxWidth = 16
 * Output:
 * [
 * "What   must   be",
 * "acknowledgment  ",
 * "shall be        "
 * ]
 * Explanation: Note that the last line is "shall be    " instead of "shall
 * be",
 * because the last line must be left-justified instead of fully-justified.
 * ⁠            Note that the second line is also left-justified becase it
 * contains only one word.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input:
 * words =
 * ["Science","is","what","we","understand","well","enough","to","explain",
 * "to","a","computer.","Art","is","everything","else","we","do"]
 * maxWidth = 20
 * Output:
 * [
 * "Science  is  what we",
 * ⁠ "understand      well",
 * "enough to explain to",
 * "a  computer.  Art is",
 * "everything  else  we",
 * "do                  "
 * ]
 * 
 * 
 */

#include <vector>
#include <string>

using namespace std;

class Solution {
public:

    string makeLine(vector<string> &words, int maxWidth, int sumLength, int prevIndex, int i) {
        string spaces = ""; // maxWidth spaces
        spaces.append(maxWidth, ' ');
        int wordCount = i - prevIndex;
        int div = 1, rem = 0;
        if (i < words.size() - 1) {
            int spacesCount = maxWidth - sumLength;
            div = (wordCount > 1) ? spacesCount / (wordCount - 1) : 0;
            rem = (wordCount > 1) ? spacesCount % (wordCount - 1) : 0;
        }
        int jj = 0;
        for (int j = 1; j <= wordCount; ++j) {
            spaces.replace(jj, words[prevIndex + j].length(), words[prevIndex + j]);
            jj += words[prevIndex + j].length();
            if (j == wordCount) break;
            jj += div;
            if (rem) {
                jj++;
                rem--;
            }
        }
        return spaces;
    }

    vector<string> fullJustify(vector<string> &words, int maxWidth) {
        vector<string> res;
        int prevIndex = -1;
        int sumLength = 0;
        int minWidth = 0;
        for (int i = 0; i < words.size(); ++i) {
            sumLength += words[i].length();
            minWidth += words[i].length();
            if (i - prevIndex >= 2) {
                minWidth++; // add a space
            }
            if (minWidth >= maxWidth) {
                if (minWidth > maxWidth) {
                    sumLength -= words[i].length();
                    i--;
                }
                res.push_back(makeLine(words, maxWidth, sumLength, prevIndex, i));
                prevIndex = i;
                minWidth = sumLength = 0;
            } else {
                if (i == words.size() - 1) {
                    res.push_back(makeLine(words, maxWidth, sumLength, prevIndex, i));
                }
            }
        }
        return res;
    }
};
