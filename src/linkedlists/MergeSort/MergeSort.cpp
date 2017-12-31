#include <iostream>
#include <vector>
using namespace std;

struct LinkedListNode 
{
public:
    int val = 0;
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
    cout << endl;
}

// Splits a list into two sublists — one for the front half, and one for the back half
// If the number of elements is odd, the extra element goes in the front list. 
// e.g. {2, 3, 5, 7, 11} should yield the two lists {2, 3, 5} and {7,11}
void FrontBackSplit(LinkedListNode *head, LinkedListNode *&a, LinkedListNode *&b)
{
    if (!head)
    {
        a = b = nullptr;
        return;
    }
    else if (!(head->next))
    {
        a = head;
        b = nullptr;
        return;
    }

    LinkedListNode *slow = head, *fast = head->next;
    while (fast && fast->next)
    {
        slow = slow->next;
        fast = fast->next->next;
    }

    b = slow->next;
    slow->next = nullptr;
    a = head;
}

// Takes two sorted lists and merges the two together into one list which is in increasing order
LinkedListNode* SortedMerge(LinkedListNode *a, LinkedListNode *b)
{
    LinkedListNode dummy;
    LinkedListNode *current = &dummy;

    while (true)
    {
        if (!a)
        {
            current->next = b;
            break;
        }
        else if (!b)
        {
            current->next = a;
            break;
        }
        else
        {
            if (a->val <= b->val)
            {
                current->next = a;
                a = a->next;
            }
            else
            {
                current->next = b;
                b = b->next;
            }
            current = current->next;
        }
    }
    return dummy.next;
}

LinkedListNode* MergeSort(LinkedListNode *head)
{
    if (!head || !(head->next))
    {
        return head;
    }

    LinkedListNode *a = nullptr, *b = nullptr;
    FrontBackSplit(head, a, b);
    a = MergeSort(a);
    b = MergeSort(b);
    return SortedMerge(a, b);
}

int main()
{
    vector<vector<int>> inputs = 
    {
        {1},
        {2, 1},
        {3, -1, 2},
        {2, 3, 1, 4},
        {5, 4, 6, 2, 1, 3, 7},
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
        cout << "After merging: ";
        PrintList(MergeSort(pList));
        cout << endl;
        DeleteList(pList);
    }
    return 0;
}