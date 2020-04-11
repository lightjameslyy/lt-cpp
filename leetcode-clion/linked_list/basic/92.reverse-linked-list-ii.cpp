/*
 * @lc app=leetcode id=92 lang=cpp
 *
 * [92] Reverse Linked List II
 *
 * https://leetcode.com/problems/reverse-linked-list-ii/description/
 *
 * algorithms
 * Medium (36.41%)
 * Total Accepted:    222.5K
 * Total Submissions: 611.1K
 * Testcase Example:  '[1,2,3,4,5]\n2\n4'
 *
 * Reverse a linked list from position m to n. Do it in one-pass.
 *
 * Note: 1 ≤ m ≤ n ≤ length of list.
 *
 * Example:
 *
 *
 * Input: 1->2->3->4->5->NULL, m = 2, n = 4
 * Output: 1->4->3->2->5->NULL
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
// struct ListNode {
//     int val;
//     ListNode *next;

//     ListNode(int x) : val(x), next(NULL) {}
// };

class Solution {
  public:
    ListNode *reverseBetween1(ListNode *head, int m, int n) {
        ListNode *dummy = new ListNode(0);
        dummy->next = head;
        ListNode *pre = dummy;
        for (int i = 0; i < m - 1; ++i)
            pre = pre->next;
        ListNode *post = pre->next;
        for (int i = m; i < n; ++i) {
            head = post->next;
            post->next = head->next;
            head->next = pre->next;
            pre->next = head;
        }
        head = dummy->next;
        delete dummy;
        return head;
    }

    ListNode *post = nullptr;

    ListNode *reverseN(ListNode *head, int n) {
        if (n == 1) {
            post = head->next;
            return head;
        }
        ListNode *last = reverseN(head->next, n - 1);
        head->next->next = head;
        head->next = post;
        return last;
    }

    // recursive solution
    ListNode *reverseBetween(ListNode *head, int m, int n) {
        if (m == 1)
            return reverseN(head, n);
        head->next = reverseBetween(head->next, m - 1, n - 1);
        return head;
    }
};
