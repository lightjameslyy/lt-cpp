/*
 * @lc app=leetcode id=622 lang=cpp
 *
 * [622] Design Circular Queue
 *
 * https://leetcode.com/problems/design-circular-queue/description/
 *
 * algorithms
 * Medium (41.24%)
 * Total Accepted:    38.4K
 * Total Submissions: 93K
 * Testcase Example:  '["MyCircularQueue","enQueue","enQueue","enQueue","enQueue","Rear","isFull","deQueue","enQueue","Rear"]\n' +
  '[[3],[1],[2],[3],[4],[],[],[],[4],[]]'
 *
 * Design your implementation of the circular queue. The circular queue is a
 * linear data structure in which the operations are performed based on FIFO
 * (First In First Out) principle and the last position is connected back to
 * the first position to make a circle. It is also called "Ring Buffer".
 * 
 * One of the benefits of the circular queue is that we can make use of the
 * spaces in front of the queue. In a normal queue, once the queue becomes
 * full, we cannot insert the next element even if there is a space in front of
 * the queue. But using the circular queue, we can use the space to store new
 * values.
 * 
 * Your implementation should support following operations:
 * 
 * 
 * MyCircularQueue(k): Constructor, set the size of the queue to be k.
 * Front: Get the front item from the queue. If the queue is empty, return
 * -1.
 * Rear: Get the last item from the queue. If the queue is empty, return
 * -1.
 * enQueue(value): Insert an element into the circular queue. Return true if
 * the operation is successful.
 * deQueue(): Delete an element from the circular queue. Return true if the
 * operation is successful.
 * isEmpty(): Checks whether the circular queue is empty or not.
 * isFull(): Checks whether the circular queue is full or not.
 * 
 * 
 * 
 * 
 * Example:
 * 
 * 
 * MyCircularQueue circularQueue = new MyCircularQueue(3); // set the size to
 * be 3
 * circularQueue.enQueue(1);  // return true
 * circularQueue.enQueue(2);  // return true
 * circularQueue.enQueue(3);  // return true
 * circularQueue.enQueue(4);  // return false, the queue is full
 * circularQueue.Rear();  // return 3
 * circularQueue.isFull();  // return true
 * circularQueue.deQueue();  // return true
 * circularQueue.enQueue(4);  // return true
 * circularQueue.Rear();  // return 4
 * 
 * 
 * 
 * Note:
 * 
 * 
 * All values will be in the range of [0, 1000].
 * The number of operations will be in the range of [1, 1000].
 * Please do not use the built-in Queue library.
 * 
 * 
 */
class MyCircularQueue {
public:
    /** Initialize your data structure here. Set the size of the queue to be k. */
    MyCircularQueue(int k) {
        
    }
    
    /** Insert an element into the circular queue. Return true if the operation is successful. */
    bool enQueue(int value) {
        
    }
    
    /** Delete an element from the circular queue. Return true if the operation is successful. */
    bool deQueue() {
        
    }
    
    /** Get the front item from the queue. */
    int Front() {
        
    }
    
    /** Get the last item from the queue. */
    int Rear() {
        
    }
    
    /** Checks whether the circular queue is empty or not. */
    bool isEmpty() {
        
    }
    
    /** Checks whether the circular queue is full or not. */
    bool isFull() {
        
    }
};

/**
 * Your MyCircularQueue object will be instantiated and called as such:
 * MyCircularQueue* obj = new MyCircularQueue(k);
 * bool param_1 = obj->enQueue(value);
 * bool param_2 = obj->deQueue();
 * int param_3 = obj->Front();
 * int param_4 = obj->Rear();
 * bool param_5 = obj->isEmpty();
 * bool param_6 = obj->isFull();
 */