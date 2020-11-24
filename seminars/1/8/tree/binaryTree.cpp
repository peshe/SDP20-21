#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int data, Node* left, Node* right): data(data), left(left), right(right) {}
};

void deleteTree(Node* root) {
    if(root == NULL) {
        return;
    }

    deleteTree(root->left);
    deleteTree(root->right);

    delete root;
}

void printTree(Node* root) {
    if(root == NULL) {
        return;
    }

    printTree(root->left);
    cout<< root->data<< " ";
    printTree(root->right);
}

int main() {
    Node* tree = new Node(1, NULL, NULL);
    Node* tree2 = new Node(1,
                           NULL,
                           new Node(3,
                                    new Node(1,
                                             new Node(7, NULL, NULL),
                                             new Node(8, NULL, NULL)),
                                    NULL));

    printTree(tree2);

    deleteTree(tree);
    deleteTree(tree2);

    return 0;
}
