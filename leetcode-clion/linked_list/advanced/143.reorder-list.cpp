/*
 * @lc app=leetcode id=143 lang=cpp
 *
 * [143] Reorder List
 *
 * https://leetcode.com/problems/reorder-list/description/
 *
 * algorithms
 * Medium (32.91%)
 * Total Accepted:    179.3K
 * Total Submissions: 544.8K
 * Testcase Example:  '[1,2,3,4]'
 *
 * Given a singly linked list L: L0→L1→…→Ln-1→Ln,
 * reorder it to: L0→Ln→L1→Ln-1→L2→Ln-2→…
 * 
 * You may not modify the values in the list's nodes, only nodes itself may be
 * changed.
 * 
 * Example 1:
 * 
 * 
 * Given 1->2->3->4, reorder it to 1->4->2->3.
 * 
 * Example 2:
 * 
 * 
 * Given 1->2->3->4->5, reorder it to 1->5->2->4->3.
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

    void reorderList(ListNode *head) {
        if (!head || !head->next) return;
        ListNode *slow = head;
        ListNode *fast = head->next;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        ListNode *pre = NULL;
        fast = slow->next;
        slow->next = NULL;
        slow = head;
        while (fast) {
            ListNode *tmp = fast;
            fast = fast->next;
            tmp->next = pre;
            pre = tmp;
        }
        while (pre) {
            ListNode *tmp = pre;
            pre = pre->next;
            tmp->next = slow->next;
            slow->next = tmp;
            slow = slow->next->next;
        }
    }
};
