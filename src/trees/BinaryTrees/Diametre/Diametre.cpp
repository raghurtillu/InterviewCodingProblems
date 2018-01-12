#include <iostream>
#include <utility>
using namespace std;

struct BinaryTreeNode
{
    int data = 0;
    BinaryTreeNode *left = nullptr;
    BinaryTreeNode *right = nullptr;

    BinaryTreeNode(int _data) : data(_data)
    {}
    BinaryTreeNode() = default;
};

size_t _diametreOfTree(const BinaryTreeNode* root, size_t &height)
{
    if (!root)
    {
        height = 0;
        return 0;
    }

    size_t leftHeight = 0, rightHeight = 0;
    size_t leftDiametre = _diametreOfTree(root->left, leftHeight);
    size_t rightDiametre = _diametreOfTree(root->right, rightHeight);
    height = max(leftHeight, rightHeight) + 1;
    size_t diametre = max(leftHeight + rightHeight + 1, max(leftDiametre, rightDiametre));
    return diametre;
}

size_t diametreOfTree(const BinaryTreeNode* root)
{
    size_t height = 0;
    return _diametreOfTree(root, height);
}

int main()
{
    // Constructed binary tree is 
    //        1
    //      /   \
    //     2     3
    //   /  \
    //  4    5

    BinaryTreeNode *root = new(std::nothrow) BinaryTreeNode(1);
    root->left        = new(std::nothrow) BinaryTreeNode(2);
    root->right       = new(std::nothrow) BinaryTreeNode(3);
    root->left->left  = new(std::nothrow) BinaryTreeNode(4);
    root->left->right = new(std::nothrow) BinaryTreeNode(5);
    cout << "Diametre of the tree is: " << diametreOfTree(root) << endl;
    return 0;
}
