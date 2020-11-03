#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;

    Node(int data = 0, Node* next = NULL) : data(data), next(next) {}
};

Node* reverseListHelper(Node* prev, Node* curr, Node* next) {
    curr->next = prev;
    return (next == NULL) ? curr : reverseListHelper(curr, next, next->next);
}

Node* reverseList(Node* head) {
    if(head == NULL) {
        return NULL;
    }

    return reverseListHelper(NULL, head, head->next);
}

void deleteList(Node* head) {
    if(head != NULL) {
        deleteList(head->next);
        delete head;
    }
}

void printList(Node* head) {
    if(head == NULL) {
        return;
    }

    cout<< head->data<< "->";
    printList(head->next);
}

int main() {
    Node* l = new Node(9,
              new Node(9,
              new Node(9,
              new Node(8))));

    l = reverseList(l);
    printList(l);
    deleteList(l);

    return 0;
}

