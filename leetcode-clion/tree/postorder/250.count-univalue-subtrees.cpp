/*
 * @lc app=leetcode id=250 lang=cpp
 *
 * [250] Count Univalue Subtrees
 *
 * https://leetcode.com/problems/count-univalue-subtrees/description/
 *
 * algorithms
 * Medium (50.43%)
 * Total Accepted:    48K
 * Total Submissions: 95.2K
 * Testcase Example:  '[5,1,5,5,5,null,5]'
 *
 * Given a binary tree, count the number of uni-value subtrees.
 * 
 * A Uni-value subtree means all nodes of the subtree have the same value.
 * 
 * Example :
 * 
 * 
 * Input:  root = [5,1,5,5,5,null,5]
 * 
 * ⁠             5
 * ⁠            / \
 * ⁠           1   5
 * ⁠          / \   \
 * ⁠         5   5   5
 * 
 * Output: 4
 * 
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
class Solution {
public:
    struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;

        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
    };

    bool dfs(TreeNode *root, int &res) {
        if (root->left == NULL && root->right == NULL) {
            ++res;
            return true;
        } else if (root->right == NULL) {
            if (dfs(root->left, res) && root->val == root->left->val) {
                ++res;
                return true;
            }
        } else if (root->left == NULL) {
            if (dfs(root->right, res) && root->val == root->right->val) {
                ++res;
                return true;
            }
        } else {
            // 此处要防止逻辑短路(short-circuit evaluation)
            bool lhs = dfs(root->left, res), rhs = dfs(root->right, res);
            if (lhs && rhs && (root->val == root->left->val) && (root->val == root->right->val)) {
                ++res;
                return true;
            }
        }
        return false;
    }

    int countUnivalSubtrees(TreeNode *root) {
        if (root == NULL) return 0;
        int res = 0;
        dfs(root, res);
        return res;
    }
};
