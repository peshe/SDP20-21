#include <iostream>
#include <stack>
using namespace std;

template <class T>
class BST {
    struct Node {
        T data;
        Node* left;
        Node* right;

        Node(T data, Node* left = NULL, Node* right = NULL): data(data), left(left), right(right) {}
    };
    Node* root;

// -------------------------------- BASIC ------------------------------

    void clear(Node*& root) {
        if(root == NULL) {
            return;
        }

        clear(root->left);
        clear(root->right);

        delete root;
        root = NULL;
    }

    void copy(Node* root, const Node* otherRoot) {
        root = new Node(otherRoot->data);
        root->left = copy(root->left, otherRoot->left);
        root->right = copy(root->right, otherRoot->right);

        return root;
    }

    void copy(const Node* otherRoot) {
        clear(root);
        root = copy(root, otherRoot);
    }

// ------------------------------ UTILITY -------------------------------

    void insert(Node* root, T data) {
        if(root->data > data) {
            if(root->left == NULL) {
                root->left = new Node(data);
                return;
            }
            return insert(root->left, data);
        } else {
            if(root->right == NULL) {
                root->right = new Node(data);
                return;
            }
            return insert(root->right, data);
        }
    }

    bool present(Node* root, T& data) {
        return (root != NULL) && (root->data == data || present(((root->data < data) ? root->left : root->right), data));
    }

    void remove(Node*& root, T data) {
        if(root == NULL) {
            return;
        }

        if(root->data == data) {
            if(root->left == NULL && root->right == NULL) {
                delete root;
                root = NULL;
                return;
            }

            if(root->left == NULL || root->right == NULL) {
                Node* temp = ((root->left == NULL) ? root->right : root->left);
                delete root;
                root = temp;
                return;
            }

            if(root->right->left == NULL) {
                root->data = root->right->data;
                Node* temp = root->right->right;
                delete root->right;
                root->right = temp;
                return;
            }

            Node* minRightParent = root->right;
            for(; minRightParent->left->left != NULL; minRightParent = minRightParent->left) {}
            root->data = minRightParent->left->data;
            Node* temp = minRightParent->left->right;
            delete minRightParent->left;
            minRightParent->left = temp;

            return;
        }

        remove((root->data > data) ? root->left : root->right, data);
    }

    void print(Node* root, ostream& out = cout) const {
        if(root == NULL) {
            return;
        }

        print(root->left, out);
        out<< root->data<< " ";
        print(root->right, out);
    }

public:
// ------------------------------ BIG FOUR --------------------------------

    BST(): root(NULL) {}
    BST(const BST& other) {
        copy(other->root);
    }
    BST& operator=(const BST& other) {
        if(this != &other) {
            copy(other->root);
        }

        return *this;
    }
    ~BST() {
        clear(root);
    }

// ----------------------------- ITERATOR ----------------------------------

    class Iterator {
        stack<Node*> iteratorStack;

    public:
        Iterator(Node* root) {
            if(root == NULL) {
                return;
            }

            for(; root != NULL; root = root->left) {
                iteratorStack.push(root);
            }
        }

        Iterator& operator++() {
            if(iteratorStack.empty()) {
                throw("can't get next");
            }

            Node* top = iteratorStack.top();
            iteratorStack.pop();
            for(Node* rightLeft = top->right; rightLeft != NULL; rightLeft = rightLeft->left) {
                iteratorStack.push(rightLeft);
            }
        }

        T& operator*() {
            return iteratorStack.top()->data;
        }

        bool operator==(const Iterator& other) {
            return iteratorStack == other.iteratorStack;
        }

        bool operator!=(const Iterator& other) {
            return !(*this == other);
        }
    };

// ----------------------------- CONTAINER ----------------------------------

    Iterator begin() {
        return Iterator(root);
    }

    Iterator end() {
        return Iterator(NULL);
    }

    void insert(T data) {
        if(root == NULL) {
            root = new Node(data);
            return;
        }

        insert(root, data);
    }

    bool present(T& data) {
        return present(root, data);
    }

    void remove(T data) {
        remove(root, data);
    }

    void print(ostream& out = cout) const {
        print(root, out);
    }
};

template <class T>
ostream& operator<<(ostream& out, const BST<T>& bst) {
    bst.print(out);
    return out;
}

int main() {
    BST<int> bst;

    int arr[] = {5, 14, -6, 3, 18, 27, -34, 0, 2, 4, 12};
    for(int i = 0; i< 11; ++i) {
        bst.insert(arr[i]);
    }
    bst.remove(5);

    cout<< "iterator print: ";
    for(BST<int>::Iterator it = bst.begin(); it != bst.end(); ++it) {
        cout<< *it<< " ";
    }
    cout<< endl;

    cout<< "in order traversal print: ";
    cout<< bst<< endl;

    return 0;
}
