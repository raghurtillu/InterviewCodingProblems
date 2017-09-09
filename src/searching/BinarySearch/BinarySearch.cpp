#include <iostream>
#include <utility>
#include <vector>

using namespace std;

// returns index of key in a sorted (and distinct) vector
size_t _BinarySearch(const vector<int>& inputs, size_t low, size_t high, int key)
{
    if (low > high)
    {
        // key not found
        return SIZE_MAX;
    }

    size_t mid = low + ((high - low) >> 1);
    if (inputs[mid] == key)
    {
        // found the key
        return mid;
    }
    else if (inputs[mid] > key)
    {
        // median is greater than key: search in the left side of the input
        return _BinarySearch(inputs, low, mid, key);
    }
    else
    {
        // median is less than key: search in the right side of the input
        return _BinarySearch(inputs, mid+1, high, key);
    }
}

size_t BinarySearch(const vector<int>& inputs, int key)
{
    if (inputs.empty())
    {
        return SIZE_MAX;
    }
    return _BinarySearch(inputs, 0, inputs.size()-1, key);
}

int main() 
{
    vector<pair<vector<int>, int>> inputs = 
    {
        // {input vector, key to search}
        make_pair<vector<int>, int>({1}, 1),
        make_pair<vector<int>, int>({1}, 2),
        make_pair<vector<int>, int>({1, 2}, 2),
        make_pair<vector<int>, int>({1, 2}, 1),
        make_pair<vector<int>, int>({1, 2}, 5),
        make_pair<vector<int>, int>({1, 2, 3}, 1),
        make_pair<vector<int>, int>({1, 2, 3}, 2),
        make_pair<vector<int>, int>({1, 2, 3}, 3),
        make_pair<vector<int>, int>({1, 2, 3}, 4),
        make_pair<vector<int>, int>({1, 2, 3, 4}, 1),
        make_pair<vector<int>, int>({1, 2, 3, 4}, 4),
        make_pair<vector<int>, int>({1, 2, 3, 4, 5}, 5),
        make_pair<vector<int>, int>({1, 2, 3, 4, 5}, 7),
    };
    
    for (const auto keyValPair : inputs)
    {
        const auto values = keyValPair.first;        
        for (auto val : values)
        {
            cout << val << " ";
        }
        cout << ": ";
        size_t index = BinarySearch(values, keyValPair.second);
        if (index == SIZE_MAX)
        {
            cout << "Key " << keyValPair.second << " not found " << endl;
        }
        else
        {
            cout << "Key " << keyValPair.second << " found at position " << index << endl;
        }
    }

    return 0;
}