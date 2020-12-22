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
        string data;

        Node(string data): data(data) {}
    };

    vector<Node> V;
};

void printCycle(const Graph& G) {
    vector<bool> visited;
    visited.reserve(G.V.size());

    for(int i = 0; i< G.V.size(); ++i) {
        visited[i] = false;
    }
    vector<int> indexChain;

    stack<int> graphDFSStack;
    graphDFSStack.push(0);
    while(!graphDFSStack.empty()) {
        Graph::Node currentNode = G.V[graphDFSStack.top()];
        indexChain.push_back(graphDFSStack.top());
        // function we do the dfs with
        if(visited[graphDFSStack.top()]) {
            vector<int>::iterator it = indexChain.begin();
            for(; it != indexChain.end() && *it != graphDFSStack.top(); ++it);
            for(; it != indexChain.end(); ++it) {
                cout<< G.V[*it].data<< " ";
            }
            cout<< endl;
            return;
        }
        // end of dfs function
        visited[graphDFSStack.top()] = true;
        graphDFSStack.pop();
        indexChain.pop_back();
        for(list<int>::iterator it = currentNode.E.begin(); it != currentNode.E.end(); ++it) {
            graphDFSStack.push(*it);
        }
    }

    cout<< "no cyclic"<< endl;
}

int main() {
    Graph G;

    int N = 4;
    string arr[] = {"ijk", "kji", "abc", "cba"};

    for(int i = 0; i< N; ++i) {
        G.V.push_back(Graph::Node(arr[i]));
    }

    for(int i = 0; i< N; ++i) {
        for(int j = 0; j< N; ++j) {
            if(arr[i][arr[i].size()-1] == arr[j][0]) {
                G.V[i].E.push_back(j);
            }
        }
    }

    printCycle(G);

    return 0;
}

