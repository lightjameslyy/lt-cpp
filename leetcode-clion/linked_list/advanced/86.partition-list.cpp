/*
 * @lc app=leetcode id=86 lang=cpp
 *
 * [86] Partition List
 *
 * https://leetcode.com/problems/partition-list/description/
 *
 * algorithms
 * Medium (38.82%)
 * Total Accepted:    183.2K
 * Total Submissions: 471.9K
 * Testcase Example:  '[1,4,3,2,5,2]\n3'
 *
 * Given a linked list and a value x, partition it such that all nodes less
 * than x come before nodes greater than or equal to x.
 * 
 * You should preserve the original relative order of the nodes in each of the
 * two partitions.
 * 
 * Example:
 * 
 * 
 * Input: head = 1->4->3->2->5->2, x = 3
 * Output: 1->2->2->4->3->5
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

    ListNode *partition(ListNode *head, int x) {
        if (!head || !head->next) return head;
        ListNode *left = new ListNode(0);
        ListNode *right = new ListNode(0);
        ListNode *l = left;
        ListNode *r = right;
        while (head) {
            if (head->val < x) {
                l->next = head;
                l = l->next;
            } else {
                r->next = head;
                r = r->next;
            }
            head = head->next;
        }
        r->next = NULL;
        l->next = right->next;
        head = left->next;
        delete left;
        delete right;
        return head;
    }
};
