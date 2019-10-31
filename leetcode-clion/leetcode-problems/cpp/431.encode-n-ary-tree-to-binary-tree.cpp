/*
 * @lc app=leetcode id=431 lang=cpp
 *
 * [431] Encode N-ary Tree to Binary Tree
 *
 * https://leetcode.com/problems/encode-n-ary-tree-to-binary-tree/description/
 *
 * algorithms
 * Hard (66.54%)
 * Total Accepted:    3.5K
 * Total Submissions: 5.3K
 * Testcase Example:  '{"$id":"1","children":[{"$id":"2","children":[{"$id":"5","children":[],"val":5},{"$id":"6","children":[],"val":6}],"val":3},{"$id":"3","children":[],"val":2},{"$id":"4","children":[],"val":4}],"val":1}'
 *
 * Design an algorithm to encode an N-ary tree into a binary tree and decode
 * the binary tree to get the original N-ary tree. An N-ary tree is a rooted
 * tree in which each node has no more than N children. Similarly, a binary
 * tree is a rooted tree in which each node has no more than 2 children. There
 * is no restriction on how your encode/decode algorithm should work. You just
 * need to ensure that an N-ary tree can be encoded to a binary tree and this
 * binary tree can be decoded to the original N-nary tree structure.
 * 
 * For example, you may encode the following 3-ary tree to a binary tree in
 * this way:
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * Note that the above is just an example which might or might not work. You do
 * not necessarily need to follow this format, so please be creative and come
 * up with different approaches yourself.
 * 
 * 
 * 
 * Note:
 * 
 * 
 * N is in the range of  [1, 1000]
 * Do not use class member/global/static variables to store states. Your encode
 * and decode algorithms should be stateless.
 * 
 * 
 */
/*
// Definition for a Node.
class Node {
public:
    int val = NULL;
    vector<Node*> children;

    Node() {}

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
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
class Codec {
public:

    // Encodes an n-ary tree to a binary tree.
    TreeNode* encode(Node* root) {
        
    }

    // Decodes your binary tree to an n-ary tree.
    Node* decode(TreeNode* root) {
        
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.decode(codec.encode(root));
