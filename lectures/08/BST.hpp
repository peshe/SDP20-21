/******************************************************************
*  Sample code to the course "Data Structures And Algorithms", FMI
*
* An educational class, representing binary search tree.
*
* (cc) Petar Armyanov, FMI, 2020
*******************************************************************/

#pragma once

#ifndef __BST_HEADER_INCLUDED_
#define __BST_HEADER_INCLUDED_

#include <iostream>
#include <algorithm>

namespace fmi {
namespace sdp {

template <class DataType>
class BST
{
public:
    BST() : root(nullptr), size(0) {};

    ~BST() { clear(root); }

    BST(const BST& tree)
        : root(copy(tree.root))
        , size(tree.size) {};

    BST(BST&& tree)
        : BST()
    {
        std::swap(root, tree.root);
        std::swap(size, tree.size);
    };

    BST& operator=(const BST& tree)
    {
        if (&tree != this) {
            clear(root);
            root = copy(tree.root);
            size = tree.size;
        }
        return *this;
    }

    BST& operator=(BST&& rhs)
    {
        if (this != &rhs) {
            std::swap(root, rhs.root);
            std::swap(size, rhs.size);
        }
        return *this;
    }

    bool find(const DataType& key) const { return find(root, key); }
    void insert(const DataType& key) { insert(root, key); ++size; }
    void remove(const DataType& key) { remove(root, key); }

    size_t getSize() const { return size; }

    size_t getHeight() const { return (size_t)height(root); }
    bool isBalanced() const { return balanced(root); }
    bool isPerfectlyBalanced() const { return perfectBalanced(root); }

    void printInorder() const { print(root); std::cout << "\n"; }

private:
    struct node
    {
        DataType key;
        node* left, * right;

        node(const DataType& key, node* left = nullptr, node* right = nullptr)
            : key(key)
            , left(left)
            , right(right)
        {}
    } *root;

    size_t size;

private:

    void clear(node* root)
    {
        if (root) {
            clear(root->left);
            clear(root->right);
            delete root;
        }
    }


    node* copy(node* root)
    {
        return root ?
            new node(root->key, copy(root->left), copy(root->right)) :
            root;
    }


    bool find(const node* root, const DataType& key) const
    {
        if (!root) return false;
        if (root->key == key) return true;
        return key < root->key ? find(root->left, key) : find(root->right, key);
    }


    void insert(node*& root, const DataType& key)
    {
        if (!root) {
            root = new node(key);
        }
        else {
            insert(key < root->key ? root->left : root->right, key);
        }
    }


    void remove(node*& root, const DataType& key)
    {
        if (!root) return;

        if (root->key == key) {
            node* toDel = root;
            if (!root->left) {
                root = root->right;
            }
            else if (!root->right) {
                root = root->left;
            }
            else {
                node* mR = extractMin(root->right);
                mR->left = root->left;
                mR->right = root->right;
                root = mR;
            }
            --size;
            delete toDel;
        }
        else {
            remove(key < root->key ? root->left : root->right, key);
        }
    }

    node* extractMin(node*& root)
    {
        if (root->left) {
            return extractMin(root->left);
        }

        node* n = root;
        root = root->right;
        return n;
    }

    int height(const node* root) const
    {
        if (!root) return 0;
        return 1 + std::max(height(root->left), height(root->right));
    }

    bool balanced(const node* root) const
    {
        if (!root) return true;
        return abs(height(root->left) - height(root->right)) < 2 &&
               balanced(root->left) && balanced(root->right);
    }


    bool perfectBalanced(const node* root) const
    {
        if (!root) return true;
        return labs(weight(root->left) - weight(root->right)) < 2 &&
               perfectBalanced(root->left) && perfectBalanced(root->right);
    }

    long weight(const node* root) const
    {
        if (!root) return 0;
        return 1 + weight(root->left) + weight(root->right);
    }

    void print(const node* root) const
    {
        if (root) {
            print(root->left);
            std::cout << root->key << " ";
            print(root->right);
        }
    }
};

} //namespace sdp
} //namespace fmi


#endif //__BST_HEADER_INCLUDED_
