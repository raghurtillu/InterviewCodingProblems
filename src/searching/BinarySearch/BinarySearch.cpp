#include <iostream>
#include <utility>
#include <vector>

using namespace std;

// returns index of key in a sorted (and distinct) vector
size_t _BinarySearchIterative(const vector<int>& inputs, int key)
{
    size_t low = 0, high = inputs.size() - 1;
    while (true)
    {
        if (low > high)
        {
            return SIZE_MAX;
        }
        size_t mid = (low + high) >> 1;
        if (inputs[mid] == key)
        {
            return mid;
        }
        else if (inputs[mid] > key)
        {
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }
    return SIZE_MAX;
}

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
        return _BinarySearch(inputs, low, mid-1, key);
    }
    else
    {
        // median is less than key: search in the right side of the input
        return _BinarySearch(inputs, mid+1, high, key);
    }
}

bool BinarySearch(const vector<int>& inputs, int key)
{
    if (inputs.empty())
    {
        return false;
    }

    return _BinarySearchIterative(inputs, key) == SIZE_MAX ? false : true;
    //return _BinarySearch(inputs, 0, inputs.size()-1, key) == SIZE_MAX ? false : true;
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
        if (BinarySearch(values, keyValPair.second))
        {
            cout << "Key " << keyValPair.second << " found" << endl;
        }
        else
        {
            cout << "Key " << keyValPair.second << " not found " << endl;
        }
    }

    return 0;
}