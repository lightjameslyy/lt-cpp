#include <iostream>
#include <vector>
#include <sstream>
#include <cstdlib>

#include "utils.h"

#include "design/146.lru-cache.cpp"

using namespace std;

int main() {
    LRUCache obj(2);
    obj.put(1,1);
    obj.put(2,2);
    cout << obj.get(1) << endl;
    obj.put(3,3);
    cout << obj.get(2) << endl;
    obj.put(4,4);
    cout << obj.get(1) << endl;
    cout << obj.get(3) << endl;
    cout << obj.get(4) << endl;
    return 0;
}

