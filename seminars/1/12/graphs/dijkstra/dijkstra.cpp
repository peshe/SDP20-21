#include <iostream>
#include <list>
#include <vector>
#include <limits>
#include "MinHeap.h"
using namespace std;

struct Graph {
    struct Edge {
        int to;
        float weight;

        Edge(int to, int weight): to(to), weight(weight) {}
    };

    struct Node {
        list<Edge> E;
        int data;

        Node(int data): data(data) {}
    };

    vector<Node> V;
};

void printShortestPath(const Graph& G, int startIndex, int endIndex) {
    vector<int> parent;
    vector<float> distance;
    parent.reserve(G.V.size());
    distance.reserve(G.V.size());
    for(int i = 0; i< G.V.size(); ++i) {
        parent[i] = -1;
        distance[i] = numeric_limits<float>::max();
    }
    parent[startIndex] = -2;
    distance[startIndex] = 0;

    MinHeap<pair<float, int>> graphDijkstraPQ;
    graphDijkstraPQ.push(pair<float, int>(distance[startIndex], startIndex));
    while(!graphDijkstraPQ.empty()) {
        float currentNodeDistance = graphDijkstraPQ.top().first;
        int currentNodeIndex = graphDijkstraPQ.top().second;

        cout<< "entering "<< currentNodeIndex<< " with "<< currentNodeDistance<< endl;

        // function we do the bfs with
        if(currentNodeIndex == endIndex) {
            for(int backIndex = currentNodeIndex; backIndex != -2; backIndex = parent[backIndex]) {
                cout<< G.V[backIndex].data<< " ";
            }
            cout<< endl;
            return;
        }
        // end of bfs function

        graphDijkstraPQ.pop();
        Graph::Node currentNode = G.V[currentNodeIndex];
        for(list<Graph::Edge>::iterator it = currentNode.E.begin(); it != currentNode.E.end(); ++it) {
            float newDistance = currentNodeDistance + it->weight;
            cout<< currentNodeIndex<< "-"<< newDistance<< "->"<< it->to<< endl;
            if(distance[it->to] > newDistance) {
                parent[it->to] = currentNodeIndex;
                distance[it->to] = newDistance;
                graphDijkstraPQ.push(pair<float, int>(newDistance, it->to));
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

    G.V[5].E.push_back(Graph::Edge(1, 3));
    G.V[5].E.push_back(Graph::Edge(2, 1));
    G.V[5].E.push_back(Graph::Edge(3, 15));
    G.V[1].E.push_back(Graph::Edge(9, 2));
    G.V[2].E.push_back(Graph::Edge(6, 7));
    G.V[6].E.push_back(Graph::Edge(7, 34));
    G.V[9].E.push_back(Graph::Edge(8, 13));
    G.V[9].E.push_back(Graph::Edge(0, 6));

    G.V[8].E.push_back(Graph::Edge(5, 1));
    G.V[6].E.push_back(Graph::Edge(1, 3));
    G.V[5].E.push_back(Graph::Edge(0, 45));
    G.V[0].E.push_back(Graph::Edge(1, 2));

    printShortestPath(G, 5, 0);

    return 0;
}
