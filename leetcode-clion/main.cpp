#include <iostream>
#include <vector>
#include <sstream>
#include <cstdlib>

#include "utils.h"

#include "dynamic_programming/stock/121.best-time-to-buy-and-sell-stock.cpp"

using namespace std;

int main() {
    Solution sol;
    vector<vector<int>> prices = {
            {7,1,5,3,6,4},
            {7,6,4,3,1}
    };
    for (int i = 0; i < prices.size(); ++i) {
        cout << sol.maxProfit(prices[i]);
        cout << endl;
    }
    return 0;
}

