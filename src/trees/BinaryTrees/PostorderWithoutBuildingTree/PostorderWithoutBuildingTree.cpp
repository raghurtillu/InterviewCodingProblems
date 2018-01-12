// C++ program to print postorder traversal from preorder and inorder traversals
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

size_t getIndex(const unordered_map<int, size_t>& lookup, int val)
{
    auto it = lookup.find(val);
    if (it == lookup.cend())
    {
        return SIZE_MAX;
    }
    else
    {
        return it->second;
    }
}

void printPostOrder(const vector<int>& preOrder, size_t& pIndex,
    const vector<int>& inOrder, size_t low, size_t high,
    const unordered_map<int, size_t>& lookup)
{
    if (preOrder.empty() || inOrder.empty() || pIndex >= preOrder.size())
    {
        return;
    }
    else if (low >= inOrder.size() || high >= inOrder.size() || low > high || high - low > inOrder.size())
    {
        return;
    }

    int val = preOrder[pIndex];
    size_t index = getIndex(lookup, val);
    if (index == SIZE_MAX)
    {
        return;
    }
    
    ++pIndex;

    printPostOrder(preOrder, pIndex, inOrder, low, index - 1, lookup);
    printPostOrder(preOrder, pIndex, inOrder, index + 1, high, lookup);

    cout << val << " ";
}

void getPostOrder(const vector<int>& preOrder, const vector<int>& inOrder)
{
    if (inOrder.empty())
    {
        return;
    }

    unordered_map<int, size_t> lookup;
    for (size_t i = 0; i < inOrder.size(); ++i)
    {
        lookup[inOrder[i]] = i;
    }

    size_t pIndex = 0;
    size_t low = 0, high = inOrder.size() - 1;

    printPostOrder(preOrder, pIndex, inOrder, low, high, lookup);
}

int main()
{
    vector<int> inOrder = {4, 2, 5, 1, 3, 6};
    vector<int> preOrder = {1, 2, 4, 5, 3, 6};
    cout << "For the given InOrder: ";
    for (auto val : inOrder)
    {
        cout << val << " ";
    }
    cout << "and PreOrder: ";
    for (auto val : preOrder)
    {
        cout << val << " ";
    }
    cout << "the Postorder traversal is" << endl;
    getPostOrder(preOrder, inOrder);    
    cout << endl;
    return 0;
}
