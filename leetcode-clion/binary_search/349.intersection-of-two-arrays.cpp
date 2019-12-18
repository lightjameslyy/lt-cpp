/*
 * @lc app=leetcode id=349 lang=cpp
 *
 * [349] Intersection of Two Arrays
 *
 * https://leetcode.com/problems/intersection-of-two-arrays/description/
 *
 * algorithms
 * Easy (57.52%)
 * Total Accepted:    267.1K
 * Total Submissions: 464.3K
 * Testcase Example:  '[1,2,2,1]\n[2,2]'
 *
 * Given two arrays, write a function to compute their intersection.
 * 
 * Example 1:
 * 
 * 
 * Input: nums1 = [1,2,2,1], nums2 = [2,2]
 * Output: [2]
 * 
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums1 = [4,9,5], nums2 = [9,4,9,8,4]
 * Output: [9,4]
 * 
 * 
 * Note:
 * 
 * 
 * Each element in the result must be unique.
 * The result can be in any order.
 * 
 * 
 * 
 * 
 */
#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
public:
    // my
    vector<int> intersection1(vector<int> &nums1, vector<int> &nums2) {
        vector<int> res;
        unordered_set<int> set1, set2;
        for (int val : nums1)
            set1.insert(val);
        for (int val : nums2) {
            if (set2.find(val) == set2.end() && set1.find(val) != set1.end()) {
                res.push_back(val);
                set2.insert(val);
            }
        }
        return res;
    }

    // copied, better
    vector<int> intersection(vector<int> &nums1, vector<int> &nums2) {
        vector<int> res;
        unordered_set<int> set1;
        for (int val : nums1)
            set1.insert(val);
        for (int val : nums2) {
            if (set1.find(val) != set1.end()) {
                res.push_back(val);
                set1.erase(val);
            }
        }
        return res;
    }
};
