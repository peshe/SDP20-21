/******************************************************************
*  Sample code to the course "Data Structures And Algorithms", FMI
*
* A template class for dynamic array.
* The implementation of the proxy class (Proxy design pattern).
* It is needed, as we want to handle change of a value, using [] operator.
*
* (cc) Petar Armyanov, FMI, 2020
*******************************************************************/

#ifndef _SORTED_ARRAY_PROXY_INCLUDED__
#define _SORTED_ARRAY_PROXY_INCLUDED__

class SortedArrayProxy
{
    friend class SortedArray;
public:

    // In case we want to read the data
    // we use the proxy in context, where DataType rvalue is expected, 
    // so here is a cast operator
    operator const DataType&() const 
    { 
        return owner.array[index]; 
    }

    // In case we want to change the data
    // the proxy class is used in context, where DataType is lvalue,
    // so here is an assignment operator
    const DataType& operator=(const DataType& data)
    {        
        // If we increase the value
        if (owner.array[index] < data)
        {
            owner.array[index] = data;
            owner.moveDown(index); // move the new value towards the end
        }
        // if the new value is smaller
        else if (data < owner.array[index])
        {
            owner.array[index] = data;
            owner.moveUp(index); // move it towards the end
        }
        // In other case the value is the same
        else
        {
            // and we just assign it
            // It is necessary in case the comparison key is not the whole value
            owner.array[index] = data;
        }
        return *this;
    }

    // Allow a proxy object to be assigned to another proxy object
    // Note, we do not want default assignment implementation
    // Note also, that default copy ctor is available
    const DataType& operator=(const SortedArrayProxy& rhs)
    {
        return operator=((const DataType&)rhs);
    }

private:
    // Private constructor.
    SortedArrayProxy(SortedArray& owner, size_t index)
        : owner(owner)
        , index(index)
    {}

private: 
    SortedArray& owner;
    size_t index;
};

#endif //_SORTED_ARRAY_PROXY_INCLUDED__
