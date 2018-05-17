#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Given an array of both positive and negative numbers, the task is to find out 
// the subarray whose sum is closest to 0.
//
// Input : arr[] = {-1, 3, 2, -5, 4}
// Output : 1, 3
// Subarray from index 1 to 3 has sum closest to 0 i.e.
// 3 + 2 + -5 = 0
//
// Input : {2, -5, 4, -6, 3} 
// Output : 0, 2
// 2 + -5 + 4 = 1 closest to 0
struct PrefixInfo
{
    int sum = 0;
    int index = 0;
};

pair<size_t, size_t> getSubArray(const vector<int>& input)
{
    if (input.empty()) { return {}; }
    else if (input.size() == 1) { return {0, 0}; }
    vector<PrefixInfo> prefix(input.size() + 1);

    prefix[0].sum = 0;
    prefix[0].index = -1;

    for (size_t i = 1; i <= input.size(); ++i)
    {
        prefix[i].sum = prefix[i-1].sum + input[i-1];
        prefix[i].index = i-1;
    }
    sort(prefix.begin(), prefix.end(), [](const PrefixInfo& lhs, const PrefixInfo& rhs)
    {
        return lhs.sum < rhs.sum;
    });

    int minDiff = INT_MAX;
    pair<size_t, size_t> minPair;
    for (size_t i = 0; i < input.size(); ++i)
    {
        auto diff = prefix[i+1].sum - prefix[i].sum;
        if (abs(diff) < abs(minDiff))
        {
            minDiff = diff;
            minPair = {prefix[i].index+1, prefix[i+1].index};
        }
    }
    return minPair;
}

int main()
{
    vector<vector<int>> inputs = 
    {
        {2, 3, -4, 9, 1, 7, -5, 6, 5},
        {2, 3, -4, -1, 6},
        {-1, 2, -3, 4, 0, 5, -6, 7, -10, 11},
        {5, 3, 1},
        {1, 2, 3, 4, 0, -4, -3, -2, -1},
        {-1, 3, 2, -5, 4},
        {2, -5, 4, -6, 3},
    };

    cout << "For the following inputs, the subarray indices whose sum is closest to zero are:" << endl;
    for (const auto& input : inputs)
    {
        for (size_t i = 0; i < input.size(); ++i)
        {
            cout << input[i];
            if (i != input.size() - 1)
            {
                cout << ", ";
            }
        }
        cout << ": ";
        pair<size_t, size_t> minPair = getSubArray(input);
        cout << "{" << minPair.first << ", " << minPair.second << "}" << endl;
    }
    return 0;
}
