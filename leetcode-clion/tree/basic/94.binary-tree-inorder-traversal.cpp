/*
 * @lc app=leetcode id=94 lang=cpp
 *
 * [94] Binary Tree Inorder Traversal
 *
 * https://leetcode.com/problems/binary-tree-inorder-traversal/description/
 *
 * algorithms
 * Medium (59.18%)
 * Total Accepted:    556.4K
 * Total Submissions: 940.2K
 * Testcase Example:  '[1,null,2,3]'
 *
 * Given a binary tree, return the inorder traversal of its nodes' values.
 * 
 * Example:
 * 
 * 
 * Input: [1,null,2,3]
 * ⁠  1
 * ⁠   \
 * ⁠    2
 * ⁠   /
 * ⁠  3
 * 
 * Output: [1,3,2]
 * 
 * Follow up: Recursive solution is trivial, could you do it iteratively?
 * 
 */

/*
 * 思路：stack
 */

#include <vector>
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

    enum OpType {
        INORDER, PROCESS
    };
    struct Cmd {
        TreeNode *node;
        OpType opType;
    };

    // 0ms, 9MB, 100%
    vector<int> inorderTraversal(TreeNode *root) {
        vector<int> res;
        if (root == NULL) return res;
        stack<Cmd> stk;
        stk.push(Cmd{root, INORDER});
        while (!stk.empty()) {
            Cmd cmd = stk.top();
            stk.pop();
            switch (cmd.opType) {
                case PROCESS: {
                    res.push_back(cmd.node->val);
                    break;
                }
                case INORDER: {
                    if (cmd.node->right != NULL)
                        stk.push(Cmd{cmd.node->right, INORDER});
                    cmd.opType = PROCESS;
                    stk.push(cmd);
                    if (cmd.node->left != NULL)
                        stk.push(Cmd{cmd.node->left, INORDER});
                    break;
                }
                default:
                    break;
            }
        }
        return res;
    }
};
