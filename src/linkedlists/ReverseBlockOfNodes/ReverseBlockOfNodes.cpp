#include <iostream>
using namespace std;

struct ListNode
{
    int data = 0;
    ListNode *next = nullptr;
    ListNode(int val) : data(val), next(nullptr)
    {}
};

void PrintList(const ListNode *head)
{
    cout << "List contents " << endl;
    while (head) {
        cout << head->data << " ";
        head = head->next;
    }
    cout << endl;
}

void DeleteList(ListNode *&head)
{
    ListNode *temp = head;
    while (head)
    {
        temp = head;
        head = head->next;
        delete temp;
    }
    head = nullptr;
}

ListNode* ReverseKBlocks(ListNode *head, int n, int k, bool& startReverse)
{
    if (!head || n < 0 || k <= 0)
    {
        return head;
    }
    n = (n+1) % k;
    ListNode *current = head;
    ListNode *Next = head->next;
    ListNode *newHead = ReverseKBlocks(head->next, n, k, startReverse);
    if (n == 0)
    {
        if (!startReverse)
        {
            startReverse = true;
            return current;
        }
        else
        {
            current->next = newHead;
            return current;
        }
    }
    else if (startReverse)
    {
        current->next = Next->next;
        Next->next = current;
        return newHead;
    }
    return current;
}

int main()
{
    auto i = 0;
    while (i < 2)
    {
        int k = 0;

        // 2 test cases
        ListNode *head = new ListNode(1);
        head->next = new ListNode(2);
        head->next->next = new ListNode(3);
        ListNode *four = new ListNode(4);
        head->next->next->next = four;
        
        four->next = new ListNode(5);
        four->next->next = new ListNode(6);
        four->next->next->next = new ListNode(7);
        
        ListNode *eight = new ListNode(8);
        four->next->next->next->next = eight;
        
        PrintList(head);

        if (i == 0) { k = 3; }
        else if (i == 1) { k = 5; }
        bool startReverse = false;
        ListNode *temp = ReverseKBlocks(head, 0, k, startReverse);

        PrintList(temp);
        DeleteList(temp);
        cout << endl;
        i++;
    }
    return 0;
}
