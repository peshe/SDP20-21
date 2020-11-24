#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;

    Node(int data = 0, Node* next = NULL) : data(data), next(next) {}
};

Node* removeSortedDuplicates(Node* head, int lastValue) {
    if(head == NULL) {
        return NULL;
    }

    if(head->data == lastValue) {
        Node* nextNode = head->next;
        delete head;
        return removeSortedDuplicates(nextNode, lastValue);
    }

    head->next = removeSortedDuplicates(head->next, head->data);
    return head;
}

Node* removeSortedDuplicates(Node* head) {
    if(head == NULL) {
        return NULL;
    }

    head->next = removeSortedDuplicates(head->next, head->data);

    return head;
}

Node* removeSortedDuplicates1(Node* head) {
    if(head == NULL) {
        return NULL;
    }

    for(Node* current = head; current->next != NULL; current = current->next) {
        while(current->data == current->next->data) {
            Node* oldNode = current->next;
            current->next = oldNode->next;
            delete oldNode;
        }
    }

    return head;
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
    Node* l = new Node(1,
                  new Node(2,
                  new Node(2,
                  new Node(2,
                   new Node(3,
                    new Node(4,
                     new Node(5,
                      NULL)))))));

    removeSortedDuplicates1(l);
    printList(l);
    deleteList(l);

    return 0;
}
