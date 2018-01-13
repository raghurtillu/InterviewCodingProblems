#include <iostream>
#include <algorithm>
using namespace std;

// Returns the size of largest Binary Search Tree in a Binary Tree
// Input: 
//            50
//          /    \
//       10       60
//      /  \     /   \
//     5   20   55    70
//             /     /  \
//            45    65   80
// Output: 6
// The following subtree is the maximum size BST subtree 
//         60
//        /  \
//      55    70
//     /     /  \
//    45   65    80

struct MinMax
{
    bool isBst = true;
    size_t size = 0;
    int min = INT_MAX;
    int max = INT_MIN;
};

struct Node
{
    int data = 0;
    Node* left = nullptr;
    Node* right = nullptr;

    Node(int _data) : data(_data)
    {}
};

MinMax LargestBST(const Node* root)
{
    MinMax mm;
    if (!root)
    {
        return mm;
    }

    MinMax leftMinMax = LargestBST(root->left);
    MinMax rightMinMax = LargestBST(root->right);

    if (!leftMinMax.isBst || !rightMinMax.isBst ||  // if either left or right subtree is not a bst
        root->data < leftMinMax.max ||  // current node is less than its predecessor
        root->data > rightMinMax.min)   // current node is greater than its successor
    {
        // the current subtree is not a bst
        mm.isBst = false;
        mm.size = max(leftMinMax.size, rightMinMax.size);
    }
    else
    {
        // the current subtree is a bst
        mm.isBst = true;
        mm.size = leftMinMax.size + rightMinMax.size + 1;
        mm.min = root->left ? leftMinMax.min : root->data;
        mm.max = root->right ? rightMinMax.max : root->data;
    }
    return mm;
}

int main()
{
    Node* root = new(std::nothrow) Node(50);
    root->left        = new(std::nothrow) Node(10);
    root->right       = new(std::nothrow) Node(60);
    root->left->left  = new(std::nothrow) Node(5);
    root->left->right = new(std::nothrow) Node(20);
    root->right->left  = new(std::nothrow) Node(55);
    root->right->left->left  = new(std::nothrow) Node(45);
    root->right->right = new(std::nothrow) Node(70);
    root->right->right->left = new(std::nothrow) Node(65);
    root->right->right->right = new(std::nothrow) Node(80);

    MinMax mm = LargestBST(root);
    cout << "Size of largest BST is " << mm.size << endl;

    return 0;
}