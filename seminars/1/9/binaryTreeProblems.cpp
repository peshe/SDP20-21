#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int data, Node* left, Node* right): data(data), left(left), right(right) {}
};

int size(Node* root) {
    if(root == NULL) {
        return 0;
    }

    return 1 + size(root->left) + size(root->right);
}

int maxDepth(Node* root) {
    if(root == NULL) {
        return 0;
    }

    return 1 + max(maxDepth(root->left),
                   maxDepth(root->right));
}


int minValue(Node* root) {
    if(root == NULL) {
        throw "no min value";
    }

    if(root->left == NULL) {
        if(root->right == NULL) {
            return root->data;
        }
        return min(root->data, minValue(root->right));
    }

    if(root->right == NULL) {
        return min(root->data, minValue(root->left));
    }

    return min(root->data, min(minValue(root->left), minValue(root->right)));
}

void deleteTree(Node* root) {
    if(root == NULL) {
        return;
    }

    deleteTree(root->left);
    deleteTree(root->right);

    delete root;
}

bool equal(Node* root1, Node* root2) {
    if(root1 == NULL && root2 == NULL) {
        return true;
    }

    if(root1 == NULL || root2 == NULL) {
        return false;
    }

    return root1->data == root2->data &&
            equal(root1->left, root2->left) &&
            equal(root1->right, root2->right);
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

    cout<< minValue(tree2);

    deleteTree(tree);
    deleteTree(tree2);

    return 0;
}
