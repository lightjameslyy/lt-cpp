/*
 * @lc app=leetcode id=146 lang=cpp
 *
 * [146] LRU Cache
 *
 * https://leetcode.com/problems/lru-cache/description/
 *
 * algorithms
 * Medium (28.10%)
 * Total Accepted:    375K
 * Total Submissions: 1.3M
 * Testcase Example:  '["LRUCache","put","put","get","put","get","put","get","get","get"]\n' +
  '[[2],[1,1],[2,2],[1],[3,3],[2],[4,4],[1],[3],[4]]'
 *
 * Design and implement a data structure for Least Recently Used (LRU) cache.
 * It should support the following operations: get and put.
 *
 * get(key) - Get the value (will always be positive) of the key if the key
 * exists in the cache, otherwise return -1.
 * put(key, value) - Set or insert the value if the key is not already present.
 * When the cache reached its capacity, it should invalidate the least recently
 * used item before inserting a new item.
 *
 * The cache is initialized with a positive capacity.
 *
 * Follow up:
 * Could you do both operations in O(1) time complexity?
 *
 * Example:
 *
 *
 * LRUCache cache = new LRUCache( 2 );
 *
 * cache.put(1, 1);
 * cache.put(2, 2);
 * cache.get(1);       // returns 1
 * cache.put(3, 3);    // evicts key 2
 * cache.get(2);       // returns -1 (not found)
 * cache.put(4, 4);    // evicts key 1
 * cache.get(1);       // returns -1 (not found)
 * cache.get(3);       // returns 3
 * cache.get(4);       // returns 4
 *
 *
 *
 *
 */

#include <unordered_map>

using namespace std;

class Node {
  public:
    int key, val;
    Node *prev, *next;
    Node(int k, int v) : key(k), val(v), prev(nullptr), next(nullptr) {}
};

class DoubleList {
  private:
    Node *head, *tail;
    int size_ = 0;

  public:
    DoubleList() {
        head = new Node(0, 0);
        tail = new Node(0, 0);
        head->next = tail;
        tail->prev = head;
    }

    void push_front(Node *node) {
        node->next = head->next;
        head->next = node;
        node->next->prev = node;
        node->prev = head;
        size_++;
    }

    Node *pop_back() {
        if (size_ == 0)
            return nullptr;
        Node *node = tail->prev;
        tail->prev = node->prev;
        node->prev->next = tail;
        size_--;
        return node;
    }

    void remove(Node *node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
        delete node;
        size_--;
    }

    void move_to_front(Node *node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
        size_--;
        push_front(node);
    }

    int size() const {
        return size_;
    }
};

class LRUCache {
  private:
    unordered_map<int, Node *> mp;
    DoubleList cache;
    int cap;

  public:
    LRUCache(int capacity) {
        cap = capacity;
    }

    int get(int key) {
        if (mp.find(key) == mp.end())
            return -1;
        int val = mp[key]->val;
        put(key, val);
        return val;
    }

    void put(int key, int value) {
        if (mp.find(key) != mp.end()) {
            cache.move_to_front(mp[key]);
            mp[key]->val = value;
        } else {
            Node *node = new Node(key, value);
            if (cap == cache.size()) {
                Node *tmp = cache.pop_back();
                mp.erase(tmp->key);
                delete tmp;
            }
            cache.push_front(node);
            mp[key] = node;
        }
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
