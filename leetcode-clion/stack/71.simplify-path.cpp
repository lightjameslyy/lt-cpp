/*
 * @lc app=leetcode id=71 lang=cpp
 *
 * [71] Simplify Path
 *
 * https://leetcode.com/problems/simplify-path/description/
 *
 * algorithms
 * Medium (30.04%)
 * Total Accepted:    170.2K
 * Total Submissions: 566.5K
 * Testcase Example:  '"/home/"'
 *
 * Given an absolute path for a file (Unix-style), simplify it. Or in other
 * words, convert it to the canonical path.
 * 
 * In a UNIX-style file system, a period . refers to the current directory.
 * Furthermore, a double period .. moves the directory up a level. For more
 * information, see: Absolute path vs relative path in Linux/Unix
 * 
 * Note that the returned canonical path must always begin with a slash /, and
 * there must be only a single slash / between two directory names. The last
 * directory name (if it exists) must not end with a trailing /. Also, the
 * canonical path must be the shortest string representing the absolute
 * path.
 * 
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: "/home/"
 * Output: "/home"
 * Explanation: Note that there is no trailing slash after the last directory
 * name.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: "/../"
 * Output: "/"
 * Explanation: Going one level up from the root directory is a no-op, as the
 * root level is the highest level you can go.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: "/home//foo/"
 * Output: "/home/foo"
 * Explanation: In the canonical path, multiple consecutive slashes are
 * replaced by a single one.
 * 
 * 
 * Example 4:
 * 
 * 
 * Input: "/a/./b/../../c/"
 * Output: "/c"
 * 
 * 
 * Example 5:
 * 
 * 
 * Input: "/a/../../b/../c//.//"
 * Output: "/c"
 * 
 * 
 * Example 6:
 * 
 * 
 * Input: "/a//b////c/d//././/.."
 * Output: "/a/b/c"
 * 
 * 
 */
#include <deque>
#include <string>

using namespace std;

class Solution {
public:
    string getNextDirName(string path, int &pos) {
        if ((pos = path.find_first_not_of('/', pos)) == string::npos)
            return "";
        int prePos = pos;
        return (pos = path.find('/', pos)) == string::npos ? path.substr(prePos) : path.substr(prePos, pos - prePos);
    }

    string simplifyPath(string path) {
        deque<string> dq;
        dq.push_back("/");
        int pos = 0;
        string cur = "";
        while ((cur = getNextDirName(path, pos)) != "") {
            if (cur == "..") {
                if (dq.back() != "/")
                    dq.pop_back();
            } else if (cur != ".")
                dq.push_back(cur);
        }
        dq.pop_front();
        string res = "";
        while (!dq.empty()) {
            res += "/";
            res += dq.front();
            dq.pop_front();
        }
        return (res == "" ? "/" : res);
    }

};
