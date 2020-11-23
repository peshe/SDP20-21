#include "DoubleLinkedList.hpp"

namespace dsa
{


// Task 4
template<class T>
inline DoubleLinkedList<T>& DoubleLinkedList<T>::append( DoubleLinkedList<T> other )
{
    this->tail->pNext   = other.head;
    other.head->pPrev   = this->tail;

    this->tail          = other.tail;
    this->size         += other.size;

    other.head          = nullptr;
    other.tail          = nullptr;
    other.size          = 0;

    return *this;
}


// Task 5
template<class T>
template<class Pred>
inline DoubleLinkedList<T>& DoubleLinkedList<T>::divide( const Pred& predicate )
{
    Node*   curr    = head;
    Node*   prev    = head->pPrev;
    Node*   next    = head->pNext;
    if ( this->size > 1 )
    {
        for ( size_t i = 0; i < this->size; i++ )
        {
            if ( predicate( curr->data ) )
            {
                // Set 'next' as the head if the head is about to be moved to the back
                if ( head == curr )
                    head = next;

                // Connect the two nodes beetween curr
                if ( prev )
                    prev->pNext = next;

                if ( next )
                    next->pPrev = prev;

                // Add curr to the end
                curr->pNext = nullptr;
                curr->pPrev = tail;
                tail->pNext = curr;
                tail        = curr;

                // Move the pointers by one except for prev
                curr    = next;
                if ( next )
                    next    = next->pNext;
            }
            else
            {
                prev    = curr;
                curr    = next;
                if ( next )
                    next    = next->pNext;
            }
        }
    }

    return *this;
}


}
