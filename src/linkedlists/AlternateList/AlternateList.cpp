#include <iostream>
#include <vector>
using namespace std;

class LinkedListNode 
{
public:
    int val;
    LinkedListNode *next = nullptr;

    LinkedListNode(int _val) : val(_val)
    {}
    LinkedListNode() = default;
};

LinkedListNode* InsertIntoSinglylinkedlist(LinkedListNode *head, LinkedListNode *tail, int val) 
{
    if (head == nullptr)
    {
        head = new(std::nothrow)LinkedListNode(val);
        if (!head)
        {
            return nullptr;
        }
        tail = head;
    }
    else 
    {
        LinkedListNode *node = new(std::nothrow)LinkedListNode(val);
        if (!node)
        {
            return nullptr;
        }
        tail->next = node;
        tail = tail->next;
    }
    return tail;
}

void DeleteList(LinkedListNode *&head)
{
    while (head)
    {
        LinkedListNode *temp = head;
        head = head->next;
        delete temp;
    }
    head = nullptr;
}

void PrintList(const LinkedListNode *head)
{
    while (head)
    {
        cout << head->val << " ";
        head = head->next;
    }
}

void alternativeSplit(LinkedListNode *head, LinkedListNode *&pList1, LinkedListNode *&pList2)
{
    if (!head)
    {
        return;
    }

    LinkedListNode *list1 = head, *tail1 = head;
    LinkedListNode *list2 = head->next, *tail2 = head->next;
    LinkedListNode *current = head->next;

    bool flag = true;
    while (current && current->next)
    {
        current = current->next;
        if (flag)
        {
            tail1->next = current;
            tail1 = tail1->next;
        }
        else
        {
            tail2->next = current;
            tail2 = tail2->next;
        }
        flag = !flag;
    }
    
    if (tail1)
    {
        tail1->next = nullptr;
    }
    if (tail2)
    {
        tail2->next = nullptr;
    }
    
    pList1 = list1;
    pList2 = list2;
}

int main()
{    
    vector<vector<int>> inputs = 
    {
        {1},
        {1, 2},
        {-1, 2, 3},
        {1, 2, 3, 4},
        {1, 2, 3, 4, 5, 6, 7},
    };

    for (const auto& input : inputs)
    {
        LinkedListNode *pList = nullptr;
        LinkedListNode *pListTail = nullptr;

        for (size_t i = 0; i < input.size(); ++i)
        {
            pListTail = InsertIntoSinglylinkedlist(pList, pListTail, input[i]);
            if (i == 0)
            {
                pList = pListTail;
            }
        }
        cout << "Single linked list: ";
        PrintList(pList);
        cout << endl;

        cout << "After alterating: ";
        LinkedListNode *pList1 = nullptr, *pList2 = nullptr;
        alternativeSplit(pList, pList1, pList2);
        cout << "List1: ";
        PrintList(pList1);
        cout << " List2: ";
        PrintList(pList2);
        DeleteList(pList1);
        DeleteList(pList2);
        cout << endl;
    }
    
    return 0;
}
