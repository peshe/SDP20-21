#ifndef QUEUE
#define QUEUE

#include <iostream>
#include "vector.h"
using namespace std;

template<typename T>
class Queue {
    Vector<T> data;

public:

    int getSize() const {
        return data.getSize();
    }

    void enqueue(T element) {
        data.push_back(element);
    }

    void dequeue() {
        data.pop_front();
    }

    const T& getFront() {
        if(getSize() < 1) {
            throw "queue is empty";
        }

        return data[0];
    }

    bool empty() const {
        return getSize() == 0;
    }
};

#endif // QUEUE
