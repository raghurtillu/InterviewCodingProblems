#include <iostream>
#include <vector>

using namespace std;
// Given an array of integers, count number of subarrays that are strictly increasing
// Input: arr[] = {1, 4, 3}
// Output: {1, 4}
//
// Input: arr[] = {1, 2, 3, 4}
// Output: {1, 2}, {1, 2, 3}, {1, 2, 3, 4}, {2, 3}, {2, 3, 4} and {3, 4}
//
// Input: arr[] = {1, 2, 2, 4}
// Output: {1, 2}, {2, 4}
size_t CountStrictlyIncreasingSubarrays(const vector<int>& input)
{
    if (input.size() <= 1)
    { return input.size(); }

    size_t count = 0, len = 1;
    for (size_t i = 0; i < input.size() - 1; ++i)
    {
        if (input[i+1] > input[i])
        {
            // if input[i+1] is greater than input[i], then increment length
            ++len;
        }
        else
        {
            // else Update count and reset length
            count += ((len-1) * (len)) >> 1; // len * (len - 1) / 2;
            len = 1;
        }
    }
    count += ((len-1) * (len)) >> 1; // len * (len - 1) / 2;
    return count;
}

int main()
{
    vector<vector<int>> inputs = 
    {
        {3},
        {1, 4, 3},
        {1, 2, 3, 4},
        {1, 2, 2, 4},
    };

    cout << "Number of subarrays that are strictly increasing for the inputs: " << endl;
    for (const auto& input : inputs)
    {
        for (size_t i = 0; i < input.size(); ++i)
        {
            if (i == 0) { cout << "{" << input[i]; }
            else if (i > 0 && i < input.size() - 1) { cout << ", " << input[i]; }
            else
            {
                if (input.size() > 1) { cout << ", " << input[i]; }
                cout << "}";
            }            
        }
        cout << ": " << CountStrictlyIncreasingSubarrays(input) << endl;
    }
}