#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Check for identical Binary Search trees without building the trees
// for e.g.
// a[] = {8, 3, 6, 1, 4, 7, 10, 14, 13}
// b[] = {8, 10, 14, 3, 6, 4, 1, 7, 13}
//
// They both construct the same following BST and hence both the arrays represent identical trees
//            8
//         /    \
//       3       10
//     /  \        \
//    1     6       14
//        /   \     /
//       4     7   13  
//

bool areIdentical(const vector<int>& a, const vector<int>& b)
{
    if ((a.empty() && !b.empty()) || (!a.empty() && b.empty()))
    {
        return false;
    }
    else if (a.empty() && b.empty())
    {
        return true;
    }
    else if (a.size() != b.size() || a[0] != b[0])
    {
        return false;
    }

    vector<int> aLeft, aRight;
    vector<int> bLeft, bRight;

    // split the sequence into left and right based on the root of the bst
    int root = a[0];
    for (size_t i = 1; i < a.size(); ++i)
    {
        if (a[i] < root)
        {
            aLeft.push_back(a[i]);
        }
        else
        {
            aRight.push_back(a[i]);
        }

        if (b[i] < root)
        {
            bLeft.push_back(b[i]);
        }
        else
        {
            bRight.push_back(b[i]);
        }
    }
    return areIdentical(aLeft, bLeft) && areIdentical(aRight, bRight);
}

int main()
{
    vector<pair<vector<int>, vector<int>>> inputs = 
    {
        make_pair<vector<int>, vector<int>>(
            {2, 4, 1, 3},
            {2, 4, 3, 1}
        ),
        make_pair<vector<int>, vector<int>>(
            {3, 5, 4, 6, 1, 0, 2},
            {3, 1, 5, 2, 4, 6, 0}
        ),
        make_pair<vector<int>, vector<int>>(
            {1, 2, 3},
            {1, 4, 9}
        ),
        make_pair<vector<int>, vector<int>>(
            {8, 3, 6, 1, 4, 7, 10, 14, 13},
            {8, 10, 14, 3, 6, 4, 1, 7, 13}
        ),
    };

    for (const auto& p : inputs)
    {
        const auto& a = p.first;
        const auto& b = p.second;
        if (a.empty() || b.empty())
        {
            continue;
        }
        cout << "For the inputs:" << endl;
        for (auto i : a)
        {
            cout << i << " ";
        }
        cout << " and " << endl;
        for (auto i : b)
        {
            cout << i << " ";
        }
        cout << endl;

        if (areIdentical(a, b))
        {
            cout << "The binary search trees would be identical";
        }
        else
        {
            cout << "The binary search trees would not be identical";
        }
        cout << endl << endl;
    }
    return 0;
}