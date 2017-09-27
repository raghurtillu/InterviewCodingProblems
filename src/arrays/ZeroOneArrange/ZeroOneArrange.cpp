#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

void reArrange(vector<int>& arr)
{
    if (arr.empty())
    {
        return;
    }

    size_t zeroIndex = 0, oneIndex = arr.size()-1;
    while (zeroIndex <= oneIndex && oneIndex != SIZE_MAX)
    {
        if (arr[zeroIndex] == 1)
        {
            swap(arr[zeroIndex], arr[oneIndex]);
            --oneIndex;
        }
        else if (arr[zeroIndex] == 0)
        {
            ++zeroIndex;
        }
    }
}

int main()
{
    vector<vector<int>> values = 
    {
        {1, 1, 1, 0, 0, 0},
        {0, 0, 0},
        {1, 1, 1, 1},
        {0, 1, 1, 0, 1, 1, 0},
        {1, 1, 1, 1, 0, 0, 1},
        // {4, 5, 2, 3},
        // {2, 1},
    };

    for (auto inputs : values)
    {
        cout << endl;
        for (auto i : inputs)
        {
            cout << i << " ";
        }
        cout << endl;
        cout << "after rearranging " << endl;

        reArrange(inputs);

        for (auto i : inputs)
        {
            cout << i << " ";
        }
        cout << endl;
    }
    
    return 0;
}
