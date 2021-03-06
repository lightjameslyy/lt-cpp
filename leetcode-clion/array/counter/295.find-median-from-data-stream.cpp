/*
 * @lc app=leetcode id=295 lang=cpp
 *
 * [295] Find Median from Data Stream
 *
 * https://leetcode.com/problems/find-median-from-data-stream/description/
 *
 * algorithms
 * Hard (36.29%)
 * Total Accepted:    105K
 * Total Submissions: 289.5K
 * Testcase Example:  '["MedianFinder","addNum","addNum","findMedian","addNum","findMedian"]\n[[],[1],[2],[],[3],[]]'
 *
 * Median is the middle value in an ordered integer list. If the size of the
 * list is even, there is no middle value. So the median is the mean of the two
 * middle value.
 * For example,
 *
 * [2,3,4], the median is 3
 *
 * [2,3], the median is (2 + 3) / 2 = 2.5
 *
 * Design a data structure that supports the following two operations:
 *
 *
 * void addNum(int num) - Add a integer number from the data stream to the data
 * structure.
 * double findMedian() - Return the median of all elements so far.
 *
 *
 *
 *
 * Example:
 *
 *
 * addNum(1)
 * addNum(2)
 * findMedian() -> 1.5
 * addNum(3)
 * findMedian() -> 2
 *
 *
 *
 *
 * Follow up:
 *
 *
 * If all integer numbers from the stream are between 0 and 100, how would you
 * optimize it?
 * If 99% of all integer numbers from the stream are between 0 and 100, how
 * would you optimize it?
 *
 *
 */

/*
 * 思路：大顶堆加小顶堆
 * 大顶堆放较小的一半，小顶堆放较大的一半
 */
class MedianFinder {
  public:
    int size;
    // bigger和smaller都是大顶堆，但是smaller存的是负数。
    priority_queue<int> bigger, smaller;

    int get_big() {
        return bigger.top();
    }

    int get_small() {
        return -smaller.top();
    }

    /** initialize your data structure here. */
    MedianFinder() {
        size = 0;
    }

    void addNum(int num) {
        if (size == 0) {
            bigger.push(num);
        } else if (size % 2 == 0) {
            if (num > get_small()) {
                bigger.push(get_small());
                smaller.pop();
                smaller.push(-num);
            } else
                bigger.push(num);
        } else {
            if (!smaller.empty() && num >= get_small()) {
                smaller.push(-num);
            } else {
                bigger.push(num);
                smaller.push(-get_big());
                bigger.pop();
            }
        }
        ++size;
    }

    double findMedian() {
        if (size == 0)
            return 0;
        if (size % 2 == 0) {
            return (1.0 * get_big() + 1.0 * get_small()) / 2.0;
        } else {
            return get_big();
        }
    }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */
