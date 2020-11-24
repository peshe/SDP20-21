#ifndef DLLIST
#define DLLIST

#include <iostream>
using namespace std;

template<typename T>
class CircularLinkedList {
    struct Node {
        T data;
        Node* prev;
        Node* next;

        Node(T data, Node* prev, Node* next): data(data), prev(prev), next(next) {}
    };
    Node* head;

public:
    CircularLinkedList(): head(NULL) {}
    CircularLinkedList(const CircularLinkedList& other) = delete;
    const CircularLinkedList& operator=(const CircularLinkedList& other) = delete;
    ~CircularLinkedList() {
        while(!empty()) {
            pop_front();
        }
    }

    void push_back(T element) {
        if(head == NULL) {
            head = new Node(element, head, head);
            head->next = head->prev = head;
            return;
        }

        Node* newNode = new Node(element, head->prev, head);
        head->prev->next = newNode;
        head->prev = newNode;
    }

    void push_front(T element) {
        if(head == NULL) {
            head = new Node(element, head, head);
            head->next = head->prev = head;
            return;
        }

        Node* newNode = new Node(element, head, head->next);
        head->next->prev = newNode;
        head->next = newNode;
    }

    void pop_back() {
        if(empty()) {
            throw "no elements";
        }

        if(head->next == head) {
            delete head;
            head = NULL;
            return;
        }

        head->prev = head->prev->prev;
        delete head->prev->next;
        head->prev->next = head;
    }

    void pop_front() {
        if(empty()) {
            throw "no elements";
        }

        if(head->next == head) {
            delete head;
            head = NULL;
            return;
        }

        head->next = head->next->next;
        delete head->next->prev;
        head->next->prev = head;
    }

    void insert(T element, int index) {
        throw "not implemented";
    }

    void remove(int index) {
        throw "not implemented";
    }

    const T& getFront() const {
        throw head->next->data;
    }

    const T& getBack() const {
        throw head->prev->data;
    }

    const T& getAt(int index) {
        if(empty()) {
            throw "no elements";
        }

        Node* seekedNode = head;
        for(; index > 0; --index) {
            seekedNode = seekedNode->next;
        }
        return seekedNode->data;
    }

    const bool empty() const {
        return head == NULL;
    }

};

#endif // DLLIST
