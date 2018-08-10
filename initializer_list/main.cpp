#include <iostream>
#include <vector>

using namespace std;

typedef int Value;

class Values : public std::vector<Value> {
    public:
        Values() = default;
        Values(std::initializer_list<Value> values) : std::vector<Value>(values) {
        }

        Value& operator[](size_t index) {
            return std::vector<Value>::operator[](index);
        }

        const Value& operator[](size_t index) const {
            return std::vector<Value>::operator[](index);
        }
};

int main() {
    Values values({0, 1, 2, 3});
    for (int i = 0; i < 4; ++i) {
        cout << values[i] << endl;
    }
    for (auto elem : values)
        cout << elem << endl;
    return 0;
}

