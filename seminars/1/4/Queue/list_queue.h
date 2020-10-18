#ifndef QUEUE
#define QUEUE

#include <iostream>
using namespace std;

template<typename T>
class Queue {
    struct Node {
        T data;
        Node* next;

        Node(T data, Node* next): data(data), next(next) {}
    };
    Node* front;

public:
    Queue(): front(NULL) {}
    Queue(const Queue& other) = delete;
    const Queue& operator=(const Queue& other) = delete;
    ~Queue() {
        throw("implement");
    }

    void enqueue(T element) {
        throw("implement");
    }

    void dequeue() {
        throw("implement");
    }

    const T& getFront() const {
        throw("implement");
    }

    const int getSize() const {
        throw("implement");
    }

    const bool empty() const {
        throw("implement");
    }

};

#endif // QUEUE


