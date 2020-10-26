template <class DataType>
inline LinkedQueue<DataType>::LinkedQueue(const LinkedQueue& queue)
    : begin(nullptr)
{
    try {
        copy(queue.begin);
    }
    catch (...) {
        clear();
        throw;
    }
}

template <class DataType>
inline LinkedQueue<DataType>::~LinkedQueue()
{
    clear();
}

template <class DataType>
inline LinkedQueue<DataType>& 
LinkedQueue<DataType>::operator=(const LinkedQueue<DataType>& rhs)
{
    if (this != &rhs) {
        clear();
        copy(rhs.begin);
    }
    return *this;
}

template <class DataType>
inline void LinkedQueue<DataType>::enqueue(const DataType& elem)
{
    node* n = new node(elem);
    if (isEmpty()) {
        begin = n;
    }
    else {
        end->next = n;
    }
    end = n;
}

template <class DataType>
inline DataType LinkedQueue<DataType>::dequeue()
{
    DataType res = first();
    node* keep = begin;
    begin = begin->next;
    delete keep;
    return res;
}

template <class DataType>
inline const DataType& LinkedQueue<DataType>::first() const
{
    if (!isEmpty())
        return begin->data;
    throw std::underflow_error("Empty queue");
}

template <class DataType>
inline bool LinkedQueue<DataType>::isEmpty() const
{
    return begin == nullptr;
}

template <class DataType>
inline void LinkedQueue<DataType>::clear()
{
    while (!isEmpty())
        dequeue();
}

template <class DataType>
inline void LinkedQueue<DataType>::copy(const node* start)
{
    assert(begin == nullptr && isEmpty());

    while (start) {
        enqueue(start->data);
        start = start->next;
    }
}
