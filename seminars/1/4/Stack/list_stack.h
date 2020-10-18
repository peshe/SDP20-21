#ifndef STACK
#define STACK

#include <iostream>
using namespace std;

template<typename T>
class Stack {
    struct Node {
        T data;
        Node* prev;

        Node(T data, Node* prev): data(data), prev(prev) {}
    };
    Node* top;

public:
    Stack(): top(NULL) {}
    Stack(const Stack& other) = delete;
    const Stack& operator=(const Stack& other) = delete;
    ~Stack() {
        throw("implement");
    }

    void push_back(T element) {
        throw("implement");
    }

    void pop_back() {
        throw("implement");
    }

    const T& getTop() const {
        throw("implement");
    }

    const int getSize() const {
        throw("implement");
    }

    const bool empty() const {
        throw("implement");
    }

};

#endif // STACK


