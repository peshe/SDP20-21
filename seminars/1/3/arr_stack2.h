#ifndef STACK
#define STACK

#include <iostream>
#include "vector.h"
using namespace std;

template<typename T>
class Stack {
    Vector<T> data;

public:

    int getSize() const {
        return data.getSize();
    }

    void push_back(T element) {
        data.push_back(element);
    }

    void pop_back() {
        data.pop_back();
    }

    const T& top() {
        if(getSize() < 1) {
            throw "stack is empty";
        }

        return data[getSize()-1];
    }

    bool empty() const {
        return getSize() == 0;
    }
};

#endif // STACK
