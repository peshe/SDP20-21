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
class DoubleLinkedList
{
private:
    struct Node;

public:
    DoubleLinkedList();
    DoubleLinkedList( const std::initializer_list<T>& );
    DoubleLinkedList( const DoubleLinkedList<T>& );
    DoubleLinkedList<T>& operator=( const DoubleLinkedList<T>& );
    ~DoubleLinkedList();

public:

    class iterator
    {
        friend DoubleLinkedList;
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
        bool operator==( const self_type& rhs ) const { return m_node_ptr == rhs.m_node_ptr; }
        bool operator!=( const self_type& rhs ) const { return !( rhs == *this );            }

        /* modifier operators */
        self_type& operator++();        // prefix ++
        self_type operator++( int );    // postfix ++
        self_type& operator--();        // prefix --
        self_type operator--( int );    // postfix --

    private:
        Node* m_node_ptr;
    };

public:
    void            push_front( const T& el );
    void            pop_front();
    void            push_back( const T& el );
    void            pop_back();

    iterator        insert( const iterator& it, const T& newElement );
    iterator        remove( const iterator& it );

    iterator        begin()     const    { return iterator( head );        }
    iterator        end()       const    { return iterator( tail->pNext ); }

    inline T&       front()              { return head->data; }
    inline T&       back()               { return tail->data; }
    inline const T& front()     const    { return head->data; }
    inline const T& back()      const    { return tail->data; }
    inline size_t   getSize()   const    { return size;       }
    inline bool     isEmpty()   const    { return size == 0;  }

    void            print()     const;

    /*** Task 4 ***/
    DoubleLinkedList<T>&    append( DoubleLinkedList<T> other );

    /*** Task 5 ***/
    template<class Pred>
    DoubleLinkedList<T>&    divide( const Pred& predicate );

private:
    void copy( const DoubleLinkedList<T>& );
    void clean();

private:
    struct Node
    {
        Node* pNext;
        Node* pPrev;
        T data;

        Node( const T& nextData, Node* nextNode = nullptr, Node* prevNode = nullptr ) 
            : data( nextData ), pNext( nextNode ), pPrev( prevNode ) {}
    };

private:
    Node*   head;
    Node*   tail;
    size_t  size;
};


}

#include "DoubleLinkedList.ipp"
#include "DoubleLinkedListTasks.ipp"
