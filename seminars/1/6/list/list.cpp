#include <iostream>
#include "list.h"
#include "completed/dllist.h"
using namespace std;

int main() {
    DoublyLinkedList<int> l;

    for(int i = 0; i< 10; ++i) {
        l.push_back(i);
    }
    l.remove(5);
    l.insert(16, 3);

    /*for(int i = 0; i< 10; ++i) {
        cout<< l.getAt(i)<< endl;
    }

    while(!l.empty()) {
        l.pop_back();
    }*/

    /*for(DoublyLinkedList<int>::Iterator it = l.begin(); it != l.end(); ++it)  {
        cout<< *it<< endl;
    }*/

    return 0;
}
