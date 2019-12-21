/*
 * @lc app=leetcode id=388 lang=cpp
 *
 * [388] Longest Absolute File Path
 *
 * https://leetcode.com/problems/longest-absolute-file-path/description/
 *
 * algorithms
 * Medium (40.12%)
 * Total Accepted:    72.9K
 * Total Submissions: 181.7K
 * Testcase Example:  '"dir\\n\\tsubdir1\\n\\tsubdir2\\n\\t\\tfile.ext"'
 *
 * Suppose we abstract our file system by a string in the following manner:
 * 
 * The string "dir\n\tsubdir1\n\tsubdir2\n\t\tfile.ext" represents:
 * 
 * dir
 * ⁠   subdir1
 * ⁠   subdir2
 * ⁠       file.ext
 * 
 * 
 * The directory dir contains an empty sub-directory subdir1 and a
 * sub-directory subdir2 containing a file file.ext.
 * 
 * The string
 * "dir\n\tsubdir1\n\t\tfile1.ext\n\t\tsubsubdir1\n\tsubdir2\n\t\tsubsubdir2\n\t\t\tfile2.ext"
 * represents:
 * 
 * dir
 * ⁠   subdir1
 * ⁠       file1.ext
 * ⁠       subsubdir1
 * ⁠   subdir2
 * ⁠       subsubdir2
 * ⁠           file2.ext
 * 
 * 
 * The directory dir contains two sub-directories subdir1 and subdir2. subdir1
 * contains a file file1.ext and an empty second-level sub-directory
 * subsubdir1. subdir2 contains a second-level sub-directory subsubdir2
 * containing a file file2.ext.
 * 
 * We are interested in finding the longest (number of characters) absolute
 * path to a file within our file system. For example, in the second example
 * above, the longest absolute path is "dir/subdir2/subsubdir2/file2.ext", and
 * its length is 32 (not including the double quotes).
 * 
 * Given a string representing the file system in the above format, return the
 * length of the longest absolute path to file in the abstracted file system.
 * If there is no file in the system, return 0.
 * 
 * Note:
 * 
 * The name of a file contains at least a . and an extension.
 * The name of a directory or sub-directory will not contain a ..
 * 
 * 
 * 
 * Time complexity required: O(n) where n is the size of the input string.
 * 
 * Notice that a/aa/aaa/file1.txt is not the longest file path, if there is
 * another path aaaaaaaaaaaaaaaaaaaaa/sth.png.
 */
#include <stack>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    int lengthLongestPath(string input) {
        if (input.empty()) return 0;
        stack<int> stk, lstk;
        int res = 0;
        int pos = 0;
        stk.push(0);
        lstk.push(0);
        input = "\n" + input;
        while (pos != input.length()) {
            // get level
            int prePos = pos;
            int spaceCount = 0;
            int preLevel = lstk.top();
            int level = 0;
            while (pos != input.length() && (input[pos] == '\n' || input[pos] == '\t' || input[pos] == ' ')) {
                if (level > preLevel) break;
                if (input[pos] == ' ') {
                    spaceCount++;
                    if (spaceCount == 4) {
                        level++;
                        spaceCount = 0;
                    }
                } else
                    level++;
                ++pos;
            }
            while (lstk.top() >= level) {
                stk.pop();
                lstk.pop();
            }
            lstk.push(level);
            // get dir/file name
            prePos = pos;
            int dotPos = input.length();
            while (pos != input.length() && input[pos] != '\n' && input[pos] != '\t') {
                if (input[pos] == '.')
                    dotPos = pos;
                ++pos;
            }
            int curLength = pos - prePos + stk.top() + 1;
            // if file, update res
            if (dotPos < pos - 1)
                res = max(res, curLength);
            stk.push(curLength);
        }
        return res ? res - 1 : 0;
    }
};
