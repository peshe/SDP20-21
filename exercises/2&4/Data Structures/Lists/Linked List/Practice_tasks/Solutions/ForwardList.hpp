//
// Created by Yasen Aleksiev on 25/10/20.
//
#pragma once

#include <cstdlib>
#include <iostream>
#include <stdexcept>

namespace dsa
{
template <class T>
class ForwardList
{
private:
    struct Node;

public:
    ForwardList();
    ForwardList( const std::initializer_list<T>& );
    ForwardList( const ForwardList<T>& );
    ForwardList<T>& operator=( const ForwardList<T>& );
    ~ForwardList();

public:
    class iterator
    {
        friend ForwardList;
    public:
        typedef iterator        self_type;
        typedef T               value_type;
        typedef T&              reference;
        typedef const T&        const_reference;
        typedef T*              pointer;
        typedef int             difference_type;

        iterator( Node* ptr = nullptr ) : m_node_ptr( ptr ) {}
    public:
        /* access operators */
        reference       operator*()         { return *m_node_ptr; }
        const_reference operator*() const   { return *m_node_ptr; }
        pointer         operator->()        { return m_node_ptr;  }

        /* compare operators */
        bool operator==(const self_type& rhs) const { return m_node_ptr == rhs.m_node_ptr; }
        bool operator!=(const self_type& rhs) const { return !(rhs == *this); }

        /* modifier operators */
        self_type& operator++();        // prefix ++
        self_type operator++( int );    // postfix ++

    private:
        operator        Node*()         { return m_node_ptr; }
        operator const  Node*() const   { return m_node_ptr; }

    private:
        Node* m_node_ptr;
    };

public:
    void            push_front( const T& element);
    void            push_back( const T& element);
    void            pop_front();
    void            pop()   { this->pop_front(); }

    iterator        insertAfter( const iterator& it, const T& element);
    iterator        removeAfter( const iterator& it );

    iterator        begin()     const   { return iterator( head );        }
    iterator        end()       const   { return iterator( tail->pNext ); }

    inline T&       front()             { return head->data; }
    inline const T& front()     const   { return head->data; }

    inline size_t   size()      const   { return currSize;      }
    inline bool     empty()     const   { return currSize == 0; }

    void            print()     const;

    /*** Tasks ***/
    ForwardList<T>& reverse();
    ForwardList<T>& removeDuplicates();
    ForwardList<T>& removeRepeated();

private:
    void copy( const ForwardList<T>& other);
    void clean();

private:
    struct Node
    {
        Node* pNext;
        T data;

        Node( const T& data, Node* nextNode = nullptr ) : data( data ), pNext( nextNode ) {}
    };

private:
    Node* head;
    Node* tail;
    size_t currSize;
};

} // end namespace dsa

#include "ForwardList.ipp"
#include "ForwardListTasks.ipp"
