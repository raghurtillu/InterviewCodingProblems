#include <iostream>
#include <vector>
#include <utility>
using namespace std;

// Given an unsorted array of integers, find an element such that all the 
// elements to its left are smaller and to its right are greater

// Input :  A[] = {4, 3, 2, 5, 8, 6, 7}  
// Output : 5
//
// Input : A[] = {5, 6, 2, 8, 10, 9, 7} 
// Output : -1

size_t Partition(const vector<int>& inputs)
{
    if (inputs.empty())
    {
        return SIZE_MAX;
    }
    else if (inputs.size() == 1)
    {
        return 0;
    }

    vector<int> left(inputs.size());

    // store greatest element on the left side
    left[0] = inputs[0];
    for (size_t i = 1; i < inputs.size(); ++i)
    {
        left[i] = max(left[i - 1], inputs[i]);
    }

    // store smallest element on the right side
    vector<int> right(inputs.size());
    right[inputs.size() - 1] = inputs[inputs.size() - 1];
    for (size_t i = inputs.size() - 2; i != SIZE_MAX; --i)
    {
        right[i] = min(right[i + 1], inputs[i]);
    }

    // Now find a number which is greater then all elements to its left 
    // and smaller than all elements to its right
    size_t n = inputs.size();
    for (size_t i = 0; i < n; ++i)
    {
        if ((i == 0 && inputs[i] < right[i + 1]) ||
            (i == n - 1 && inputs[n - 1] > left[n - 2]) ||
            (inputs[i] >= left[i - 1] && inputs[i] <= right[i + 1]))
        {
            return i;
        }
    }
    return SIZE_MAX;
}

int main()
{
    vector<vector<int>> values = 
    {
        {4, 3, 2, 5, 8, 6, 7},
        {1, 2, 3, 4},
        {5, 6, 2, 8, 10, 9, 11},
    };

    for (const auto& inputs : values)
    {
        cout << "For the inputs: ";
        for (auto i : inputs)
        {
            cout << i << " ";
        }
        cout << endl;
        size_t index =  Partition(inputs);
        if (index == SIZE_MAX)
        {
            cout << "the partition element does not exist";
        }
        else
        {
            cout << "the partition element is: " << inputs[index];
        }
        cout << endl;
    }
    return 0;
}