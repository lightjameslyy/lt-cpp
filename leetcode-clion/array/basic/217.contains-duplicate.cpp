/*
 * @lc app=leetcode id=217 lang=cpp
 *
 * [217] Contains Duplicate
 *
 * https://leetcode.com/problems/contains-duplicate/description/
 *
 * algorithms
 * Easy (53.76%)
 * Total Accepted:    411K
 * Total Submissions: 764.5K
 * Testcase Example:  '[1,2,3,1]'
 *
 * Given an array of integers, find if the array contains any duplicates.
 * 
 * Your function should return true if any value appears at least twice in the
 * array, and it should return false if every element is distinct.
 * 
 * Example 1:
 * 
 * 
 * Input: [1,2,3,1]
 * Output: true
 * 
 * Example 2:
 * 
 * 
 * Input: [1,2,3,4]
 * Output: false
 * 
 * Example 3:
 * 
 * 
 * Input: [1,1,1,3,3,4,3,2,4,2]
 * Output: true
 * 
 */
#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
public:
    bool containsDuplicate(vector<int> &nums) {
        unordered_set<int> set;
        for (int n : nums) {
            if (set.find(n) != set.end())
                return true;
            set.insert(n);
        }
        return false;
    }
};
