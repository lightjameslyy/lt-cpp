/*
 * @lc app=leetcode id=199 lang=cpp
 *
 * [199] Binary Tree Right Side View
 *
 * https://leetcode.com/problems/binary-tree-right-side-view/description/
 *
 * algorithms
 * Medium (50.15%)
 * Total Accepted:    204.3K
 * Total Submissions: 407.4K
 * Testcase Example:  '[1,2,3,null,5,null,4]'
 *
 * Given a binary tree, imagine yourself standing on the right side of it,
 * return the values of the nodes you can see ordered from top to bottom.
 * 
 * Example:
 * 
 * 
 * Input: [1,2,3,null,5,null,4]
 * Output: [1, 3, 4]
 * Explanation:
 * 
 * ⁠  1            <---
 * ⁠/   \
 * 2     3         <---
 * ⁠\     \
 * ⁠ 5     4       <---
 * 
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
#include <vector>

using namespace std;

class Solution {
public:
    struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;

        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
    };

    void helper(TreeNode *root, int level, vector<int> &res) {
        if (root == NULL) return;
        if (res.size() < level + 1)
            res.push_back(0);
        helper(root->left, level + 1, res);
        res[level] = root->val;
        helper(root->right, level + 1, res);
    }

    vector<int> rightSideView(TreeNode *root) {
        vector<int> res;
        helper(root, 0, res);
        return res;
    }
};
