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
    Node* back;
    int size;

public:
    Queue(): front(NULL), back(NULL), size(0) {}
    Queue(const Queue& other) = delete;
    const Queue& operator=(const Queue& other) = delete;
    ~Queue() {
        Node* oldFront = front;
        while(front != NULL) {
            oldFront = front;
            front = front->next;
            delete oldFront;
        }
    }

    void enqueue(T element) {
        if(back != NULL) {
            back->next = new Node(element, NULL);
            back = back->next;
        } else  {
            back = new Node(element, NULL);
            front = back;
        }
        ++size;
    }

    void dequeue() {
        if(empty()) {
            return;
        }
        Node* newFront = front->next;
        delete front;
        front = newFront;
        if(front == NULL) {
            back = NULL;
        }
        --size;
    }

    const T& getFront() const {
        return front->data;
    }

    const int getSize() const {
        return size;
    }

    const bool empty() const {
        return front == NULL;
    }

};

#endif // QUEUE

