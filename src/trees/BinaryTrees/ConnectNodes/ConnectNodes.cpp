#include <iostream>
#include <queue>
#include <vector>
using namespace std;

// Connects nodes of a binary tree at the same level using constant extra space
struct Node
{
    int data = 0;
    Node* left = nullptr;
    Node* right = nullptr;
    Node* nextRight = nullptr;
    Node(int _data) : data(_data)
    {}
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

void LevelOrder(const Node* root)
{
    if (!root)
    {
        return;
    }

    queue<const Node*> q;
    q.push(root);
    q.push(nullptr);
    while (!q.empty())
    {
        const Node* node = q.front();
        q.pop();
        if (node != nullptr)
        {
            cout << node->data << " ";
            if (node->left)
            {
                q.push(node->left);
            }
            if (node->right)
            {
                q.push(node->right);
            }
            if (node->nextRight)
            {
                q.push(node->nextRight);
            }
        }
        else
        {
            if (!q.empty() && q.front() != nullptr)
            {
                q.push(nullptr);
            }
            cout << endl;
        }
    }
}

Node* getNextRight(Node* root)
{
    if (!root)
    {
        return root;
    }
    
    Node* temp = root->nextRight;
    while (temp)
    {
        if (temp->left)
        {
            return temp->left;
        }
        else if (temp->right)
        {
            return temp->right;
        }
        temp = temp->nextRight;
    }
    return nullptr;
}

void ConnectRecur(Node* root)
{
    if (!root)
    {
        return;
    }

    if (root->nextRight)
    {
        ConnectRecur(root->nextRight);
    }

    if (root->left)
    {
        if (root->right)
        {
            root->left->nextRight = root->right;
            root->right->nextRight = getNextRight(root);
        }
        else
        {
            root->left->nextRight = getNextRight(root);
        }
        ConnectRecur(root->left);
    }
    else if (root->right)
    {
        root->right->nextRight = getNextRight(root);
        ConnectRecur(root->right);
    }
    else
    {
        ConnectRecur(getNextRight(root));
    }
}

void Connect(Node* root)
{
    if (!root)
    {
        return;
    }

    root->nextRight = nullptr;
    ConnectRecur(root);
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

    LevelOrder(root);
    cout << endl;
    return 0;
}