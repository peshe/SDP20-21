#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <string>
using namespace std;

struct Graph {
    struct Node {
        list<int> E;
        int data;

        Node(int data): data(data) {}
    };

    vector<Node> V;
};

void printShortestPath(const Graph& G, int startIndex, int endIndex) {
    vector<int> parent;
    parent.reserve(G.V.size());
    for(int i = 0; i< G.V.size(); ++i) {
        parent[i] = -1;
    }
    parent[startIndex] = -2;

    queue<int> graphBFSQueue;
    graphBFSQueue.push(startIndex);
    while(!graphBFSQueue.empty()) {
        int currentNodeIndex = graphBFSQueue.front();

        // function we do the bfs with
        if(currentNodeIndex == endIndex) {
            stack<int> path;
            for(int backIndex = currentNodeIndex; backIndex != -2; backIndex = parent[backIndex]) {
                path.push(G.V[backIndex].data);
                //cout<< G.V[backIndex].data<< " ";
            }
            while(!path.empty()) {
                cout<< path.top()<< " ";
                path.pop();
            }
            cout<< endl;
            return;
        }
        // end of bfs function

        graphBFSQueue.pop();
        Graph::Node currentNode = G.V[currentNodeIndex];
        for(list<int>::iterator it = currentNode.E.begin(); it != currentNode.E.end(); ++it) {
            if(parent[*it] == -1) {
                parent[*it] = currentNodeIndex;
                graphBFSQueue.push(*it);
            }
        }
    }

    cout<< "no such path";
}

int main() {
    Graph G;
    for(int i = 0; i< 10; ++i) {
        G.V.push_back(Graph::Node(i));
    }

    G.V[5].E.push_back(1);
    G.V[5].E.push_back(2);
    G.V[5].E.push_back(3);
    G.V[1].E.push_back(9);
    G.V[2].E.push_back(6);
    G.V[6].E.push_back(7);
    G.V[9].E.push_back(8);
    G.V[9].E.push_back(0);

    G.V[8].E.push_back(5);

    printShortestPath(G, 5, 0);

    return 0;
}

