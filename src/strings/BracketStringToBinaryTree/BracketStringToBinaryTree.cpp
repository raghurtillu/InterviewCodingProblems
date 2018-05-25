#include <iostream>
#include <string>
#include <stack>
#include <vector>
using namespace std;

// Construct a Binary tree from a string containing paranthesis as follows
// Input : "1(2)(3)" 
// Output : 1 2 3
// Explanation :
//            1
//           / \
//          2   3
// Explanation: first pair of parenthesis contains 
// left subtree and second one contains the right 
// subtree. Preorder of above tree is "1 2 3".  
//
// Input : "4(2(3)(1))(6(5))"
// Output : 4 2 3 1 6 5
// Explanation :
//            4
//          /   \
//         2     6
//        / \   / 
//       3   1 5 

struct TreeNode
{
    string data;
    TreeNode *left = nullptr;
    TreeNode *right = nullptr;
    TreeNode(const string& _data) : data(_data)
    { }

    static TreeNode* getTreeNode(const string& str)
    {
        return new(std::nothrow) TreeNode(str);
    }
};

void WalkTree(const TreeNode *root)
{
    if (!root) { return; }
    cout << root->data << " ";
    WalkTree(root->left);
    WalkTree(root->right);
}

int findIndex(const string& str, int low, int high)
{
    if (low < 0 || high < 0 || low >= str.size() || high >= str.size() || low > high)
    {
        return -1;
    }

    stack<char> stk;
    for (int i = low; i <= high; ++i)
    {
        if (str[i] == '(') { stk.push(str[i]); }
        else if (str[i] == ')')
        {
            if (!stk.empty() && stk.top() == '(')
            { stk.pop(); }

            if (stk.empty())
            { return i; }
        }
    }
    return -1;
}

TreeNode* _ConstructTree(const string& str, int low, int high)
{
    if (low < 0 || high < 0 || low >= str.size() || high >= str.size() || low > high)
    {
        return nullptr;
    }

    string data;
    int i = low;
    while (i <= high)
    {
        if (str[i] == '(') { break; }
        data.push_back(str[i++]);
    }
    TreeNode *root = TreeNode::getTreeNode(data);
    if (!root) { return root; }
    if (i > high) { return root; }

    int index = findIndex(str, i, high);
    if (index == -1) { return root; }

    root->left = _ConstructTree(str, i + 1, index - 1);
    root->right = _ConstructTree(str, index + 2, high - 1);

    return root;
}

TreeNode* ConstructTree(const string& str)
{
    if (str.empty()) { return nullptr; }
    return _ConstructTree(str, 0, str.size() - 1);
}

int main()
{
    vector<string> inputs = 
    {
        "()",
        "1",
        "1(2)(3)",
        "4(2(3)(1))(6(5))",
    };

    cout << "Binary tree representations for the strings: " << endl;
    for (size_t i = 0; i < inputs.size(); ++i)
    {
        const string& input = inputs[i];
        cout << i + 1 << ": " << input << endl;
        cout << "Ans: ";
        TreeNode *root = ConstructTree(input);
        if (!root) { cout << "Empty tree"; }
        else { WalkTree(root); }
        cout << endl;
    }
    return 0;
}