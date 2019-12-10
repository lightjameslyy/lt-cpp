/*
 * @lc app=leetcode id=270 lang=cpp
 *
 * [270] Closest Binary Search Tree Value
 *
 * https://leetcode.com/problems/closest-binary-search-tree-value/description/
 *
 * algorithms
 * Easy (45.14%)
 * Total Accepted:    100.2K
 * Total Submissions: 222K
 * Testcase Example:  '[4,2,5,1,3]\n3.714286'
 *
 * Given a non-empty binary search tree and a target value, find the value in
 * the BST that is closest to the target.
 * 
 * Note:
 * 
 * 
 * Given target value is a floating point.
 * You are guaranteed to have only one unique value in the BST that is closest
 * to the target.
 * 
 * 
 * Example:
 * 
 * 
 * Input: root = [4,2,5,1,3], target = 3.714286
 * 
 * ⁠   4
 * ⁠  / \
 * ⁠ 2   5
 * ⁠/ \
 * 1   3
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

#include <stack>
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

    int closestValue(TreeNode *root, double target) {
        if (!root) return 0;
        stack<TreeNode *> s;
        while (root) {
            s.push(root);
            root = root->left;
        }
        int res;
        double diff = 1LL << 32;
        while (!s.empty()) {
            root = s.top();
            double tmpDiff = (root->val < target ? target - root->val : root->val - target);
            if (tmpDiff < diff) {
                res = root->val;
                diff = tmpDiff;
            }
            if (root->val > target)
                return res;
            s.pop();
            root = root->right;
            while (root) {
                s.push(root);
                root = root->left;
            }
        }
        return res;
    }
};
