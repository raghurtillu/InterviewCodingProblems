#include <iostream>
using namespace std;

class LinkedListNode {
public:
    int val;
    LinkedListNode *next;

    LinkedListNode(int node_value) {
        val = node_value;
        next = NULL;
    }
};

LinkedListNode* _insert_node_into_singlylinkedlist(LinkedListNode *head, LinkedListNode *tail, int val) {
    if(head == NULL) {
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

size_t GetListSize(const LinkedListNode *head)
{
    size_t count = 0;
    while (head)
    {
        ++count;
        head = head->next;
    }
    return count;
}
LinkedListNode* swapNodes(LinkedListNode *head, size_t k)
{
    if (!head)
    {
        return head;
    }

    size_t n = GetListSize(head);
    if (k > n || k == (n+1)/2)
    {
        // if k == (n+1)/2, the swap nodes are the same
        return head;
    }

    LinkedListNode *x = head, *xPrev = nullptr;
    for (size_t i = 1; i < k; ++i)
    {
        xPrev = x;
        x = x->next;
    }

    LinkedListNode *y = head, *yPrev = nullptr;
    for (size_t i = 1; i < n-k+1; ++i)
    {
        yPrev = y;
        y = y->next;
    }

    if (xPrev)
    {
        xPrev->next = y;
    }
    if (yPrev)
    {
        yPrev->next = x;
    }
    
    auto temp = x->next;
    x->next = y->next;
    y->next = temp;

    if (k == 1)
    {
        return y;
    }
    else if (k == n)
    {
        return x;
    }
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

    size_t k = 3;
    cout << "after swapping " << k << endl;
    auto result = swapNodes(pList, k);
    PrintList(result);
    return 0;
}