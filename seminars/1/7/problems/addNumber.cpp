#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;

    Node(int data = 0, Node* next = NULL) : data(data), next(next) {}
};

int addOneToListHelper(Node* head) {
    if(head == NULL) {
        return 1;
    }

    head->data += addOneToListHelper(head->next);
    int remainder = head->data / 10;
    head->data %= 10;

    return remainder;
}

Node* addOneToList(Node* head) {
    if(head == NULL) {
        return NULL;
    }

    return (addOneToListHelper(head) > 0) ? new Node(1, head) : head;
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

    l = addOneToList(l);
    printList(l);
    l = addOneToList(l);
    cout<< endl;
    printList(l);
    deleteList(l);

    return 0;
}
