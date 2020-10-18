#include <iostream>
#include "list_queue_complete.h"
using namespace std;

int main() {
    int sum = 0;
    Queue<int> q;
    for(int i = 1; i< 15+1; ++i) {
        q.enqueue(i);
    }

    while(!q.empty()) {
        sum += q.getFront();
        q.dequeue();
    }

    cout<< sum<< endl;

    return 0;
}
