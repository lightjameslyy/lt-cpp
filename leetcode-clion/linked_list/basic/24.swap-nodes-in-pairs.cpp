/*
 * @lc app=leetcode id=24 lang=cpp
 *
 * [24] Swap Nodes in Pairs
 *
 * https://leetcode.com/problems/swap-nodes-in-pairs/description/
 *
 * algorithms
 * Medium (46.92%)
 * Total Accepted:    370.7K
 * Total Submissions: 790.1K
 * Testcase Example:  '[1,2,3,4]'
 *
 * Given a linked list, swap every two adjacent nodes and return its head.
 * 
 * You may not modify the values in the list's nodes, only nodes itself may be
 * changed.
 * 
 * 
 * 
 * Example:
 * 
 * 
 * Given 1->2->3->4, you should return the list as 2->1->4->3.
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

    ListNode *swapPairs(ListNode *head) {
        if (!head || !head->next) return head;
        ListNode *dummy = new ListNode(0);
        ListNode *pre = dummy;
        ListNode *p1 = head;
        while (p1 && p1->next) {
            ListNode *p2 = p1->next;
            ListNode *p3 = p2->next;
            pre->next = p2;
            p2->next = p1;
            p1->next = p3;
            pre = p1;
            p1 = p3;
        }
        head = dummy->next;
        delete dummy;
        return head;
    }
};
