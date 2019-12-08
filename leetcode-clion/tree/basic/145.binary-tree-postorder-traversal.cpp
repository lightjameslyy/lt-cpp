/*
 * @lc app=leetcode id=145 lang=cpp
 *
 * [145] Binary Tree Postorder Traversal
 *
 * https://leetcode.com/problems/binary-tree-postorder-traversal/description/
 *
 * algorithms
 * Hard (50.84%)
 * Total Accepted:    300.7K
 * Total Submissions: 591.5K
 * Testcase Example:  '[1,null,2,3]'
 *
 * Given a binary tree, return the postorder traversal of its nodes' values.
 * 
 * Example:
 * 
 * 
 * Input: [1,null,2,3]
 * ⁠  1
 * ⁠   \
 * ⁠    2
 * ⁠   /
 * ⁠  3
 * 
 * Output: [3,2,1]
 * 
 * 
 * Follow up: Recursive solution is trivial, could you do it iteratively?
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
    struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;

        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
    };

    enum OpType {
        RECURSIVE, PROCESS
    };
    struct Cmd {
        TreeNode *node;
        OpType opType;
    };

    // 0ms, 9.2MB, 100%
    vector<int> postorderTraversal(TreeNode *root) {
        vector<int> res;
        if (root == NULL) return res;
        stack <Cmd> stk;
        stk.push(Cmd{root, RECURSIVE});
        while (!stk.empty()) {
            Cmd cmd = stk.top();
            stk.pop();
            switch (cmd.opType) {
                case PROCESS: {
                    res.push_back(cmd.node->val);
                    break;
                }
                case RECURSIVE: {
                    cmd.opType = PROCESS;
                    stk.push(cmd);
                    if (cmd.node->right != NULL)
                        stk.push(Cmd{cmd.node->right, RECURSIVE});
                    if (cmd.node->left != NULL)
                        stk.push(Cmd{cmd.node->left, RECURSIVE});
                    break;
                }
                default:
                    break;
            }
        }
        return res;
    }
};
