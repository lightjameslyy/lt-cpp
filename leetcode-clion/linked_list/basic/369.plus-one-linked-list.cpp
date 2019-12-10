/*
 * @lc app=leetcode id=369 lang=cpp
 *
 * [369] Plus One Linked List
 *
 * https://leetcode.com/problems/plus-one-linked-list/description/
 *
 * algorithms
 * Medium (57.10%)
 * Total Accepted:    38.5K
 * Total Submissions: 67.4K
 * Testcase Example:  '[1,2,3]'
 *
 * Given a non-negative integer represented as non-empty a singly linked list
 * of digits, plus one to the integer.
 * 
 * You may assume the integer do not contain any leading zero, except the
 * number 0 itself.
 * 
 * The digits are stored such that the most significant digit is at the head of
 * the list.
 * 
 * 
 * Example :
 * 
 * 
 * Input: [1,2,3]
 * Output: [1,2,4]
 * 
 * 
 * 
 */
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    struct ListNode {
        int val;
        ListNode *next;

        ListNode(int x) : val(x), next(NULL) {}
    };

    void helper(ListNode *head) {
        if (!head || !carry) return;
        helper(head->next);
        int sum = head->val + carry;
        carry = sum / 10;
        head->val = sum % 10;
    }

    ListNode *plusOne(ListNode *head) {
        carry = 1;
        helper(head);
        if (carry) {
            ListNode *dummy = new ListNode(1);
            dummy->next = head;
            return dummy;
        }
        return head;
    }

private:
    int carry;
};
