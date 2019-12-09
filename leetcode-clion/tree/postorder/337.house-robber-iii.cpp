/*
 * @lc app=leetcode id=337 lang=cpp
 *
 * [337] House Robber III
 *
 * https://leetcode.com/problems/house-robber-iii/description/
 *
 * algorithms
 * Medium (49.12%)
 * Total Accepted:    121.1K
 * Total Submissions: 246.6K
 * Testcase Example:  '[3,2,3,null,3,null,1]'
 *
 * The thief has found himself a new place for his thievery again. There is
 * only one entrance to this area, called the "root." Besides the root, each
 * house has one and only one parent house. After a tour, the smart thief
 * realized that "all houses in this place forms a binary tree". It will
 * automatically contact the police if two directly-linked houses were broken
 * into on the same night.
 * 
 * Determine the maximum amount of money the thief can rob tonight without
 * alerting the police.
 * 
 * Example 1:
 * 
 * 
 * Input: [3,2,3,null,3,null,1]
 * 
 * ⁠    3
 * ⁠   / \
 * ⁠  2   3
 * ⁠   \   \ 
 * ⁠    3   1
 * 
 * Output: 7 
 * Explanation: Maximum amount of money the thief can rob = 3 + 3 + 1 = 7.
 * 
 * Example 2:
 * 
 * 
 * Input: [3,4,5,1,3,null,1]
 * 
 * 3
 * ⁠   / \
 * ⁠  4   5
 * ⁠ / \   \ 
 * ⁠1   3   1
 * 
 * Output: 9
 * Explanation: Maximum amount of money the thief can rob = 4 + 5 = 9.
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

/*
 * 思路：bfs
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

    // tle
    int rob1(TreeNode *root) {
        if (root == NULL) return 0;
        int lhs = rob(root->left), rhs = rob(root->right);
        int ll = root->left ? rob(root->left->left) : 0;
        int lr = root->left ? rob(root->left->right) : 0;
        int rl = root->right ? rob(root->right->left) : 0;
        int rr = root->right ? rob(root->right->right) : 0;
        return max(lhs + rhs, root->val + ll + lr + rl + rr);
    }

    int helper(TreeNode *root, int &l, int &r) {
        if (root == NULL) return 0;
        int ll = 0, lr = 0, rl = 0, rr = 0;
        l = helper(root->left, ll, lr);
        r = helper(root->right, rl, rr);
        return max(root->val + ll + lr + rl + rr, l + r);
    }

    // 12ms, 20.6MB, 93.3%
    int rob(TreeNode *root) {
        int l = 0, r = 0;
        return helper(root, l, r);
    }
};
