/*
 * @lc app=leetcode id=234 lang=cpp
 *
 * [234] Palindrome Linked List
 *
 * https://leetcode.com/problems/palindrome-linked-list/description/
 *
 * algorithms
 * Easy (37.28%)
 * Total Accepted:    313.7K
 * Total Submissions: 841.5K
 * Testcase Example:  '[1,2]'
 *
 * Given a singly linked list, determine if it is a palindrome.
 * 
 * Example 1:
 * 
 * 
 * Input: 1->2
 * Output: false
 * 
 * Example 2:
 * 
 * 
 * Input: 1->2->2->1
 * Output: true
 * 
 * Follow up:
 * Could you do it in O(n) time and O(1) space?
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

    bool isPalindrome(ListNode *head) {
        if (!head || !head->next) return true;
        ListNode *pre = NULL;
        ListNode *slow = head;
        ListNode *fast = head->next;
        // reverse first half
        while (fast && fast->next) {
            fast = fast->next->next;
            ListNode *tmp = slow;
            slow = slow->next;
            tmp->next = pre;
            pre = tmp;
        }
        bool isOdd = !fast;
        fast = slow->next;
        slow->next = pre;
        if (isOdd)
            slow = slow->next;
        while (slow) {
            if (slow->val != fast->val)
                return false;
            slow = slow->next;
            fast = fast->next;
        }
        return true;
    }
};
