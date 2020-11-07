#include "ForwardList.hpp"

namespace dsa
{


// Task 1
template<class T>
inline ForwardList<T>& ForwardList<T>::reverse()
{
    tail    = head;

    Node*   prev    = nullptr;
    Node*   next    = head->pNext;
    while ( next )
    {
        head->pNext = prev;
        prev        = head;
        head        = next;
        next        = next->pNext;
    }

    head->pNext = prev;

    return *this;
}


// Task 2
template<class T>
inline ForwardList<T>& ForwardList<T>::removeDuplicates()
{
    Node*   curr    = head;
    Node*   next    = curr->pNext;

    while ( next )
    {
        if ( curr->data == next->data )
        {
            next = this->removeAfter( curr );
        }
        else
        {
            curr = curr->pNext;
            next = next->pNext;
        }
    }

    return *this;
}


// Task 3
template<class T>
inline ForwardList<T>& ForwardList<T>::removeRepeated()
{
    for ( Node* curr = head; curr != nullptr; curr = curr->pNext )
    {
        for ( Node* remover = curr; remover->pNext != nullptr; )
        {
            if ( curr->data == remover->pNext->data )
            {
                this->removeAfter( remover );
            }
            else
            {
                remover = remover->pNext;;
            }
        }
    }

    return *this;
}


} // end namespace dsa
