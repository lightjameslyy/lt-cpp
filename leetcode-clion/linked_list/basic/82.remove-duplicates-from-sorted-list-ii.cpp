/*
 * @lc app=leetcode id=82 lang=cpp
 *
 * [82] Remove Duplicates from Sorted List II
 *
 * https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/description/
 *
 * algorithms
 * Medium (34.46%)
 * Total Accepted:    206.9K
 * Total Submissions: 600.4K
 * Testcase Example:  '[1,2,3,3,4,4,5]'
 *
 * Given a sorted linked list, delete all nodes that have duplicate numbers,
 * leaving only distinct numbers from the original list.
 * 
 * Example 1:
 * 
 * 
 * Input: 1->2->3->3->4->4->5
 * Output: 1->2->5
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: 1->1->1->2->3
 * Output: 2->3
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

    ListNode *deleteDuplicates(ListNode *head) {
        ListNode *dummy = new ListNode(0);
        dummy->next = head;
        head = dummy;
        while (head->next) {
            ListNode *p1 = head->next;
            ListNode *p2 = p1->next;
            if (!p2)
                break;
            if (p1->val == p2->val) {
                int val = p1->val;
                while (p1 && p1->val == val) {
                    p2 = p1;
                    p1 = p1->next;
                    delete p2;
                }
                head->next = p1;
            } else {
                head = head->next;
            }
        }
        head = dummy->next;
        delete dummy;
        return head;
    }
};
