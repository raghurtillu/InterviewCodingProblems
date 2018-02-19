#include <iostream>
#include <vector>
#include <utility>
using namespace std;

// Minimum number of swaps required to sort an array
// Input : {4, 3, 2, 1}
// Output : 2
// Explanation : Swap index 0 with 3 and 1 with 2 to form the sorted array {1, 2, 3, 4}
//
// Graph below depicts edge directed from node i to node j if the element at 
// i'th index must be present in the j'th index in the sorted array
//     _______________
//   /                \
//   4     3     2     1
//         \    /
//          ----
// 
// Input : {4, 5, 2, 1, 5}
// Output : 3
//
//                ________
//   _____  _____/____    \
//  /     \/    /     \    \
//  2     4     5     1     3   
//  \____________\____/    /
//                \_______/  
//

size_t MinimumSwaps(const vector<int>& input)
{
    if (input.size() <= 1)
    {
        return 0;
    }

    struct ArrPos
    {
        int val = 0;
        size_t index = 0;

        ArrPos(int _val, size_t _index) : val(_val), index(_index)
        {}
    };

    vector<ArrPos> values;
    for (size_t i = 0; i < input.size(); ++i)
    {
        values.push_back(ArrPos(input[i], i));
    }

    sort(values.begin(), values.end(), [](const ArrPos& a, const ArrPos& b)
    {
        return a.val < b.val;
    });

    vector<bool> visited(values.size(), false);
    size_t swapsCount = 0;

    for (size_t i = 0; i < values.size(); ++i)
    {
        if (visited[i] || values[i].index == i)
        {
            continue;
        }

        size_t cycleSize = 0;
        size_t j = values[i].index;

        while (!visited[j])
        {
            visited[j] = true;
            j = values[j].index;
            ++cycleSize;
        }
        swapsCount += (cycleSize > 0) ? cycleSize - 1 : 0;
    }
    return swapsCount;
}

int main()
{
    vector<vector<int>> inputs
    {
        {4, 3, 2, 1},
        {4, 5, 2, 1, 5},
        {1, 2, 3, 4},
    };

    for (const auto& input : inputs)
    {
        cout << "For the inputs: ";
        for (auto i : input)
        {
            cout << i << " ";
        }
        cout << endl;
        cout << "the minimum number of swaps to sort the array is: " << MinimumSwaps(input);
        cout << endl;
    }
    return 0;
}