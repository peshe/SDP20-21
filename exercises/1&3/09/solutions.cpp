#include <iostream>
#include <climits>

struct BTNode {
    int value;
    BTNode* left;
    BTNode* right;

    BTNode(int value, BTNode* left = nullptr, BTNode* right = nullptr)
        :value(value), left(left), right(right){}
    
};

BTNode*& getMax(BTNode*& root) {
    if(!root->right) {
        return root;
    }
    return getMax(root->right);
}

BTNode*& findNode(BTNode*& root, int val) {
    if(!root || root->value == val) { 
        return root;
    } 

    if(val > root->value) {
        return findNode(root->right, val);
    }
    else {
        return findNode(root->left, val);
    }
}

void insertNode(BTNode*& root, int val) {
    BTNode*& node = findNode(root, val);

    if(node) {
        return;
    }

    node = new BTNode(val);
}

void delNode(BTNode* root, int val) {
    BTNode*& node = findNode(root, val);

    if(!node) {
        return;
    }

    if(!node->left && !node->right) {
        delete node;
        node = nullptr;
    }
    else if(!node->left) {
        BTNode* right = node->right;
        delete node;
        node = right;
    }
    else if(!node->right) {
        BTNode* left = node->left;
        delete node;
        node = left;
    }
    else {
        BTNode*& max = getMax(node->left);
        node->value = max->value;
        delete max;
        max = nullptr;
    }
}

void mirror(BTNode* root) {
    if(!root) {
        return;
    }
    mirror(root->left);
    mirror(root->right);

    BTNode* temp = root->left;
    root->left = root->right;
    root->right = temp;
}

void doubleTree(BTNode* root) {
    if(!root) {
        return;
    }

    doubleTree(root->left);
    doubleTree(root->right);

    BTNode* temp = root->left;
    root->left = new BTNode(root->value);
    root->left->left = temp;
}

void print(BTNode* root) {
    if(!root) {
        return;
    }
    print(root->left);
    std::cout << root->value;
    print(root->right);
}

bool isBSTUtil(BTNode* root, int min, int max) {
    if(!root) {
        return true;
    }

    if(root->value < min || root->value > max) {
        return false;
    }

    return isBSTUtil(root->left, min, root->value) && 
           isBSTUtil(root->right, root->value+1, max);
}

bool isBST(BTNode* root) {
    return isBSTUtil(root, INT_MIN, INT_MAX);
}

int main() {

    return 0;
}