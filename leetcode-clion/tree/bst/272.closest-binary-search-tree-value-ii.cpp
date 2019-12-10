/*
 * @lc app=leetcode id=272 lang=cpp
 *
 * [272] Closest Binary Search Tree Value II
 *
 * https://leetcode.com/problems/closest-binary-search-tree-value-ii/description/
 *
 * algorithms
 * Hard (47.34%)
 * Total Accepted:    44.8K
 * Total Submissions: 94.6K
 * Testcase Example:  '[4,2,5,1,3]\n3.714286\n2'
 *
 * Given a non-empty binary search tree and a target value, find k values in
 * the BST that are closest to the target.
 * 
 * Note:
 * 
 * 
 * Given target value is a floating point.
 * You may assume k is always valid, that is: k ≤ total nodes.
 * You are guaranteed to have only one unique set of k values in the BST that
 * are closest to the target.
 * 
 * 
 * Example:
 * 
 * 
 * Input: root = [4,2,5,1,3], target = 3.714286, and k = 2
 * 
 * ⁠   4
 * ⁠  / \
 * ⁠ 2   5
 * ⁠/ \
 * 1   3
 * 
 * Output: [4,3]
 * 
 * Follow up:
 * Assume that the BST is balanced, could you solve it in less than O(n)
 * runtime (where n = total nodes)?
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
#include <queue>
#include <stack>

using namespace std;

class Solution {
public:
    struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;

        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
    };

    double diff(int num, double target) {
        if (num > target)
            return num - target;
        return target - num;
    }

    vector<int> closestKValues(TreeNode *root, double target, int k) {
        auto cmp = [=](int a, int b) {
            return diff(a, target) < diff(b, target);
        };
        priority_queue<int, vector<int>, decltype(cmp)> heap(cmp);
        stack<TreeNode *> s;
        while (root) {
            s.push(root);
            root = root->left;
        }
        int greaterCount = 0;
        while (!s.empty()) {
            root = s.top();
            s.pop();
            if (heap.size() == k) {
                if (diff(root->val, target) < diff(heap.top(), target)) {
                    heap.pop();
                    heap.push(root->val);
                }
            } else {
                heap.push(root->val);
            }
            if (root->val > target) {
                ++greaterCount;
                if (greaterCount >= k)
                    break;
            }
            root = root->right;
            while (root) {
                s.push(root);
                root = root->left;
            }
        }
        vector<int> res;
        while (!heap.empty()) {
            res.push_back(heap.top());
            heap.pop();
        }
        return res;
    }
};
