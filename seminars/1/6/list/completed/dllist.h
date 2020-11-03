#ifndef DLLIST
#define DLLIST

template<typename T>
class DoublyLinkedList {
    struct Node {
        T data;
        Node* prev;
        Node* next;

        Node(T data, Node* prev, Node* next): data(data), prev(prev), next(next) {}
    };
    Node* head;
    Node* tail;

public:
    DoublyLinkedList(): head(NULL), tail(NULL) {}
    DoublyLinkedList(const DoublyLinkedList& other) = delete;
    const DoublyLinkedList& operator=(const DoublyLinkedList& other) = delete;
    ~DoublyLinkedList() {
        while(!empty()) {
            pop_front();
        }
    }

    class Iterator {
        Node* current;

    public:

        Iterator(Node* current) : current(current) {}

        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }

        Iterator& operator++() {
            if(current == NULL) {
                throw "no next element";
            }

            current = current->next;
        }

        T operator*() {
            return current->data;
        }
    };

    Iterator begin() {
        return Iterator(head);
    }

    Iterator end() {
        return Iterator(NULL);
    }

    void push_back(T element) {
        if(tail == NULL) {
            head = tail = new Node(element, NULL, NULL);
        } else {
            tail->next = new Node(element, tail, NULL);
            tail = tail->next;
        }
    }

    void push_front(T element) {
        head = new Node(element, head);
        if(tail == NULL) {
            tail = head;
        }
    }

    void pop_back() {
        if(empty()) {
            throw "empty list";
        }

        if(tail == head) {
            delete tail;
            tail = head = NULL;
            return;
        }

        tail = tail->prev;
        delete tail->next;
        tail->next = NULL;
    }

    void pop_front() {
        if(empty()) {
            throw "empty list";
        }

        if(head == tail) {
            delete head;
            head = tail = NULL;
        }

        head = head->next;
        delete head->prev;
        head->prev = NULL;
    }

    void insert(T element, int index) {
        Node* insertionNode = head;
        for(; index > 0; --index) {
            if(insertionNode == NULL) {
                throw "no such index in list";
            }
            insertionNode = insertionNode->next;
        }
        Node* newNode = new Node(element, insertionNode, insertionNode->next);
        insertionNode->next = newNode;
        newNode->next->prev = newNode;
    }

    void remove(int index) {
        Node* deletionNode = head;
        for(; index > 1; --index) {
            if(deletionNode == NULL || deletionNode->next == NULL) {
                throw "no such index in list";
            }
            deletionNode = deletionNode->next;
        }

        Node* oldNode = deletionNode->next;
        deletionNode->next = deletionNode->next->next;
        delete oldNode;
        if(deletionNode->next != NULL) {
            deletionNode->next->prev = deletionNode;
        }
    }

    const T& getFront() const {
        if(empty()) {
            throw "list is empty";
        }

        return head->data;
    }

    const T& getBack() const {
        if(empty()) {
            throw "list is empty";
        }

        return tail->data;
    }

    const T& getAt(int index) {
        Node* getNode = head;
        for(; index > 0; --index) {
            if(getNode == NULL) {
                throw "no such index in list";
            }
            getNode = getNode->next;
        }
        return getNode->data;
    }

    const bool empty() const {
        return head == NULL;
    }

};

#endif // DLLIST
