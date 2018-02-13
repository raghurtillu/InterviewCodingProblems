#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

// Given an array of positive integers find the maximum possible value K such that the array has at least K elements that are greater than or equal to K
// The array is unsorted and may contain duplicate values
//
// Input: [2, 3, 4, 5, 6, 7]
// Output: 4
// Explanation : 4 elements [4, 5, 6, 7] are greater than equal to 4

// Input: [1, 2, 3, 4]
// Output: 3
// Explanation : 3 elements [2, 3, 4] are greater than equal to 2

// Input: [4, 7, 2, 3, 8]
// Output: 4 
// Explanation : 4 elements [4, 7, 3, 8] are greater than equal to 3
 
// Input: [6, 7, 9, 8, 10]
// Output: 5
// Explanation : All 5 elements are greater than equal to 5 

// this has o(nlogn) time complexity
size_t MaxValue(vector<int> inputs)
{
    if (inputs.size() <= 1)
    {
        return inputs.size();
    }

    sort(inputs.begin(), inputs.end());
    int maxDiff = 0;    
    for (size_t i = inputs.size() - 1; i != SIZE_MAX; --i)
    {
        maxDiff = max(maxDiff, min(inputs[i], static_cast<int>(inputs.size() - i)));
    }
    return maxDiff;
}

// this has o(n) time complexity
size_t MaxValueOpt(const vector<int>& inputs)
{
    // We process all input elements
    //  a) If an element arr[i] is less than n, then we increment its frequency, i.e., we do freq[arr[i]]++.
    //  b) Else we increment freq[n]
    // After above we have two things.
    //  a) Frequencies of elements for elements smaller than n stored in freq[0..n-1]
    //  b) Count of elements greater than n stored in freq[n]
    vector<int> freq(inputs.size() + 1);
    for (size_t i = 0; i < inputs.size(); ++i)
    {
        if (inputs[i] < inputs.size())
        {
            freq[inputs[i]]++;
        }
        else
        {
            freq[inputs.size()]++;
        }
    }

    // sum stores number of elements in input array that are greater than or equal to current index
    auto sum = 0;
    for (size_t i = inputs.size(); i != SIZE_MAX; --i)
    {
        sum += freq[i];
        // if sum is greater than current index, then current index is the answer
        if (sum >= i)
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
        {5, 2, 6, 3, 4, 7},
        {3, 1, 2},
        {4, 7, 2, 3, 8},
    };

    for (const auto& inputs : values)
    {
        cout << "For the inputs: ";
        for (auto i : inputs)
        {
            cout << i << " ";
        }
        cout << endl;
        auto val = MaxValueOpt(inputs);
        cout << "there are " << val << " elements which are greater than or equal to " << val << endl;
    }
}