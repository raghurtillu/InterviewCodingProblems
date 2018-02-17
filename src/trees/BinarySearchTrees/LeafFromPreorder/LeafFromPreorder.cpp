#include <iostream>
#include <vector>
#include <stack>
using namespace std;

// Find mirror of a given node
// The mirror of a node is a node which exists at the mirror position in the opposite subtree
//           9
//        /     \
//       5      ...
//      /  \
//     4    7
// 4 and 7 are leaves

// Print the leaf node from the given preorder of BST
void leafNode(const vector<int>& preOrder)
{
    if (preOrder.empty())
    {
        return;
    }

    stack<int> s;
    size_t n = preOrder.size();
    for (size_t i = 0, j = 1; j < n; i++, j++)
    {
        bool found = false;

        if (preOrder[i] > preOrder[j])
        {
            s.push(preOrder[i]);
        }
        else
        {
            while (!s.empty())
            {
                if (preOrder[j] > s.top())
                {
                    // if j is right subtree of i's parent
                    // e.g. j is 7 and i is 4
                    //          9
                    //        / 
                    //       5 
                    //      /  \
                    //     4    7
                    s.pop();
                    found = true;
                }
                else
                {
                    // if j is right subtree of i's parent
                    // e.g. j is 7 and i is 5
                    //          9
                    //        / 
                    //       5 
                    //         \
                    //          7
                    break;
                }
            }
        }

        if (found)
        {
            cout << preOrder[i] << " ";
        }
    }

    // Since rightmost element is always leaf node.
    cout << preOrder[n - 1];
}

// Driver code
int main()
{
    vector<vector<int>> values = 
    {
        { 9, 5, 4, 7 },
        { 9, 5, 4 },
        { 100, 50, 20, 40, 65 }
    };

    for (const auto& preOrder : values)
    {
        cout << "For the preorder: ";
        for (size_t i = 0; i < preOrder.size(); ++i)
        {
            cout << preOrder[i] << " ";
        }
        cout << endl;
        cout << "the leaf node(s) are: ";
        leafNode(preOrder);
        cout << endl << endl;
    }
    return 0;
}
