#include <iostream>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

struct Node {
    int data;
    vector<Node*> children;

    Node(int data): data(data) {}
};

void deleteTree(Node* root) {
    for(vector<Node*>::iterator it = root->children.begin(); it != root->children.end(); ++it) {
        deleteTree(*it);
    }

    delete root;
}

void printTree(Node* root) {
    for(vector<Node*>::iterator it = root->children.begin(); it != root->children.end(); ++it) {
        printTree(*it);
    }

    cout<< root->data<< " ";
}

void dfsPrint(Node* root) {
    stack<Node*> dfsStack;
    Node* currentNode = NULL;

    dfsStack.push(root);
    while(!dfsStack.empty()) {
        currentNode = dfsStack.top();
        dfsStack.pop();
        cout<< currentNode->data<< " ";

        for(vector<Node*>::iterator it = currentNode->children.begin(); it != currentNode->children.end(); ++it) {
            dfsStack.push(*it);
        }
    }
}

void bfsPrint(Node* root) {
    queue<Node*> dfsStack;
    Node* currentNode = NULL;

    dfsStack.push(root);
    while(!dfsStack.empty()) {
        currentNode = dfsStack.front();
        dfsStack.pop();
        cout<< currentNode->data<< " ";

        for(vector<Node*>::iterator it = currentNode->children.begin(); it != currentNode->children.end(); ++it) {
            dfsStack.push(*it);
        }
    }
}

int main() {
    Node* root = new Node(0);
    for(int i = 0; i< 3; ++i) {
        root->children.push_back(new Node(1+i));
        for(int j = 0; j< 3; ++j) {
            root->children[i]->children.push_back(new Node((i+1)*10 + j+1));
        }
    }

    //printTree(root);
    //cout<< endl;
    //dfsPrint(root);
    //bfsPrint(root);
    deleteTree(root);

    return 0;
}
