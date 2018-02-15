#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Find mirror of a given node
// The mirror of a node is a node which exists at the mirror position in the opposite subtree
//           1
//        /     \
//       2       3
//      /  \    /  \
//     4    5  6    7
//           /   \
//          8     9
// 2 and 3 are mirrors
// 4 and 6 are mirrors

struct Node
{
    int data = 0;
    Node* left = nullptr;
    Node* right = nullptr;

    Node(int _data) : data(_data)
    {}
};

size_t _FindMirror(const Node* left, const Node* right, size_t input)
{
    if (!left || !right)
    {
        return SIZE_MAX;
    }

    // if left Node is target Node, then return right's key, which is the mirror and vice versa
	if (left->data == input)
	{
	    return right->data;
	}
	else if (right->data == input)
	{
	    return left->data;   
	}

	// first check external nodes
	int mirror = _FindMirror(left->left, right->right, input);
	if (mirror != SIZE_MAX)
	{
	    return mirror;  
	}

    // then check internal nodes
    return _FindMirror(left->right, right->left, input);
}

size_t FindMirror(const Node* root, int input)
{
	if (!root) { return SIZE_MAX; }
	else if (root->data == input) { return input; }
	return _FindMirror(root->left, root->right, input);
}

int main()
{
	Node* root = new(std::nothrow) Node(1);
    root->left        = new(std::nothrow) Node(2);
    root->right       = new(std::nothrow) Node(3);
    root->left->left  = new(std::nothrow) Node(4);
    root->left->right = new(std::nothrow) Node(5);
    root->right->left  = new(std::nothrow) Node(6);
    root->right->right  = new(std::nothrow) Node(7);
    root->right->left->left  = new(std::nothrow) Node(8);
    root->right->left->right = new(std::nothrow) Node(9);

    vector<size_t> inputs = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (size_t i = 0; i < inputs.size(); ++i)
    {
        size_t mirror = FindMirror(root, inputs[i]);
        if (mirror == SIZE_MAX)
        {
            cout << "Mirror of node: " << inputs[i] << " not found" << endl;
        }
        else
        {
            cout << "Mirror of node: " << inputs[i] << " is " << mirror << endl;
        }
    }
    return 0;
}
