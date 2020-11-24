#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;

    Node(int data = 0, Node* next = NULL) : data(data), next(next) {}
};

/*Node* middle(Node* head) {
    if(head == NULL) {
        return NULL;
    }

    Node* slowPointer = head;
    Node* fastPointer = head;

    while(fastPointer->next != NULL && fastPointer->next->next != NULL) {
        slowPointer = slowPointer->next;
        fastPointer = fastPointer->next->next;
    }

    return slowPointer;
}*/

Node* middleHelper(Node* slow, Node* fast) {
    if(fast->next == NULL || fast->next->next == NULL) {
        return slow;
    }

    return middleHelper(slow->next, fast->next->next);
}

Node* middle(Node* head) {
    if(head == NULL) {
        return NULL;
    }

    return middleHelper(head, head);
}

void deleteList(Node* head) {
    if(head != NULL) {
        deleteList(head->next);
        delete head;
    }
}

int main() {
    Node* l = new Node(1,
                  new Node(2,
                   new Node(3,
                    new Node(4,
                     new Node(5,
                      NULL)))));

    cout<< middle(l)->data<< endl;
    deleteList(l);

    return 0;
}
