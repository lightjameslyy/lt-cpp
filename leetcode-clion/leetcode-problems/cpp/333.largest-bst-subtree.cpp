/*
 * @lc app=leetcode id=333 lang=cpp
 *
 * [333] Largest BST Subtree
 *
 * https://leetcode.com/problems/largest-bst-subtree/description/
 *
 * algorithms
 * Medium (34.24%)
 * Total Accepted:    36.9K
 * Total Submissions: 107.8K
 * Testcase Example:  '[10,5,15,1,8,null,7]'
 *
 * Given a binary tree, find the largest subtree which is a Binary Search Tree
 * (BST), where largest means subtree with largest number of nodes in it.
 * 
 * Note:
 * A subtree must include all of its descendants.
 * 
 * Example:
 * 
 * 
 * Input: [10,5,15,1,8,null,7]
 * 
 * ⁠  10 
 * ⁠  / \ 
 * ⁠ 5  15 
 * ⁠/ \   \ 
 * 1   8   7
 * 
 * Output: 3
 * Explanation: The Largest BST Subtree in this case is the highlighted one.
 * ⁠            The return value is the subtree's size, which is 3.
 * 
 * 
 * Follow up:
 * Can you figure out ways to solve it with O(n) time complexity?
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
    int largestBSTSubtree(TreeNode* root) {
        
    }
};
