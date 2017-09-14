#include <iostream>
#include <stdexcept>
#include <unordered_map>
#include <vector>

using namespace std;

class Queue;
class Hashtable;

class QueueNode
{
    size_t id = 0;
    QueueNode *prev = nullptr;
    QueueNode *next = nullptr;
    
    QueueNode(size_t _id) : id(_id)
    {}
    friend class Queue;
    
    static QueueNode* GetQueueNode(size_t pageid)
    {
        return new (nothrow) QueueNode(pageid);
    }
};

class Queue
{  
    size_t size = 0;
    size_t capacity = 0;
    QueueNode *front = nullptr;
    QueueNode *rear = nullptr;

    friend class Hashtable;
    Queue(size_t _capacity) : capacity(_capacity)
    {}

    bool isEmpty() const
    {
        return size == 0;
    }

    bool isFull() const
    {
        return size == capacity;
    }

    QueueNode* Enqueue(size_t id)
    {
        if (isFull())
        {
            throw length_error("Queue size full");
        }

        QueueNode *node = QueueNode::GetQueueNode(id);
        if (!node)
        {
            return nullptr;
        }

        if (!rear)
        {
            front = rear = node;
        }
        else
        {
            rear->next = node;
            node->prev = rear;
            rear = node;
        }
        size++;
        return node;
    }

    size_t Dequeue()
    {
        if (isEmpty())
        {
            throw length_error("Queue size empty");
        }

        QueueNode *node = front;
        front = front->next;
        if (front)
        {
            front->prev = nullptr;
        }
        else
        {
            rear = nullptr;
        }
        
        size--;
        size_t id = node->id;
        delete node;
        return id;
    }

    void MovetoEnd(QueueNode *node)
    {
        if (!node)
        {
            return;
        }
        else if (isEmpty())
        {
            throw length_error("Queue size empty");
        }

        if (node->next)
        {
            if (node->prev)
            {
                node->prev->next = node->next;
                node->next->prev = node->prev;
            }
            else
            {
                front = front->next;
                front->prev = nullptr;
            }
            rear->next = node;
            node->prev = rear;
            rear = node;
            rear->next = nullptr;            
        }
    }
    void PrintQueue() 
    {
        auto temp = front;
        while (temp)
        {
            cout << temp->id << " ";
            temp = temp->next;
        }
    }

    ~Queue()
    {
        while (front)
        {
            auto temp = front;
            front = front->next;
            delete temp;
        }
        size = capacity = 0;
        front = rear = nullptr;
    }
};

class Hashtable
{
    Queue q;
    unordered_map<size_t, QueueNode *> lookup;
public:
    Hashtable(size_t capacity) : q(capacity)
    {}
    void ReferencePage(size_t id)
    {
        if (lookup.find(id) == lookup.cend())
        {
            if (q.isFull())
            {
                auto id = q.Dequeue();
                lookup.erase(id);
            }
            lookup[id] = q.Enqueue(id);
        }
        q.MovetoEnd(lookup[id]);

        cout << "referencing page id: " << id << endl;
        cout << "status of q: ";
        q.PrintQueue(); 
        cout << endl;
    }    
};

int main()
{
    size_t hashTableCapacity = 4;
    Hashtable ht(hashTableCapacity);
    cout << "Hash table capacity is " << hashTableCapacity << endl;
    ht.ReferencePage(1);
	ht.ReferencePage(2);
	ht.ReferencePage(3);
	ht.ReferencePage(1);
	ht.ReferencePage(4);
    ht.ReferencePage(5);
    ht.ReferencePage(6);
    ht.ReferencePage(1);
    return 0;
}