/*
 * @lc app=leetcode id=113 lang=cpp
 *
 * [113] Path Sum II
 *
 * https://leetcode.com/problems/path-sum-ii/description/
 *
 * algorithms
 * Medium (42.80%)
 * Total Accepted:    266.8K
 * Total Submissions: 623.3K
 * Testcase Example:  '[5,4,8,11,null,13,4,7,2,null,null,5,1]\n22'
 *
 * Given a binary tree and a sum, find all root-to-leaf paths where each path's
 * sum equals the given sum.
 * 
 * Note: A leaf is a node with no children.
 * 
 * Example:
 * 
 * Given the below binary tree and sum = 22,
 * 
 * 
 * ⁠     5
 * ⁠    / \
 * ⁠   4   8
 * ⁠  /   / \
 * ⁠ 11  13  4
 * ⁠/  \    / \
 * 7    2  5   1
 * 
 * 
 * Return:
 * 
 * 
 * [
 * ⁠  [5,4,11,2],
 * ⁠  [5,8,4,5]
 * ]
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

    void dfs(TreeNode *node, int diff, vector<int> &tmp, vector<vector<int>> &res) {
        tmp.push_back(node->val);
        diff -= node->val;
        if (node->left == NULL && node->right == NULL) {
            if (diff == 0)
                res.push_back(tmp);
            tmp.pop_back();
            return;
        }
        if (node->left)
            dfs(node->left, diff, tmp, res);
        if (node->right)
            dfs(node->right, diff, tmp, res);
        tmp.pop_back();
    }

    // 8ms, 19.8MB, 96.8%
    vector<vector<int>> pathSum(TreeNode *root, int sum) {
        vector<vector<int>> res;
        if (root == NULL) return res;
        vector<int> tmp;
        dfs(root, sum, tmp, res);
        return res;
    }
};
