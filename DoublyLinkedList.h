#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

template <typename T>
class DoublyLinkedList
{
    typedef struct Node
    {
        Node* prev;
        Node* next;
        T data;
    } *NodePtr;

public:
    DoublyLinkedList(): _size(0), _head(0) {}

    ~DoublyLinkedList(){

        while(_size)
            remove(_head->data);

    }

    bool isEmpty() const {return _size == 0;}
    int size() const {return _size;}

    bool insert(const T& item)
    {
        if(!_head)
        {
            _head = new Node;
            _head->data = item;
            _head->prev = _head;
            _head->next = _head;
            ++_size;
            return true;
        }

        NodePtr ptr = _head->next;

        while(ptr)
        {
            if(ptr->data == item) return false;

            if( !(ptr->data < item) || ptr == _head)
            {                
                NodePtr temp = new Node;
                temp->data = item;
                temp->prev = ptr->prev;
                temp->next = ptr;
                ptr->prev->next = temp;
                ptr->prev = temp;

                ++_size;
                return true;
            }

            ptr = ptr->next;
        }

        return false;
    }

    bool remove(const T& item)
    {
        if(!_head) return false;

        if(_head->data == item)
        {
            if(_size == 1)
            {
                delete _head;
                _head = 0;
            }
            else
            {
                NodePtr temp = _head;
                _head->prev->next = _head->next;
                _head->next->prev = _head->prev;
                _head = _head->next;
                delete temp;
            }

            --_size;
            return true;
        }

        NodePtr ptr = _head->next;
        while(ptr != _head)
        {
            if(ptr->data == item)
            {
                ptr->prev->next = ptr->next;
                ptr->next->prev = ptr->prev;
                delete ptr;
                --_size;
                return true;
            }
            ptr = ptr->next;
        }

        return false;
    }

    T* search(const T& item) const
    {
        NodePtr ptr = _head;
        while(!ptr)
        {
            if(ptr->data == item)
                return &(ptr->data);
            ptr = ptr->next;

            if(ptr == _head)
                break;
        }
        return 0;
    }

private:
    NodePtr _head;
    unsigned int _size;
};

#endif // DOUBLYLINKEDLIST_H
