#include <iostream>
#include "minHeap.h"
using namespace std;

void print(vector<int> v) {
    for(vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
        cout<< *it<< " ";
    }
    cout<< endl;
}

struct MachineNode {
    vector<int>* machineVector;
    int currentIndex;

    MachineNode(vector<int>* machineVector, int currentIndex = 0):
        machineVector(machineVector), currentIndex(currentIndex) {}

    int getCurrValue() const {
        return machineVector->at(currentIndex);
    }

    bool setNext() {
        return (++currentIndex < machineVector->size()) ? true : false;
    }

    bool operator<(const MachineNode& other) const {
        return getCurrValue() < other.getCurrValue();
    }
};

vector<int> mergeSorted(vector< vector<int>* >& machinesData) {
    MinHeap<MachineNode> sortHeap;

    for(vector<vector<int>*>::iterator it = machinesData.begin(); it != machinesData.end(); ++it) {
        sortHeap.push(MachineNode(*it));
    }

    vector<int> result;
    while(!sortHeap.empty()) {
        MachineNode top = sortHeap.top();
        result.push_back(top.getCurrValue());
        sortHeap.pop();
        if(top.setNext()) {
            sortHeap.push(top);
        }
    }

    return result;
}

int main() {
    vector<int> v1, v2, v3;
    vector< vector<int>* > machinesInput;

    for(int i = 0; i< 25; ++i) {
        v1.push_back(i*2);
    }
    machinesInput.push_back(&v1);

    for(int i = 0; i< 10; ++i) {
        v2.push_back(i*i);
    }
    machinesInput.push_back(&v2);

    for(int i = 5; i< 12; ++i) {
        v3.push_back(i*i - 5*i + 4);
    }
    machinesInput.push_back(&v3);

    cout<< "input: "<< endl;
    print(v1);
    print(v2);
    print(v3);
    cout<< endl;

    cout<< "output: "<< endl;
    print(mergeSorted(machinesInput));

    return 0;
}
