/*
 * @lc app=leetcode id=115 lang=cpp
 *
 * [115] Distinct Subsequences
 *
 * https://leetcode.com/problems/distinct-subsequences/description/
 *
 * algorithms
 * Hard (36.05%)
 * Total Accepted:    116.7K
 * Total Submissions: 323.6K
 * Testcase Example:  '"rabbbit"\n"rabbit"'
 *
 * Given a string S and a string T, count the number of distinct subsequences
 * of S which equals T.
 * 
 * A subsequence of a string is a new string which is formed from the original
 * string by deleting some (can be none) of the characters without disturbing
 * the relative positions of the remaining characters. (ie, "ACE" is a
 * subsequence of "ABCDE" while "AEC" is not).
 * 
 * Example 1:
 * 
 * 
 * Input: S = "rabbbit", T = "rabbit"
 * Output: 3
 * Explanation:
 * 
 * As shown below, there are 3 ways you can generate "rabbit" from S.
 * (The caret symbol ^ means the chosen letters)
 * 
 * rabbbit
 * ^^^^ ^^
 * rabbbit
 * ^^ ^^^^
 * rabbbit
 * ^^^ ^^^
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: S = "babgbag", T = "bag"
 * Output: 5
 * Explanation:
 * 
 * As shown below, there are 5 ways you can generate "bag" from S.
 * (The caret symbol ^ means the chosen letters)
 * 
 * babgbag
 * ^^ ^
 * babgbag
 * ^^    ^
 * babgbag
 * ^    ^^
 * babgbag
 * ⁠  ^  ^^
 * babgbag
 * ⁠    ^^^
 * 
 * 
 */

using namespace std;

class Solution {
public:

    void helper(const string &s, const string &t, int spos, int tpos, int &count) {
        if (tpos == t.length()) {
            ++count;
            return;
        }
        if (s.length() - spos < t.length() - tpos)
            return;
        // choose s[spos]
        if (s[spos] == t[tpos]) {
            helper(s, t, spos + 1, tpos + 1, count);
        }
        // skip s[spos]
        helper(s, t, spos + 1, tpos, count);
    }

    // time limit exceeded
    int numDistinct_tle(string s, string t) {
        int count = 0;
        helper(s, t, 0, 0, count);
        return count;
    }

    // DP
    // 0ms, 8.8MB, 100%
    int numDistinct(string s, string t) {
        // dp[i]: count of potential matches with t[0, i-1]
        // NOTE: potential matches may overflow
        vector<long long> dp(t.length() + 1, 0);
        dp[0] = 1;  // t is empty
        for (char c : s) {
            // must update backwards because dp[j] depends on dp[j-1],
            // which is updated at the last iteration
            for (size_t j = t.length(); j > 0; --j)
                if (c == t[j - 1]) dp[j] += dp[j - 1];
        }
        return dp[t.length()];
    }
};
