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
class ForwardList
{
private:
    struct Node;

public:
    ForwardList();
    ForwardList(std::initializer_list<T> il);
    ForwardList( const ForwardList<T>& );
    ForwardList<T>& operator=( const ForwardList<T>& );
    ~ForwardList();

public:
    class iterator
    {
        friend ForwardList;
    public:
        typedef iterator                  self_type;
        typedef T                         value_type;
        typedef T&                        reference;
        typedef T*                        pointer;
        typedef int                       difference_type;

        iterator( Node* ptr = nullptr ) : m_node_ptr( ptr ) {}
    public:
        /* access operators */
        reference operator*() { return *m_node_ptr; }
        const reference operator*() const { return *m_node_ptr; }
        pointer operator->() { return m_node_ptr; }

        /* compare operators */
        bool operator==(const self_type& rhs) const { return m_node_ptr == rhs.m_node_ptr; }
        bool operator!=(const self_type& rhs) const { return !(rhs == *this); }

        /* modifier operators */
        self_type& operator++() { // prefix ++

            m_node_ptr = m_node_ptr->pNext;
            return *this;
        }

        self_type operator++(int) { // postfix ++

            self_type res(*this);
            ++(*this);
            return res;
        }

    private:
        Node* m_node_ptr;
    };

private:
    void copy( const ForwardList<T>& other);
    void clean();
public:
    void push_front( const T& element);
    void pop_front();

    iterator insertAfter( const iterator& it, const T& element);
    iterator removeAfter( const iterator& it );

    iterator begin() const
    {
        return iterator( head );
    }

    iterator end() const
    {
        return iterator( tail->pNext );
    }

public:
    inline T& front()
    {
        return head->data;
    }
    inline const T& front() const
    {
        return head->data;
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
        T data;

        Node( const T& data, Node* nextNode ): data( data ), pNext( nextNode ) {}
    };

    Node* head;
    Node* tail;

    size_t size;
};

template<class T>
ForwardList<T>::ForwardList(): head( nullptr ), tail( nullptr ), size( 0 ) {}

template<class T>
inline ForwardList<T>::ForwardList( std::initializer_list<T> il )
{
    for ( typename std::initializer_list<T>::iterator it = il.end() - 1;
        it >= il.begin();
        --it )
    {
        this->push_front( *it );
    }
}

template<class T>
ForwardList<T>::ForwardList( const ForwardList<T>& other )
{
    this->copy( other );
}

template<class T>
ForwardList<T>& ForwardList<T>::operator=( const ForwardList<T>& other )
{
    if ( this != &other )
    {
        this->clean();
        this->copy( other );
    }
    return *this;
}


template<class T>
ForwardList<T>::~ForwardList()
{
    this->clean();
}

template<class T>
void ForwardList<T>::copy( const ForwardList<T>& other )
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

            copied->pNext = new Node( toCopy->data );
            copied = copied->pNext;
            size++;
        }

        tail = copied;
    }
    catch (...)
    {
        this->clean();
        throw;
    }
}

template<class T>
void ForwardList<T>::clean()
{
    while ( !this->isEmpty() )
    {
        this->pop_front();
    }
}

template<class T>
void ForwardList<T>::print() const
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
void ForwardList<T>::push_front( const T& newData )
{
    head = new Node( newData, head );
    if ( size == 0 )
    {
        tail = head;
    }
    ++size;
}

template<class T>
void ForwardList<T>::pop_front()
{
    if ( size == 0 )
    {
        throw std::logic_error( "the list is empty!\n" );
    }
    Node* temp = head;
    head = head->pNext;
    delete temp;
    --size;
    if ( size == 0 )
    {
        tail = nullptr;
    }
}

template<class T>
typename ForwardList<T>::iterator ForwardList<T>::insertAfter( const iterator& it, const T& newData )
{
    Node* new_node = new Node( newData, it.m_node_ptr->pNext );

    it.m_node_ptr->pNext = new_node;

    if ( new_node->pNext == nullptr )
    {
        tail = new_node;
    }

    ++size;
    return new_node;
}

template<class T>
typename ForwardList<T>::iterator ForwardList<T>::removeAfter( const iterator& it )
{
    if ( this->isEmpty() )
    {
        throw std::logic_error( "empty forward list!" );
    }

    Node* removed = it.m_node_ptr->pNext;
    it.m_node_ptr->pNext = removed->pNext;

    if ( removed->pNext == nullptr )
    {
        tail = it.m_node_ptr;
    }

    delete removed;

    --size;
    return it.m_node_ptr->pNext;
}

} // end namespace dsa