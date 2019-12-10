/*
 * @lc app=leetcode id=203 lang=cpp
 *
 * [203] Remove Linked List Elements
 *
 * https://leetcode.com/problems/remove-linked-list-elements/description/
 *
 * algorithms
 * Easy (36.62%)
 * Total Accepted:    259.4K
 * Total Submissions: 708.5K
 * Testcase Example:  '[1,2,6,3,4,5,6]\n6'
 *
 * Remove all elements from a linked list of integers that have value val.
 * 
 * Example:
 * 
 * 
 * Input:  1->2->6->3->4->5->6, val = 6
 * Output: 1->2->3->4->5
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

    ListNode *removeElements(ListNode *head, int val) {
        ListNode *dummy = new ListNode(0);
        dummy->next = head;
        head = dummy;
        while (head->next) {
            ListNode *tmp = head->next;
            if (tmp->val == val) {
                head->next = tmp->next;
                delete tmp;
            } else {
                head = head->next;
            }
        }
        head = dummy->next;
        delete dummy;
        return head;
    }
};
