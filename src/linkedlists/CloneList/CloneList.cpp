#include <iostream>
using namespace std;

struct Node
{
    int data = 0;
    Node *next = nullptr;
    Node *random = nullptr;
    Node (int x) : data(x)
    {}
};

// Utility function to print the list.
void PrintList(const Node *head)
{
    while (head)
    {
        auto randomData = (head->random) ? head->random->data : 0;
        cout << "Data = " << head->data << ", Random  = " << randomData << endl;
        head = head->next;
    }
}

Node* CloneList(Node *head)
{
    if (!head)
    {
        return head;
    }
    Node *cloneHead = nullptr;
    Node *current = head, *temp = nullptr;
    
    // insert additional node after every node of original list
    while (current)
    {
        temp = current->next;
        current->next = new(std::nothrow)Node(current->data);
        if (!current->next)
        {
            return nullptr;
        }
        current->next->next = temp;
        current = temp;
    }
    cloneHead = head->next;

    // adjust the random pointers of the newly added nodes
    current = head;
    while (current)
    {
        current->next->random = (current->random) ? current->random->next : nullptr;
        current = (current->next) ? current->next->next : nullptr;
    }

    current = head;
    Node *cloneCurrent = current->next;
    while (current && cloneCurrent)
    {
        current->next = (current->next) ? current->next->next : nullptr;
        cloneCurrent->next = (cloneCurrent->next) ? cloneCurrent->next->next : nullptr;
        current = current->next;
        cloneCurrent = cloneCurrent->next;
    }
    return cloneHead;
}

int main()
{
    Node *head = new Node(1);
    head->next = new Node(2);
    head->next->next = new Node(3);
    head->next->next->next = new Node(4);
    head->next->next->next->next = new Node(5);
 
    // 1's random points to 3
    head->random = head->next->next;
 
    // 2's random points to 1
    head->next->random = head;
 
    // 3's and 4's random points to 5
    head->next->next->random = head->next->next->next->next;
    head->next->next->next->random = head->next->next->next->next;
 
    // 5's random points to 2
    head->next->next->next->next->random = head->next;
 
    cout << "Original list : \n";
    PrintList(head);
 
    cout << "\nCloned list : \n";
    Node *cloned_list = CloneList(head);
    PrintList(cloned_list);
 
    return 0;
}