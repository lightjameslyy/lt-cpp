/*
 * @lc app=leetcode id=110 lang=cpp
 *
 * [110] Balanced Binary Tree
 *
 * https://leetcode.com/problems/balanced-binary-tree/description/
 *
 * algorithms
 * Easy (41.97%)
 * Total Accepted:    367.8K
 * Total Submissions: 876.4K
 * Testcase Example:  '[3,9,20,null,null,15,7]'
 *
 * Given a binary tree, determine if it is height-balanced.
 * 
 * For this problem, a height-balanced binary tree is defined as:
 * 
 * 
 * a binary tree in which the left and right subtrees of every node differ in
 * height by no more than 1.
 * 
 * 
 * 
 * 
 * Example 1:
 * 
 * Given the following tree [3,9,20,null,null,15,7]:
 * 
 * 
 * ⁠   3
 * ⁠  / \
 * ⁠ 9  20
 * ⁠   /  \
 * ⁠  15   7
 * 
 * Return true.
 * 
 * Example 2:
 * 
 * Given the following tree [1,2,2,3,3,null,null,4,4]:
 * 
 * 
 * ⁠      1
 * ⁠     / \
 * ⁠    2   2
 * ⁠   / \
 * ⁠  3   3
 * ⁠ / \
 * ⁠4   4
 * 
 * 
 * Return false.
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
#include <algorithm>

using namespace std;

class Solution {
public:
    struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;

        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
    };

    int height(TreeNode *root) {
        if (root == NULL)
            return 0;
        return 1 + max(height(root->left), height(root->right));
    }

    // 20ms, 36.9MB, 19.33%
    bool isBalanced1(TreeNode *root) {
        if (root == NULL) return true;
        return isBalanced(root->left) && isBalanced(root->right) && abs(height(root->left) - height(root->right)) < 2;
    }

    int helper(TreeNode *root) {
        if (root == NULL) return 0;
        int lh = helper(root->left), rh = helper(root->right);
        if (lh == -1 || rh == -1 || abs(lh - rh) > 1) return -1;
        return 1 + max(lh, rh);
    }

    // 8ms, 17.3MB, 96.89%
    bool isBalanced(TreeNode *root) {
        if (root == NULL) return true;
        return helper(root) != -1;
    }
};
