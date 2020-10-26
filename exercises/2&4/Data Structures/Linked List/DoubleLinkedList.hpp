//
// Created by Yasen Aleksiev on 25/10/20.
//
#pragma

#include <cstdlib>
#include <iostream>
#include <stdexcept>

namespace dsa
{
template <class T>
class DoubleLinkedList
{
public:
    DoubleLinkedList();
    DoubleLinkedList(std::initializer_list<T> il);
    DoubleLinkedList( const DoubleLinkedList<T>& );
    DoubleLinkedList<T>& operator=( const DoubleLinkedList<T>& );
    ~DoubleLinkedList();

public:

    class Node;
    class iterator
    {
        friend DoubleLinkedList;
    public:
        typedef iterator                  self_type;
        typedef T                         value_type;
        typedef T& reference;
        typedef T* pointer;
        typedef int                       difference_type;

        iterator( Node* ptr = nullptr ): m_node_ptr( ptr )
        {
        }
    public:
        /* access operators */
        reference operator*()
        {
            return *m_node_ptr;
        }
        const reference operator*() const
        {
            return *m_node_ptr;
        }
        pointer operator->()
        {
            return m_node_ptr;
        }

        /* compare operators */
        bool operator==( const self_type& rhs ) const
        {
            return m_node_ptr == rhs.m_node_ptr;
        }
        bool operator!=( const self_type& rhs ) const
        {
            return !( rhs == *this );
        }

        /* modifier operators */
        self_type& operator++()
        { // prefix ++

            m_node_ptr = m_node_ptr->pNext;
            return *this;
        }

        self_type operator++( int )
        { // postfix ++

            self_type res( *this );
            ++( *this );
            return res;
        }

        self_type& operator--() { // prefix --

            m_node_ptr = m_node_ptr->pPrev;
            return *this;
        }

        self_type operator--( int ) { //postfix --

            self_type res(*this);
            --(*this);
            return res;
        }

    private:
        Node* m_node_ptr;
    };

private:
    void copy( const DoubleLinkedList<T>& );
    void clean();
public:
    void push_front( const T& el );
    void pop_front();

    void push_back( const T& el );
    void pop_back();

    iterator insert( const iterator& it, const T& newElement );
    iterator remove( const iterator& it );

    iterator begin() { return iterator( head ); }

    iterator end() { return iterator( tail->pNext ); }

public:
    inline T& front()
    {
        return head->data;
    }
    inline const T& front() const
    {
        return head->data;
    }
    inline T& back()
    {
        return tail->data;
    }
    inline const T& back() const
    {
        return tail->data;
    }

public:
    inline size_t getSize() const
    {
        return size;
    }
    inline bool isEmpty() const
    {
        return size == 0;
    }

    void print() const;
private:
    struct Node
    {
        Node* pNext;
        Node* pPrev;
        T data;

        Node( const T& nextData, Node* nextNode = nullptr, Node* prevNode = nullptr ) 
                :   data( nextData ), pNext( nextNode ), pPrev( prevNode ) {}
    };

    Node* head;
    Node* tail;

    size_t size;
};

template<class T>
DoubleLinkedList<T>::DoubleLinkedList(): head( nullptr ), tail( nullptr ), size( 0 )
{
}

template<class T>
inline DoubleLinkedList<T>::DoubleLinkedList( std::initializer_list<T> il )
{
    for ( const T& el : il )
    {
        this->push_back( el );
    }
}

template<class T>
DoubleLinkedList<T>::DoubleLinkedList( const DoubleLinkedList<T>& other )
{
    this->copy( other );
}

template<class T>
DoubleLinkedList<T>& DoubleLinkedList<T>::operator=( const DoubleLinkedList<T>& other )
{
    if ( this != &other )
    {
        this->clean();
        this->copy( other );
    }
    return *this;
}


template<class T>
DoubleLinkedList<T>::~DoubleLinkedList()
{
    this->clean();
}

template<class T>
void DoubleLinkedList<T>::copy( const DoubleLinkedList<T>& other )
{
    if ( other.isEmpty() )
    {
        return;
    }

    try
    {
        head = new Node( other.head->data );
        Node* toCopy = other.head;
        Node* copied = head;

        while ( toCopy->pNext != nullptr )
        {
            toCopy = toCopy->pNext;

            copied->pNext = new Node( toCopy->data, nullptr, copied );
            copied = copied->pNext;
            size++;
        }

        tail = copied;
    }
    catch ( ... )
    {
        this->clean();
        throw;
    }
}

template<class T>
void DoubleLinkedList<T>::clean()
{
    while ( !this->isEmpty() )
    {
        this->pop_front();
    }
}

template<class T>
void DoubleLinkedList<T>::print() const
{
    Node* ptr = head;
    while ( ptr != nullptr )
    {
        std::cout << ptr->data << ' ';
        ptr = ptr->pNext;
    }
    std::cout << std::endl;
}

template<class T>
void DoubleLinkedList<T>::push_front( const T& newData )
{
    head = new Node( newData, head );
    if ( size == 0 )
    {
        tail = head;
    }
    
    ++size;
}

template<class T>
void DoubleLinkedList<T>::pop_front()
{
    if ( size == 0 )
    {
        throw std::logic_error( "the list is empty!\n" );
    }
    
    if ( size == 1 )
    {
        delete head;
        head = nullptr;
        tail = nullptr;
    }
    else
    {
        head = head->pNext;
        delete head->pPrev;
        head->pPrev = nullptr;
    }
    --size;
}

template<class T>
void DoubleLinkedList<T>::push_back( const T& newData )
{
    tail = new Node( newData, nullptr, tail );
    if ( size == 0 )
    {
        head = tail;
    }
    else
    {
        tail->pPrev->pNext = tail;
    }
    ++size;
}

template<class T>
void DoubleLinkedList<T>::pop_back()
{
    if ( size == 0 )
    {
        throw std::logic_error( "the list is empty!\n" );
    }
    if ( size == 1 )
    {
        delete head;
        head = nullptr;
        tail = nullptr;
        size = 0;
        return;
    }

    tail = tail->pPrev;
    delete tail->pNext;
    tail->pNext = nullptr;
    --size;
}

template<class T>
typename DoubleLinkedList<T>::iterator DoubleLinkedList<T>::insert( const iterator& it, const T& newData )
{
    if ( it == this->begin() || size < 2 )
    {
        this->push_front( newData );
        return iterator( head );
    }

    Node* prev = it.m_node_ptr->pPrev;

    Node* newNode = new Node( newData, it.m_node_ptr, prev );
    prev->pNext = newNode;

    it.m_node_ptr->pPrev = newNode;

    ++size;
    return newNode;
}

template<class T>
typename DoubleLinkedList<T>::iterator DoubleLinkedList<T>::remove( const iterator& it )
{
    if ( this->isEmpty() )
    {
        throw std::logic_error( "empty double linked list!" );
    }
    // there is no element
    if ( it == this->end() )
    {
        return end();
    }
    // first element case
    if ( it.m_node_ptr == head )
    {
        this->pop_front();
        return iterator( tail );
    }
    // last element case
    if ( it.m_node_ptr == tail )
    {
        this->pop_back();
        return iterator( tail );
    }

    Node* prev = it.m_node_ptr->pPrev;
    Node* next = it.m_node_ptr->pNext;

    // link the previous with the next
    prev->pNext = next;

    // link next with the previous
    next->pPrev = prev;

    // free the resources for the deleted box
    delete it.m_node_ptr;
    --size;

    return next;
}

}