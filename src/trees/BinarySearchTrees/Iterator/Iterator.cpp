#include <iostream>
#include <vector>
#include <stack>
using namespace std;

// Implements an iterator over a binary search tree
// calling next will return the next smallest number in bst
// calling hasNext will return whether the next element exits
struct Node
{
    int data = 0;
    Node* left = nullptr;
    Node* right = nullptr;

    Node(int _data) : data(_data)
    {}
};

size_t CountNodes(const Node* root)
{
    if (!root)
    {
        return 0;
    }
    return CountNodes(root->left) + CountNodes(root->right) + 1;
}

class BSTIterator
{
private:
    const Node* next = nullptr;
    stack<const Node*> stk;
    size_t totalNodes = 0;
    size_t currCount = 0;

    void pushNodes(const Node* root)
    {
        const Node* current = root;
        while (current)
        {
            if (current->right)
            {
                if (stk.empty() || stk.top() != current->right)
                {
                    stk.push(current->right);
                }
            }
            if (!stk.empty() && stk.top() == current)
            {
                break;
            }
            stk.push(current);
            current = current->left;
        }
    }

public:
    
    BSTIterator(const Node* root)
    {
        totalNodes = CountNodes(root);
        if (totalNodes > 0)
        {
            pushNodes(root);
        }
    }

    bool hasNext() const
    {
        return currCount < totalNodes;
    }

    const Node* Next()
    {
        if (!hasNext())
        {
            return nullptr;
        }
        next = stk.top();
        stk.pop();

        if (next->right)
        {
            pushNodes(next->right);
        }
        currCount++;
        return next;
    }
};

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
                1
              /   \
            2       3
          /   \   /   \
         4     5 6     7
    */
    Node* root = new(std::nothrow) Node(1);
    root->left = new(std::nothrow) Node(2);
    root->right = new(std::nothrow) Node(3);
    root->left->left = new(std::nothrow) Node(4);
    root->left->right = new(std::nothrow) Node(5);
    root->right->left = new(std::nothrow) Node(6);
    root->right->right = new(std::nothrow) Node(7);

    BSTIterator iter(root);
    while (iter.hasNext())
    {
        cout << iter.Next()->data << " ";
    }
    cout << endl;
    return 0;
}