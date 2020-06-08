/*
 * @lc app=leetcode id=1206 lang=cpp
 *
 * [1206] Design Skiplist
 *
 * https://leetcode.com/problems/design-skiplist/description/
 *
 * algorithms
 * Hard (60.04%)
 * Total Accepted:    1.2K
 * Total Submissions: 2.1K
 * Testcase Example:  '["Skiplist","add","add","add","search","add","search","erase","erase","search"]\r\n' +
  '[[],[1],[2],[3],[0],[4],[1],[0],[1],[1]]\r'
 *
 * Design a Skiplist without using any built-in libraries.
 *
 * A Skiplist is a data structure that takes O(log(n)) time to add, erase and
 * search. Comparing with treap and red-black tree which has the same function
 * and performance, the code length of Skiplist can be comparatively short and
 * the idea behind Skiplists are just simple linked lists.
 *
 * For example: we have a Skiplist containing [30,40,50,60,70,90] and we want
 * to add 80 and 45 into it. The Skiplist works this way:
 *
 *
 * Artyom Kalinin [CC BY-SA 3.0], via Wikimedia Commons
 *
 * You can see there are many layers in the Skiplist. Each layer is a sorted
 * linked list. With the help of the top layers, add , erase and search can be
 * faster than O(n). It can be proven that the average time complexity for each
 * operation is O(log(n)) and space complexity is O(n).
 *
 * To be specific, your design should include these functions:
 *
 *
 * bool search(int target) : Return whether the target exists in the Skiplist
 * or not.
 * void add(int num): Insert a value into the SkipList. 
 * bool erase(int num): Remove a value in the Skiplist. If num does not exist
 * in the Skiplist, do nothing and return false. If there exists multiple num
 * values, removing any one of them is fine.
 *
 *
 * See more about Skiplist : https://en.wikipedia.org/wiki/Skip_list
 *
 * Note that duplicates may exist in the Skiplist, your code needs to handle
 * this situation.
 *
 *
 *
 * Example:
 *
 *
 * Skiplist skiplist = new Skiplist();
 *
 * skiplist.add(1);
 * skiplist.add(2);
 * skiplist.add(3);
 * skiplist.search(0);   // return false.
 * skiplist.add(4);
 * skiplist.search(1);   // return true.
 * skiplist.erase(0);    // return false, 0 is not in skiplist.
 * skiplist.erase(1);    // return true.
 * skiplist.search(1);   // return false, 1 has already been erased.
 *
 *
 * Constraints:
 *
 *
 * 0 <= num, target <= 20000
 * At most 50000 calls will be made to search, add, and erase.
 *
 */
class Skiplist {
    struct Node {
        int val;
        Node **next;
        Node(int val, int level) : val(val) {
            if (level < 1)
                level = 1;
            next = new Node *[level];
            fill_n(next, level, nullptr);
        }
        ~Node() {
            delete[] next;
        }
    };

    const int MAX_LEVELS = 32;
    // const int P = 0.25;
    int levels;
    Node *head;
    Node **update;

  public:
    Skiplist() {
        levels = 1;
        head = new Node(INT_MIN, MAX_LEVELS);
        update = new Node*[MAX_LEVELS]; // preceeding nodes to be updated
        srand(chrono::system_clock::now().time_since_epoch().count());
    }

    int randomLevel() {
        int level = 1;
        while ((rand() % 4 == 0) && (level < MAX_LEVELS)) // P=1/4
            level++;
        return level;
    }

    bool search(int target) {
        Node *cur = head;
        // top-down
        for (int i = levels - 1; i >= 0; --i) { // downwards
            while (cur->next[i] != nullptr && cur->next[i]->val < target)   // forwards
                cur = cur->next[i];
        }
        return (cur->next[0] != nullptr) && (cur->next[0]->val == target);
    }

    void add(int num) {
        Node* cur = head;
        int level = randomLevel();
        Node* nodeToInsert = new Node(num, level);
        fill_n(update, levels, nullptr);
        // top-down
        for (int i = levels - 1; i >= 0; --i) { // downwards
            while (cur->next[i] != nullptr && cur->next[i]->val < num)  // forwards
                cur = cur->next[i];
            update[i] = cur;
        }
        // update nodes
        for (int i = 0; i < min(levels, level); ++i) {
            if (update[i] != nullptr) {
                nodeToInsert->next[i] = update[i]->next[i];
                update[i]->next[i] = nodeToInsert;
            }
        }
        if (level > levels) {   // expand levels
            for (int i = levels; i < level; ++i)
                head->next[i] = nodeToInsert;
            levels = level;
        }
    }

    bool erase(int num) {
        Node* cur = head;
        fill_n(update, levels, nullptr);
        // top-down
        for (int i = levels - 1; i >= 0; --i) { // downwards
            while (cur->next[i] != nullptr && cur->next[i]->val < num)  // forwards
                cur = cur->next[i];
            update[i] = cur;
        }

        Node* nodeToDel = cur->next[0];
        if (nodeToDel != nullptr && nodeToDel->val == num) {
            for (int i = levels-1; i >= 0; --i) {   // delete node
                if (update[i]->next[i] != nodeToDel)
                    continue;
                update[i]->next[i] = update[i]->next[i]->next[i];
            }
            for (int i = levels-1; i >= 0; --i) {   // shrink levels
                if (head->next[i] != nullptr)
                    break;
                levels--;
            }
            delete nodeToDel;
            return true;
        }
        return false;
    }
};

/**
 * Your Skiplist object will be instantiated and called as such:
 * Skiplist* obj = new Skiplist();
 * bool param_1 = obj->search(target);
 * obj->add(num);
 * bool param_3 = obj->erase(num);
 */
