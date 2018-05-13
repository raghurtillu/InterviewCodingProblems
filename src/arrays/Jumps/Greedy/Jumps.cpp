#include <iostream>
#include <vector>
using namespace std;

// Given an array of positive integers, find the minimum number of jumps to reach the end the array
// Input: arr[] = {1, 4, 3, 7, 1, 2, 6, 7, 6, 10}
// Output: 3, (1, 4, 7)
// Time complexity: O(n)

size_t MinJumps(const vector<int>& arr)
{
    if (arr.empty()) { return 0; }

    int ladder = arr[0]; // keep track of the largest ladder
    int stairs = arr[0]; // keep track of stairs in the current ladder
    size_t jumps = 1;
    for (size_t level = 1; level < arr.size(); ++level)
    {
        if (level == arr.size() - 1)
        { 
            // reached the end; done
            break;
        }
        if (level + arr[level] > ladder)
        {
            // build the ladder
            ladder = level + arr[level];
        }
        --stairs; // use the stairs
        if (stairs == 0)
        {
            ++jumps; // no stairs left; now jump
            stairs = ladder - level; // now get new set of stairs
        }
    }
    return jumps;
}

int main()
{
    vector<vector<int>> inputs = 
    {
        {1},
        {1, 2},
        {3, 1},
        {1, 4, 3, 7, 1, 2, 6, 7, 6, 10},
        {2, 3, 1, 1, 4},
        {1, 3, 5, 8, 9, 2, 6, 7, 6, 8, 9},
    };

    cout << "Minimum jumps for the following inputs: " << endl;
    for (const auto& input : inputs)
    {
        for (auto i : input)
        {
            cout << i << " ";
        }
        cout << ": " << MinJumps(input) << endl;
    }
    return 0;
}
