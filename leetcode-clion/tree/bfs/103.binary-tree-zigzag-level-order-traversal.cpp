/*
 * @lc app=leetcode id=103 lang=cpp
 *
 * [103] Binary Tree Zigzag Level Order Traversal
 *
 * https://leetcode.com/problems/binary-tree-zigzag-level-order-traversal/description/
 *
 * algorithms
 * Medium (43.80%)
 * Total Accepted:    267.3K
 * Total Submissions: 610.3K
 * Testcase Example:  '[3,9,20,null,null,15,7]'
 *
 * Given a binary tree, return the zigzag level order traversal of its nodes'
 * values. (ie, from left to right, then right to left for the next level and
 * alternate between).
 * 
 * 
 * For example:
 * Given binary tree [3,9,20,null,null,15,7],
 * 
 * ⁠   3
 * ⁠  / \
 * ⁠ 9  20
 * ⁠   /  \
 * ⁠  15   7
 * 
 * 
 * 
 * return its zigzag level order traversal as:
 * 
 * [
 * ⁠ [3],
 * ⁠ [20,9],
 * ⁠ [15,7]
 * ]
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

#include <vector>
#include <deque>

using namespace std;

class Solution {
public:
    struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;

        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
    };

    vector<vector<int>> zigzagLevelOrder(TreeNode *root) {
        vector<vector<int>> res;
        if (root == NULL) return res;
        deque<TreeNode *> q;
        q.push_back(root);
        bool leftToRight = true;
        while (!q.empty()) {
            res.push_back(vector<int>());
            int size = q.size();
            if (leftToRight) {
                for (int i = 0; i < size; ++i) {
                    TreeNode *tmp = q.front();
                    q.pop_front();
                    res.back().push_back(tmp->val);
                    if (tmp->left)
                        q.push_back(tmp->left);
                    if (tmp->right)
                        q.push_back(tmp->right);
                }
            } else {
                for (int i = 0; i < size; ++i) {
                    TreeNode *tmp = q.back();
                    q.pop_back();
                    res.back().push_back(tmp->val);
                    if (tmp->right)
                        q.push_front(tmp->right);
                    if (tmp->left)
                        q.push_front(tmp->left);
                }
            }
            leftToRight = 1 - leftToRight;
        }
        return res;
    }
};
