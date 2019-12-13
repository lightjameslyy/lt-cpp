/*
 * @lc app=leetcode id=25 lang=cpp
 *
 * [25] Reverse Nodes in k-Group
 *
 * https://leetcode.com/problems/reverse-nodes-in-k-group/description/
 *
 * algorithms
 * Hard (38.37%)
 * Total Accepted:    214.2K
 * Total Submissions: 558.2K
 * Testcase Example:  '[1,2,3,4,5]\n2'
 *
 * Given a linked list, reverse the nodes of a linked list k at a time and
 * return its modified list.
 * 
 * k is a positive integer and is less than or equal to the length of the
 * linked list. If the number of nodes is not a multiple of k then left-out
 * nodes in the end should remain as it is.
 * 
 * 
 * 
 * 
 * Example:
 * 
 * Given this linked list: 1->2->3->4->5
 * 
 * For k = 2, you should return: 2->1->4->3->5
 * 
 * For k = 3, you should return: 3->2->1->4->5
 * 
 * Note:
 * 
 * 
 * Only constant extra memory is allowed.
 * You may not alter the values in the list's nodes, only nodes itself may be
 * changed.
 * 
 * 
 */
/**
 * Definition for singly-linked list.
  struct ListNode {
      int val;
      ListNode *next;
      ListNode(int x) : val(x), next(NULL) {}
  };
 */

class Solution {
public:
    struct ListNode {
        int val;
        ListNode *next;

        ListNode(int x) : val(x), next(NULL) {}
    };

/*
 *     dummy   1  ->  2  ->  3  ->  4  ->  5
 *       ^     ^      ^
 *      res   head   cur
 */
    ListNode *reverseKGroup(ListNode *head, int k) {
        if (!head || k < 2) return head;
        ListNode *dummy = new ListNode(0);
        dummy->next = head;
        ListNode *res = head;
        int len = 0;
        while (res) {
            ++len;
            res = res->next;
        }
        res = dummy;
        for (int i = 0; i < len / k; ++i) {
            for (int j = 0; j < k - 1; ++j) {
                ListNode *cur = head->next;
                head->next = cur->next;
                cur->next = res->next;
                res->next = cur;
            }
            res = head;
            head = head->next;
        }
        res = dummy->next;
        delete dummy;
        return res;
    }
};
