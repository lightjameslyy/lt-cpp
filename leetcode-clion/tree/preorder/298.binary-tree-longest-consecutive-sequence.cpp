/*
 * @lc app=leetcode id=298 lang=cpp
 *
 * [298] Binary Tree Longest Consecutive Sequence
 *
 * https://leetcode.com/problems/binary-tree-longest-consecutive-sequence/description/
 *
 * algorithms
 * Medium (45.16%)
 * Total Accepted:    68.5K
 * Total Submissions: 151.8K
 * Testcase Example:  '[1,null,3,2,4,null,null,null,5]'
 *
 * Given a binary tree, find the length of the longest consecutive sequence
 * path.
 * 
 * The path refers to any sequence of nodes from some starting node to any node
 * in the tree along the parent-child connections. The longest consecutive path
 * need to be from parent to child (cannot be the reverse).
 * 
 * Example 1:
 * 
 * 
 * Input:
 * 
 * ⁠  1
 * ⁠   \
 * ⁠    3
 * ⁠   / \
 * ⁠  2   4
 * ⁠       \
 * ⁠        5
 * 
 * Output: 3
 * 
 * Explanation: Longest consecutive sequence path is 3-4-5, so return 3.
 * 
 * Example 2:
 * 
 * 
 * Input:
 * 
 * ⁠  2
 * ⁠   \
 * ⁠    3
 * ⁠   / 
 * ⁠  2    
 * ⁠ / 
 * ⁠1
 * 
 * Output: 2 
 * 
 * Explanation: Longest consecutive sequence path is 2-3, not 3-2-1, so return
 * 2.
 */
/**
 * Definition for a binary tree node.
  struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode(int x) : val(x), left(NULL), right(NULL) {}
  };
 */

#include <climits>

using namespace std;

class Solution {
public:
    struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;

        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
    };

    void dfs(TreeNode *node, int pVal, int count, int &res) {
        if (node == NULL) {
            if (count > res)
                res = count;
            return;
        }
        int cVal = node->val;
        if (pVal >= cVal || pVal < cVal - 1) {
            if (count > res)
                res = count;
            dfs(node->left, cVal, 1, res);
            dfs(node->right, cVal, 1, res);
        } else {
            dfs(node->left, cVal, count + 1, res);
            dfs(node->right, cVal, count + 1, res);
        }
    }

    // 32ms, 27.2MB, 98.61%
    int longestConsecutive(TreeNode *root) {
        int res = 0;
        dfs(root, INT_MAX, 0, res);
        return res;
    }
};
