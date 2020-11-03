#ifndef LIST
#define LIST

template<typename T>
class List {
    struct Node {
        T data;
        Node* next;

        Node(T data, Node* next): data(data), next(next) {}
    };
    Node* head;

public:
    List(): head(NULL) {}
    List(const List& other) = delete;
    const List& operator=(const List& other) = delete;
    ~List() {
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
        if(head == NULL) {
            head = new Node(element, NULL);
        } else {
            Node* lastElement = head;
            for(;lastElement->next != NULL; lastElement = lastElement->next);
            lastElement->next = new Node(element, NULL);
        }
    }

    void push_front(T element) {
        head = new Node(element, head);
    }

    void pop_back() {
        if(empty()) {
            throw "empty list";
        }

        if(head->next == NULL) {
            delete head;
            head = NULL;
            return;
        }

        Node* lastElement = head;
        for(;lastElement->next->next != NULL; lastElement = lastElement->next);
        delete lastElement->next;
        lastElement->next = NULL;
    }

    void pop_front() {
        if(empty()) {
            throw "empty list";
        }

        Node* oldHead = head;
        head = head->next;
        delete oldHead;
    }

    void insert(T element, int index) {
        Node* insertionNode = head;
        for(; index > 0; --index) {
            if(insertionNode == NULL) {
                throw "no such index in list";
            }
            insertionNode = insertionNode->next;
        }
        insertionNode->next = new Node(element, insertionNode->next);
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
        deletionNode->next = oldNode->next;
        delete oldNode;
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

        Node* back = head;
        for(; back->next != NULL; back = back->next);
        return back->data;
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

#endif // LIST
