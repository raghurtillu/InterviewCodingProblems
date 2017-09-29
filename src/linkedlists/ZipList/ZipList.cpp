#include <iostream>

using namespace std;
class LinkedListNode {
public:
    int val;
    LinkedListNode *next;

    LinkedListNode(int node_value) {
        val = node_value;
        next = nullptr;
    }
};

LinkedListNode* _insert_node_into_singlylinkedlist(LinkedListNode *head, LinkedListNode *tail, int val) {
    if(head == nullptr) {
        head = new LinkedListNode(val);
        tail = head;
    }
    else {
        LinkedListNode *node = new LinkedListNode(val);
        tail->next = node;
        tail = tail->next;
    }
    return tail;
}

void PrintList(const LinkedListNode* head)
{
    while (head != nullptr)
    {
        cout << head->val << " ";
        head = head->next;
    }
    cout << endl;
}

void _Zip(LinkedListNode *head, LinkedListNode *&zipNode, bool &stopZipping)
{
    if (!head)
    {
        return;
    }

    auto nextNode = head->next;
    _Zip(head->next, zipNode, stopZipping);

    if (stopZipping || !zipNode)
    {
        return;
    }
    if (nextNode)
    {
        nextNode->next = zipNode;
    }

    if (zipNode == head || zipNode->next == head)
    {
        if (nextNode)
        {
            nextNode->next = zipNode;
        }
        head->next = nullptr;
        stopZipping = true;
        return;
    }

    auto nextZipNode = zipNode->next;
    zipNode->next = head;
    zipNode = nextZipNode;
    head->next = nullptr;
}

LinkedListNode* Zip(LinkedListNode *head)
{
    if (!head || !(head->next))
    {
        // if empty or just sinble node list; simply return
        return head;
    }
    LinkedListNode *zipNode = head;
    bool stopZipping = false;
    _Zip(head, zipNode, stopZipping);
    return head;
}

int main()
{
    int pList_size = 5;

    LinkedListNode* pList = nullptr;
    LinkedListNode* pList_tail = nullptr;

    for(int i = 0; i < pList_size; i++) 
    {
        int pList_item = i+1;
        pList_tail = _insert_node_into_singlylinkedlist(pList, pList_tail, pList_item);

        if(i == 0) 
        {
            pList = pList_tail;
        }
    }
    PrintList(pList);
    cout << "after zipping" << endl;
    auto result = Zip(pList);
    PrintList(result);
    return 0;
}