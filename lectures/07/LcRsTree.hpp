/******************************************************************
*  Sample code to the course "Data Structures And Algorithms", FMI
*
* An educational class, representing generic tree data structure.
* The connection scheme is Left-child / Right sibling
*
* (cc) Petar Armyanov, FMI, 2020
*******************************************************************/

#pragma once

#ifndef __TREE_HEADER_INCLUDED_
#define __TREE_HEADER_INCLUDED_

#include <iostream>
#include <queue>

namespace fmi {
namespace sdp {

template <class DataType>
class Tree
{
public:
    Tree() : root(nullptr), size(0) {};

    ~Tree() { clear(root); }

    Tree(const Tree& tree)
        : root(copy(tree.root))
        , size(tree.size) {};

    Tree(Tree&& tree)
        : Tree()
    {
        std::swap(root, tree.root);
        std::swap(size, tree.size);
    };

    Tree& operator=(const Tree& tree)
    {
        if (&tree != this) {
            clear(root);
            root = copy(tree.root);
            size = tree.size;
        }
        return *this;
    }

    Tree& operator=(Tree&& rhs)
    {
        if (this != &rhs) {
            std::swap(root, rhs.root);
            std::swap(size, rhs.size);
        }
        return *this;
    }

    bool find(const DataType& key) const { return find(root, key); }
    void insert(const DataType& key, int path[]) { if (insert(root, key, path)) ++size; }
    void remove(const DataType& key) { remove(root, key); }

    size_t getSize() const { return size; }
    size_t getHeight() const { return height(root); }

    template <class Function>
    void map(const Function& fun) { map(fun, root); }

    void print() {
        map([](const DataType& x) {std::cout << x << ' '; });
        std::cout << '\n';
    }

    void printByLevels() const { printByLevels(root); }
private:
    struct node
    {
        DataType data;
        node* child, * brother;

        node(const DataType& data, node* child = nullptr, node* brother = nullptr)
            : data(data)
            , child(child)
            , brother(brother)
        {}
    } *root;

    size_t size;

private:

    void clear(node* root)
    {
        if (root) {
            clear(root->child);
            clear(root->brother);
            delete root;
        }
    }

    node* copy(node* root)
    {
        return root ?
            new node(root->data, copy(root->child), copy(root->brother)) :
            root;
    }

    bool find(const node* root, const DataType& key) const
    {
        if (!root) return false;
        if (root->data == key) return true;
        return find(root->brother, key) || find(root->child, key);
    }

    size_t height(const node* root) const
    {
        if (!root) return 0;
        return std::max(1+height(root->child), height(root->brother));
    }

    template <class Function>
    void map(const Function& fun, node* root) {
        if (root) {
            fun(root->data);
            map(fun, root->brother);
            map(fun, root->child);
        }
    }

    bool remove(node*& root, const DataType& key) {
        if (!root) return false;

        if (root->data == key) {
            node* toDelete = root;
            if (!root->child) {
                root = root->brother;
            }
            else if (root->brother){
                node* it = root->child;
                while (it->brother) it = it->brother;
                it->brother = root->brother->child;
                root->brother->child = root->child;
                root = root->brother;
            }
            else {
                root = root->child;
            }
            --size;
            delete toDelete;
            return true;
        }
        else {
            return remove(root->brother, key) || remove(root->child, key);
        }
    }

    bool insert(node*& root, const DataType& key, const int* path)
    {
        //Connect the new element as a sibling of the root
        if (path[0] < 0) {
            root = new node(key, nullptr, root);
            return true;
        }

        // No child -> invalid path?
        if (!root) return false;

        // Recursively connect among the children
        if (path[0] == 0) {
            return insert(root->child, key, path + 1);
        }

        // Find the proper node among the brothers
        node* it = root;
        int pos = path[0];
        while (it->brother && pos > 0) {
            it = it->brother;
            --pos;
        }
        return it->brother ? insert(it->brother->child, key, path + 1) : false;
    }

    void printByLevels(const node* root) const
    {
        if (!root) return;
        std::queue<const node*> front;
        front.push(root);
        front.push(nullptr);
        for (;;) {
            const node* current = front.front();
            front.pop();
            if (!current) {
                std::cout << '\n';
                if (front.empty()) return;
                front.push(nullptr);
            }
            else {
                std::cout << current->data << ' ';
                for (const node* it = current->child; it; it = it->brother) {
                    front.push(it);
                }
            }
        }
    }
};

} //namespace sdp
} //namespace fmi

#endif //__TREE_HEADER_INCLUDED_
