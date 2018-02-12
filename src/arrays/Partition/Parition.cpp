#include <iostream>
#include <vector>
#include <utility>
using namespace std;

// Given an unsorted array of integers, find an element such that all the 
// elements to its left are smaller and to its right are greater

// Input :  A[] = {4, 3, 2, 5, 8, 6, 7}  
// Output : 5
//
// Input : A[] = {5, 6, 2, 8, 10, 9, 8} 
// Output : -1

size_t Partition(const vector<int>& inputs)
{
    if (inputs.empty())
    {
        return -1;
    }

    vector<int> smaller(inputs.size()), greater(inputs.size());
    
    smaller[0] = inputs[0];
    for (size_t i = 1; i < inputs.size(); ++i)
    {
        smaller[i] = min(inputs[i], smaller[i-1]);
    }

    greater[inputs.size()-1] = inputs[inputs.size()-1];
    for (size_t i = inputs.size() - 2; i != SIZE_MAX; --i)
    {
        greater[i] = max(inputs[i], greater[i-1]);
    }

    for (size_t i = 0; i < inputs.size(); ++i)
    {
        if ((i == 0 && inputs[i] < smaller[i+1]) ||
            (i == inputs.size() - 1 && inputs[i] > greater[i-1]) ||
            (i-1 != SIZE_MAX && i+1 != SIZE_MAX && inputs[i] >= smaller[i-1] && inputs[i] <= greater[i+1]))
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

}