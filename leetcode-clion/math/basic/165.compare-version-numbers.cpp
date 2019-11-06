/*
 * @lc app=leetcode id=165 lang=cpp
 *
 * [165] Compare Version Numbers
 *
 * https://leetcode.com/problems/compare-version-numbers/description/
 *
 * algorithms
 * Medium (25.04%)
 * Total Accepted:    154.6K
 * Total Submissions: 617.6K
 * Testcase Example:  '"0.1"\n"1.1"'
 *
 * Compare two version numbers version1 and version2.
 * If version1 > version2 return 1; if version1 < version2 return -1;otherwise
 * return 0.
 * 
 * You may assume that the version strings are non-empty and contain only
 * digits and the . character.
 * The . character does not represent a decimal point and is used to separate
 * number sequences.
 * For instance, 2.5 is not "two and a half" or "half way to version three", it
 * is the fifth second-level revision of the second first-level revision.
 * You may assume the default revision number for each level of a version
 * number to be 0. For example, version number 3.4 has a revision number of 3
 * and 4 for its first and second level revision number. Its third and fourth
 * level revision number are both 0.
 * 
 * 
 * 
 * Example 1:
 * 
 * Input: version1 = "0.1", version2 = "1.1"
 * Output: -1
 * 
 * Example 2:
 * 
 * Input: version1 = "1.0.1", version2 = "1"
 * Output: 1
 * 
 * Example 3:
 * 
 * Input: version1 = "7.5.2.4", version2 = "7.5.3"
 * Output: -1
 * 
 * Example 4:
 * 
 * Input: version1 = "1.01", version2 = "1.001"
 * Output: 0
 * Explanation: Ignoring leading zeroes, both “01” and “001" represent the same
 * number “1”
 * 
 * Example 5:
 * 
 * Input: version1 = "1.0", version2 = "1.0.0"
 * Output: 0
 * Explanation: The first version number does not have a third level revision
 * number, which means its third level revision number is default to "0"
 * 
 * 
 * 
 * Note:
 * 
 * Version strings are composed of numeric strings separated by dots . and this
 * numeric strings may have leading zeroes. 
 * Version strings do not start or end with dots, and they will not be two
 * consecutive dots.
 * 
 */

using namespace std;

class Solution {
public:

    // my solution, no need to convert to integer value
    // 0ms, 8.6MB, 100%
    int compareVersion(string version1, string version2) {
        int pos1 = 0, pos2 = 0;
        int len1 = version1.length(), len2 = version2.length();
        while (pos1 < len1 && pos2 < len2) {
            // skip leading zeros
            while (pos1 < len1 && version1[pos1] == '0')
                pos1++;
            while (pos2 < len2 && version2[pos2] == '0')
                pos2++;
            if (pos1 == len1 || pos2 == len2)
                break;
            int potential = 0;
            int start1 = pos1, start2 = pos2;
            // compare value
            while (version1[pos1] != '.' && version2[pos2] != '.') {
                if (version1[pos1] > version2[pos2]) {
                    potential = 1;
                    break;
                }
                if (version2[pos2] > version1[pos1]) {
                    potential = -1;
                    break;
                }
                pos1++;
                pos2++;
                if (pos1 == len1 || pos2 == len2)
                    break;
            }
            while (pos1 < len1 && version1[pos1] != '.') {
                pos1++;
            }
            while (pos2 < len2 && version2[pos2] != '.') {
                pos2++;
            }
            if (potential == 1) {
                return (pos1 - start1 >= pos2 - start2) ? 1 : -1;
            } else if (potential == -1) {
                return (pos2 - start2 >= pos1 - start1) ? -1 : 1;
            } else {
                if (pos1 - start1 > pos2 - start2)
                    return 1;
                if (pos2 - start2 > pos1 - start1)
                    return -1;
            }
            // now, pos1 and pos2 both at '.' or end
            pos1++;
            pos2++;
        }
        // consider more dots
        // NOTE: '.' < '0' < '1' < '2' < ... < '9'
        while (pos1 < len1) {
            if (version1[pos1++] > '0')
                return 1;
        }
        while (pos2 < len2) {
            if (version2[pos2++] > '0')
                return -1;
        }
        return 0;
    }
};
