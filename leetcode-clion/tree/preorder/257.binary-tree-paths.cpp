/*
 * @lc app=leetcode id=257 lang=cpp
 *
 * [257] Binary Tree Paths
 *
 * https://leetcode.com/problems/binary-tree-paths/description/
 *
 * algorithms
 * Easy (47.79%)
 * Total Accepted:    256.3K
 * Total Submissions: 536.3K
 * Testcase Example:  '[1,2,3,null,5]'
 *
 * Given a binary tree, return all root-to-leaf paths.
 * 
 * Note: A leaf is a node with no children.
 * 
 * Example:
 * 
 * 
 * Input:
 * 
 * ⁠  1
 * ⁠/   \
 * 2     3
 * ⁠\
 * ⁠ 5
 * 
 * Output: ["1->2->5", "1->3"]
 * 
 * Explanation: All root-to-leaf paths are: 1->2->5, 1->3
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
#include <string>

using namespace std;

class Solution {
public:
    struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;

        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
    };

    void helper(TreeNode *cur, string path, vector<string> &res) {
        path += "->" + to_string(cur->val);
        if (cur->left == NULL && cur->right == NULL) {
            res.push_back(path);
            return;
        }
        if (cur->left != NULL)
            helper(cur->left, path, res);
        if (cur->right != NULL)
            helper(cur->right, path, res);
    }

    // 4ms, 11.7MB, 76.8%
    vector<string> binaryTreePaths(TreeNode *root) {
        vector<string> res;
        if (root == NULL) return res;
        if (root->left == NULL && root->right == NULL)
            return {to_string(root->val)};
        if (root->left)
            helper(root->left, to_string(root->val), res);
        if (root->right)
            helper(root->right, to_string(root->val), res);
        return res;
    }
};
