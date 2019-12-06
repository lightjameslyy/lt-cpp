/*
 * @lc app=leetcode id=365 lang=cpp
 *
 * [365] Water and Jug Problem
 *
 * https://leetcode.com/problems/water-and-jug-problem/description/
 *
 * algorithms
 * Medium (29.63%)
 * Total Accepted:    31.9K
 * Total Submissions: 107.7K
 * Testcase Example:  '3\n5\n4'
 *
 * You are given two jugs with capacities x and y litres. There is an infinite
 * amount of water supply available. You need to determine whether it is
 * possible to measure exactly z litres using these two jugs.
 * 
 * If z liters of water is measurable, you must have z liters of water
 * contained within one or both buckets by the end.
 * 
 * Operations allowed:
 * 
 * 
 * Fill any of the jugs completely with water.
 * Empty any of the jugs.
 * Pour water from one jug into another till the other jug is completely full
 * or the first jug itself is empty.
 * 
 * 
 * Example 1: (From the famous "Die Hard" example)
 * 
 * 
 * Input: x = 3, y = 5, z = 4
 * Output: True
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: x = 2, y = 6, z = 5
 * Output: False
 * 
 */

/*
 * greatest common divisor
 * if gcd == 1 (x和y互质)，z in [1,x+y]
 * else z in [1,x+y] && z==n*gcd
 */

class Solution {
public:
    int getGcd(int x, int y) {
        if (x == 0)
            return y;
        return getGcd(y % x, x);
    }

    // 4ms, 7.9MB, 53.04%
    bool canMeasureWater(int x, int y, int z) {
        if (x > y) return canMeasureWater(y, x, z);
        int gcd = getGcd(x, y);
        if (gcd == 0)
            return z == 0;
        return z % gcd == 0 && z <= (x + y);
    }
};
