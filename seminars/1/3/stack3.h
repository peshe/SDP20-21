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
        Node* oldTop = top;
        while(top != NULL) {
            oldTop = top;
            top = top->prev;
            delete oldTop;
        }
    }

    void push_back(T element) {
        Node* newTop = new Node(element, top);
        top = newTop;
    }

    void pop_back() {
        if(empty()) {
            return;
        }
        Node* newTop = top->prev;
        delete top;
        top = newTop;
    }

    const T& getTop() const {
        return top->data;
    }

    const bool empty() const {
        return top == NULL;
    }

};

#endif // STACK

