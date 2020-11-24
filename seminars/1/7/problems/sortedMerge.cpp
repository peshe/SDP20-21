#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;

    Node(int data = 0, Node* next = NULL) : data(data), next(next) {}
};

Node* mergeLists(Node* l1, Node* l2) {
    if(l1 == NULL) {
        return l2;
    }

    if(l2 == NULL) {
        return l1;
    }

    if(l1->data < l2->data) {
        l1->next = mergeLists(l1->next, l2);
        return l1;
    } else {
        l2->next = mergeLists(l1, l2->next);
        return l2;
    }
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
    Node* l1 = new Node(1,
              new Node(2,
              new Node(4,
              new Node(8))));

    Node* l2 = new Node(3,
              new Node(9,
              new Node(27,
              new Node(81))));

    Node* l = mergeLists(l1, l2);
    printList(l);
    deleteList(l);

    return 0;
}


