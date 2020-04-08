/*
 * @lc app=leetcode id=450 lang=cpp
 *
 * [450] Delete Node in a BST
 *
 * https://leetcode.com/problems/delete-node-in-a-bst/description/
 *
 * algorithms
 * Medium (40.93%)
 * Total Accepted:    80.8K
 * Total Submissions: 197.4K
 * Testcase Example:  '[5,3,6,2,4,null,7]\n3'
 *
 * Given a root node reference of a BST and a key, delete the node with the
 * given key in the BST. Return the root node reference (possibly updated) of
 * the BST.
 *
 * Basically, the deletion can be divided into two stages:
 *
 * Search for a node to remove.
 * If the node is found, delete the node.
 *
 *
 *
 * Note: Time complexity should be O(height of tree).
 *
 * Example:
 *
 * root = [5,3,6,2,4,null,7]
 * key = 3
 *
 * ⁠   5
 * ⁠  / \
 * ⁠ 3   6
 * ⁠/ \   \
 * 2   4   7
 *
 * Given key to delete is 3. So we find the node with value 3 and delete it.
 *
 * One valid answer is [5,4,6,2,null,null,7], shown in the following BST.
 *
 * ⁠   5
 * ⁠  / \
 * ⁠ 4   6
 * ⁠/     \
 * 2       7
 *
 * Another valid answer is [5,2,6,null,4,null,7].
 *
 * ⁠   5
 * ⁠  / \
 * ⁠ 2   6
 * ⁠  \   \
 * ⁠   4   7
 *
 *
 */
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
  public:
    TreeNode *deleteNode(TreeNode *root, int key) {
        if (root == nullptr)
            return nullptr;
        if (root->val == key) {
            if (root->left == nullptr) {
                TreeNode *res = root->right;
                delete root;
                return res;
            }
            if (root->right == nullptr) {
                TreeNode *res = root->left;
                delete root;
                return res;
            }
            root->val = getMinValue(root->right);
            root->right = deleteNode(root->right, root->val);
        } else if (root->val > key) {
            root->left = deleteNode(root->left, key);
        } else
            root->right = deleteNode(root->right, key);
        return root;
    }

    int getMinValue(TreeNode *node) {
        while (node->left != nullptr)
            node = node->left;
        return node->val;
    }
};
