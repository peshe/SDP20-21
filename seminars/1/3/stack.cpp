#include <iostream>
#include "stack3.h"
using namespace std;

int main() {
    int sum = 0;
    Stack<int> s;
    for(int i = 1; i< 15+1; ++i) {
        s.push_back(i);
    }

    while(!s.empty()) {
        sum += s.getTop();
        s.pop_back();
    }

    cout<< sum<< endl;

    return 0;
}
