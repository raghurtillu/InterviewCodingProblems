#include <iostream>
#include <vector>
using namespace std;

// Given a storted array, determine wheter an element exists in the array from where number of smaller elements is equal to number of greater elements
// Input  : arr[] = {1, 2, 3, 3, 3, 3}
// Output : 1
// Equal Point is arr[1] which is 2. Number of elements smaller than 2 and greater than 2 are same
// Input : arr[] = {1, 2, 3, 4, 4, 5, 6, 6, 6, 7}
// Output : 3
// First occurrence of equal point is arr[3]

size_t FindEqualPointElement(const vector<int>& inputs)
{
    if (inputs.empty())
    {
        return SIZE_MAX;
    }

    // find distinct elements
    vector<int> distinct;
    for (size_t i = 0; i < inputs.size();)
    {
        distinct.push_back(inputs[i++]);
        while (i < inputs.size() && inputs[i] == inputs[i-1])
        {
            // skip duplicates
            i++;
        }
    }
    // if the number of distinct elements is odd, equal point exists else it does not
    return distinct.size() & 1 ? distinct.size() >> 1 : SIZE_MAX;
}

int main()
{
    vector<vector<int>> values = 
    {
        {1},
        {1, 2, 2},
        {1, 2, 3, 3, 3, 3},
        {1, 2, 3, 3, 3, 3, 4, 4},
        {1, 2, 3, 4, 4, 5, 6, 6, 6, 7},
    };

    for (const auto& inputs : values)
    {
        cout << "For the inputs: ";
        for (auto i : inputs)
        {
            cout << i << " ";
        }
        cout << endl;
        auto index = FindEqualPointElement(inputs);
        if (index != SIZE_MAX)
        {
            cout << "equal point element is: " << inputs[index];
        }
        else
        {
            cout << "equal point does not exist";
        }
        cout << endl;
    }
}