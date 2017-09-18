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
    while (zeroIndex <= oneIndex)
    {
        if (arr[zeroIndex] == 1)
        {
            swap(arr[zeroIndex], arr[oneIndex]);
            zeroIndex++;
            oneIndex--;
        }
    }
}

int main()
{
    vector<vector<int>> values = 
    {
        {1, 1, 1, 0, 0, 0},
        // {1, 2, 3, 4},
        // {4, 5, 2, 3},
        // {2, 1},
    };

    for (auto inputs : values)
    {
        cout << "For the inputs: ";
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
