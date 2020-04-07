#include <vector>

using namespace std;

template <class T, class Comp>
class BinaryHeap {
  private:
    T *data_;
    int cap_;
    int size_ = 0;
    Comp comp_;

    void swap(int i, int j) {
        T tmp = data_[i];
        data_[i] = data_[j];
        data_[j] = tmp;
    }

  public:
    explicit BinaryHeap(int cap, Comp comp) : cap_(cap), comp_(comp) {
        // data in data_[1:cap_]
        data_ = new T[cap_ + 1];
    }
    ~BinaryHeap() {
        delete[] data_;
    }

    int left(int i) {
        return i << 1;
    }

    bool empty() const {
        return size_ == 0;
    }

    int right(int i) {
        return (i << 1) + 1;
    }

    int parent(int i) {
        return i >> 1;
    }

    T front() const {
        return data_[1];
    }

    void push_back(T val) {
        data_[++size_] = val;
        swim(size_);
    }

    T pop_front() {
        T res = data_[1];
        swap(1, size_--);
        sink(1);
        return res;
    }

    void swim(int k) {
        while (k > 1 && comp_(data_[parent(k)], data_[k])) {
            swap(parent(k), k);
            k = parent(k);
        }
    }

    void sink(int k) {
        while (left(k) <= size_) {
            int older = left(k);
            if (right(k) <= size_ && comp_(data_[older], data_[right(k)]))
                older = right(k);
            if (comp_(data_[older], data_[k]))
                break;
            swap(k, older);
            k = older;
        }
    }
};