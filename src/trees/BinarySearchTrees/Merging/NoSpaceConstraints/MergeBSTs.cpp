#include <iostream>
using namespace std;

struct Node
{
    int data = 0;
    Node* left = nullptr;
    Node* right = nullptr;

    Node(int _data) : data(_data)
    {}
    Node() = default;
};

void Bst2Dll(Node* root, Node*& head)
{
    if (!root)
    {
        return;
    }
    Bst2Dll(root->right, head);

    root->right = head;
    if (head)
    {
        head->left = root;
    }
    head = root;

    Bst2Dll(root->left, head);
}

Node* mergeLists(Node* a, Node* b)
{
    Node dummy;
    Node* current = &dummy;

    while (true)
    {
        if (!a)
        {
            current->right = b;
            break;
        }
        else if (!b)
        {
            current->right = a;
            break;
        }

        if (a->data <= b->data)
        {
            current->right = a;
            a = a->right;
        }
        else
        {
            current->right = b;
            b = b->right;
        }
        current = current->right;
    }
    return dummy.right;
}

size_t CountNodes(const Node* head)
{
    size_t count = 0;
    while (head)
    {
        ++count;
        head = head->right;
    }
    return count;
}

Node* _Dll2Bst(Node*& head, size_t count)
{
    if (!head || count == 0)
    {
        return nullptr;
    }

    Node* left = _Dll2Bst(head, count/2);

    Node* root = new(std::nothrow)Node(head->data);
    if (!root)
    {
        return root;
    }

    root->left = left;
    head = head->right;
    root->right = _Dll2Bst(head, count - count/2 - 1);

    return root;
}

Node* Dll2Bst(Node* head)
{
    size_t count = CountNodes(head);
    if (count == 0)
    {
        return nullptr;        
    }
    return _Dll2Bst(head, count);
}

Node* mergeTrees(Node* n1, Node* n2) 
{
    if (!n1)
    {
        return n2;
    }
    else if (!n2)
    {
        return n1;
    }

    Node* head1 = nullptr, *head2 = nullptr;
    Bst2Dll(n1, head1);
    Bst2Dll(n2, head2);

    Node* mergedHead = mergeLists(head1, head2);
    return Dll2Bst(mergedHead);
}

void Inorder(const Node* root)
{
    if (!root)
    {
        return;
    }
    Inorder(root->left);
    cout << root->data << " ";
    Inorder(root->right);
}

int main() 
{
    /*          
                5
              /   \
            3       7
          /   \   /   \
         2     4 6     9
    */
    Node* root1 = new(std::nothrow) Node(5);
    root1->left = new(std::nothrow) Node(3);
    root1->right = new(std::nothrow) Node(7);
    root1->left->left = new(std::nothrow) Node(2);
    root1->left->right = new(std::nothrow) Node(4);
    root1->right->left = new(std::nothrow) Node(6);
    root1->right->right = new(std::nothrow) Node(9);

    /*          
                10
              /    \
             8      12
           /   \   /   \
          0     9 11   15
    */
    Node* root2 = new(std::nothrow) Node(10);
    root2->left = new(std::nothrow) Node(8);
    root2->right = new(std::nothrow) Node(12);
    root2->left->left = new(std::nothrow) Node(0);
    root2->left->right = new(std::nothrow) Node(9);
    root2->right->left = new(std::nothrow) Node(11);
    root2->right->right = new(std::nothrow) Node(15);

    cout << "Tree 1: ";
    Inorder(root1);
    cout << endl;

    cout << "Tree 2: ";
    Inorder(root2);
    cout << endl;

    cout << "After merging: ";
    Node* root = mergeTrees(root1, root2);
    Inorder(root);
    cout << endl;
    return 0;
}
