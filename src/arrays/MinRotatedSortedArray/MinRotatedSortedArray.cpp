#include <iostream>
#include <vector>
using namespace std;

size_t _findMinimum(const vector<int>& inputs, size_t low, size_t high)
{
    if (low == high || inputs[low] < inputs[high])
    {
        return low;
    }

    auto mid = (low + high) >> 1;
    if (inputs[low] > inputs[mid])
    {
        return _findMinimum(inputs, low, mid);
    }
    else
    {
        return _findMinimum(inputs, mid + 1, high);
    }
}

int findMinimum(const vector<int>& inputs)
{
    if (inputs.empty())
    {
        return 0;
    }

    size_t low = 0, high = inputs.size() - 1;
    size_t index = _findMinimum(inputs, low, high);
    if (index == SIZE_MAX)
    {
        return -1;
    }
    else
    {
        return inputs[index];
    }
}

int main()
{
    vector<vector<int>> values = 
    {
        {5, 6, 1, 2, 3, 4},
        {1, 2, 3, 4},
        {4, 5, 2, 3},
        {2, 1},
    };

    for (auto inputs : values)
    {
        cout << "For the inputs: ";
        for (auto i : inputs)
        {
            cout << i << " ";
        }
        cout << endl;
        int val = findMinimum(inputs);        
        cout << "min element is: " << val << endl;
    }
    
    return 0;
}
