#include <iostream>
#include <vector>
using namespace std;

// Example:
// Inputs:  1->2->3->4->5->6->7->8->9->10->NULL and k = 3 
// Output:  3->2->1->6->5->4->9->8->7->10->NULL
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

LinkedListNode* ReverseKBlocks(LinkedListNode *head, size_t n, size_t k)
{
    if (!head || k == 0 || n > k)
	{
        return head;
    }
    
    static bool startReverse = false;
    n = (n + 1) % k;
    LinkedListNode *current = head;
    LinkedListNode *next = head->next;
    LinkedListNode *newHead = ReverseKBlocks(head->next, n, k);
	if (!startReverse)
	{
		if (n == 0)
		{
			startReverse = true;
		}
	}
	else
	{
		if (n == 0)
		{
			current->next = newHead;
			return current;
		}
		else
		{
			if (next)
			{
				current->next = next->next;
				next->next = current;
				return newHead;
			}
		}
	}
    return current;
}

int main()
{
    vector<vector<int>> inputs = 
    {
        {1},
        {1, 2},
        {1, 2, 3},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
    };

	for (const auto& input : inputs)
	{
		for (size_t blockSize = 0; blockSize <= input.size(); ++blockSize)
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
			
			cout << "Linked list contents: ";
			PrintList(pList);
			cout << endl;

			cout << "After reversing in blocks of " << blockSize << ", contents are: " << endl;
			LinkedListNode *temp = ReverseKBlocks(pList, 0, blockSize);
			PrintList(temp);
			
			cout << endl << endl;
			DeleteList(pList);
		}
	}
    return 0;
}