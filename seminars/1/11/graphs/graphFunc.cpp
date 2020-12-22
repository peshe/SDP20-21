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

void printDFS(const Graph& G, int startIndex) {
    vector<bool> visited;
    visited.reserve(G.V.size());
    for(int i = 0; i< G.V.size(); ++i) {
        visited[i] = false;
    }

    stack<int> graphDFSStack;
    graphDFSStack.push(startIndex);
    while(!graphDFSStack.empty()) {
        Graph::Node currentNode = G.V[graphDFSStack.top()];
        visited[graphDFSStack.top()] = true;
        // function we do the dfs with
        cout<< currentNode.data<< " ";
        // end of dfs function
        graphDFSStack.pop();
        for(list<int>::iterator it = currentNode.E.begin(); it != currentNode.E.end(); ++it) {
            if(!visited[*it]) {
                graphDFSStack.push(*it);
            }
        }
    }
}

void printBFS(const Graph& G, int startIndex) {
    vector<bool> visited;
    visited.reserve(G.V.size());
    for(int i = 0; i< G.V.size(); ++i) {
        visited[i] = false;
    }

    queue<int> graphDFSStack;
    graphDFSStack.push(startIndex);
    while(!graphDFSStack.empty()) {
        Graph::Node currentNode = G.V[graphDFSStack.front()];
        visited[graphDFSStack.front()] = true;
        // function we do the dfs with
        cout<< currentNode.data<< " ";
        // end of dfs function
        graphDFSStack.pop();
        for(list<int>::iterator it = currentNode.E.begin(); it != currentNode.E.end(); ++it) {
            if(!visited[*it]) {
                graphDFSStack.push(*it);
            }
        }
    }
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

    printDFS(G, 5);
    cout<< endl;
    printBFS(G, 5);

    return 0;
}
