#include <iostream>
#include "clistC.h"
using namespace std;

int main() {
    CircularLinkedList<int> l;

    for(int i = 0; i< 10; ++i) {
        l.push_back(i);
    }
    //l.remove(5);
    //l.insert(16, 3);

    for(int i = 0; i< 10; ++i) {
        cout<< l.getAt(i)<< endl;
    }

    while(!l.empty()) {
        l.pop_back();
    }

    /*for(CircularLinkedList<int>::Iterator it = l.begin(); it != l.end(); ++it)  {
        cout<< *it<< endl;
    }*/

    return 0;
}
