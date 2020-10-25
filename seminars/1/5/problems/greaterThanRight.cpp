#include <iostream>
#include "../libs/vector.h"
#include "../libs/list_stack.h"
using namespace std;

Vector<int> greaterThanRight(int* arr, int arrSize) {
    Stack<int> s;
    for(int i = 0; i< arrSize; ++i) {
        s.push_back(arr[i]);
    }

    int cMax = s.getTop();
    Vector<int> result;

    while(!s.empty()) {
        if(s.getTop() >= cMax) {
            result.push_back(s.getTop());
        }
        cMax = (cMax < s.getTop()) ? s.getTop() : cMax;
        s.pop_back();
    }

    return result;
}

int main () {
    // in 10 4 6 3 5
    // out 10 6 5

    int arr[] = {10, 4, 6, 3, 5};
    Vector<int> res = greaterThanRight(arr, 5);

    res.print();

    return 0;
}
