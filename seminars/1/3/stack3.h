#ifndef STACK
#define STACK

#include <iostream>
using namespace std;

template<typename T>
class Stack {
    struct Node {
        T data;
        Node* next;
    };
    Node* head;
    Node* tail;

public:
    Stack(): head(NULL) {}
    Stack(const Stack& other) = delete;
    const Stack& operator=(const Stack& other) = delete;
    ~Stack() {
        Node* oldHead = head;
        while(head != NULL) {
            oldHead = head;
            head = head->next;
            delete oldHead;
        }
    }

};

#endif // STACK

