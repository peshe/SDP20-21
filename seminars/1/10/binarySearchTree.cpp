
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

bool searchInTree(Node* root, int val) {
    return root != NULL && (root->data == val || searchInTree(root->left) || searchInTree(root->right));
}


bool searchInBST(Node* root, int val) {
    return root == NULL && (root->data == val || searchInBST(((root->data < val) ? root->left, root->right), val));
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
    Node* tree2 = new Node(5,
                           new Node(3,
                                    new Node(2,
                                             new Node(1, NULL, NULL),
                                             new Node(3, NULL, NULL)),
                                    NULL),
                           new Node(8,
                                    new Node(6,
                                             new Node(5, NULL, NULL),
                                             new Node(7, NULL, NULL)),
                                    new Node(10, NULL, NULL)));

    printTree(tree2);

    deleteTree(tree);
    deleteTree(tree2);

    return 0;
}
