#include <iostream>

struct Node {
    int data;
    Node* next;

    Node(int data, Node* next = nullptr): data(data), next(next){}

};

void pushFront(Node*& head, int elem) {
    head = new Node(elem, head);
}

void printList(Node* head) {
    while(head != nullptr) {
        std::cout << head->data << ' ';
        head = head->next;
    }
}
 
void deleteList(Node* head) {
    while(head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

Node* split(Node* list, Node* position) {
    if(list == nullptr) {
        return nullptr;
    }
    if(list->next == nullptr) {
        return nullptr;
    }

    Node* iter = list;

    while(iter && iter->next != position) {
        iter = iter->next;
    }

    if(!iter) {
        return nullptr;
    }

    Node* newList = iter->next;
    iter->next = nullptr;
    return newList;
}

void append(Node* head, Node* secondHead) {
    if(!head) {
        return;
    }

    Node* iter = head;
    while(iter->next) {
        iter = iter->next;
    }

    iter->next = secondHead;
}

Node* merge(Node* firstList, Node* secondList) { 
    if (!firstList) {
        return secondList; 
    }
    if (!secondList) {
        return firstList; 
    }
  
    if (firstList->data < secondList->data) { 
        firstList->next = merge(firstList->next, secondList); 
        return firstList; 
    } 
    else { 
        secondList->next = merge(firstList, secondList->next); 
        return secondList; 
    } 
}    

Node* merge2(Node* firstList, Node* secondList) {
    if(!firstList) {
        return secondList;
    }
    if(!secondList) {
        return firstList;
    }

    Node* newList;
    if(firstList->data <= secondList->data) {
        newList = new Node(firstList->data);
        firstList = firstList->next;
    }
    else {
        newList = new Node(secondList->data);
        secondList = secondList->next;
    }

    Node* iter = newList;
    while(firstList && secondList) {
        if(firstList->data <= secondList->data) {
            iter->next = new Node(firstList->data);
            firstList = firstList->next;
        }
        else {
            iter->next = new Node(secondList->data);
            secondList = secondList->next;
        }
        iter = iter->next;
    }

    while(firstList) {
        iter->next = new Node(firstList->data);
        firstList = firstList->next;
    }
    while(secondList) {
        iter->next = new Node(secondList->data);
        secondList = secondList->next;
    }
    
    return newList;
}

Node* merge3(Node* firstList, Node* secondList) {
    if(!firstList) {
        return secondList;
    }
    if(!secondList) {
        return firstList;
    }

    Node* newList;
    if(firstList->data <= secondList->data) {
        newList = firstList;
        firstList = firstList->next;
    }
    else {
        newList = secondList;
        secondList = secondList->next;
    }

    Node* iter = newList;
    while(firstList && secondList) {
        if(firstList->data <= secondList->data) {
            iter->next = firstList;
            firstList = firstList->next;
        }
        else {
            iter->next = secondList;
            secondList = secondList->next;
        }
        iter = iter->next;
    }

    if(!firstList) {
        iter->next = secondList;
    }
    else {
        iter->next = firstList;
    }
    return newList;
}

void testSplit() {
    Node* head = new Node(5);
    pushFront(head, 4);
    pushFront(head, 3);
    pushFront(head, 2);
    pushFront(head, 1);
    Node* iter = head;
    for(size_t i = 0; i < 3; i++) {
        iter = iter->next;
    }
    Node* newList = split(head, iter);
    
    printList(head);
    std::cout << std::endl;
    printList(newList);
}

void testAppend() {
    Node* head = new Node(9);
    pushFront(head, 7);
    pushFront(head, 5);
    pushFront(head, 3);
    pushFront(head, 1);

    Node* head2 = new Node(10);
    pushFront(head2, 8);
    pushFront(head2, 6);
    pushFront(head2, 4);
    pushFront(head2, 2);

    append(head, head2);
    printList(head);
}

void testMerge() {
    Node* head = new Node(9);
    pushFront(head, 7);
    pushFront(head, 5);
    pushFront(head, 3);
    pushFront(head, 1);

    Node* head2 = new Node(10);
    pushFront(head2, 8);
    pushFront(head2, 6);
    pushFront(head2, 4);
    pushFront(head2, 2);

    printList(merge(head, head2));
}

void testMerge2() {
    Node* head = new Node(9);
    pushFront(head, 7);
    pushFront(head, 5);
    pushFront(head, 3);
    pushFront(head, 1);

    Node* head2 = new Node(10);
    pushFront(head2, 8);
    pushFront(head2, 6);
    pushFront(head2, 4);
    pushFront(head2, 2);

    printList(merge2(head, head2));
}

void testMerge3() {
    Node* head = new Node(9);
    pushFront(head, 7);
    pushFront(head, 5);
    pushFront(head, 3);
    pushFront(head, 1);

    Node* head2 = new Node(10);
    pushFront(head2, 8);
    pushFront(head2, 6);
    pushFront(head2, 4);
    pushFront(head2, 2);

    printList(merge3(head, head2));
}

int main() {
   //testSplit();
   //testAppend();
   //testMerge();
   //testMerge2();
   testMerge3();
    
    return 0;
}