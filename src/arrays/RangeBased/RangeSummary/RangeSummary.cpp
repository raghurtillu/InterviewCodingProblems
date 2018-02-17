#include <iostream>
#include <vector>
#include <utility>
#include <initializer_list>
using namespace std;

// https://leetcode.com/problems/summary-ranges/
// Given a sorted integer array without duplicates, return the summary of its ranges.
// For example, given [0, 1, 2, 4, 5, 7], return [(0 - 2), (4 - 5), (7 - 7)]

vector<pair<int, int>> GetSummaryOfRanges(const vector<int>& input)
{
    if (input.empty())
    {
        return {};
    }
    else if (input.size() == 1)
    {
        return {{input[0], input[0]}};
    }
    
    vector<pair<int, int>> ranges;
    size_t start = 0;
    for (size_t i = 0; i < input.size() - 1; ++i)
    {
        if (input[i] == input[i + 1])
        {
            // skip dups
            continue;
        }
        else if (input[i] + 1 != input[i + 1])
        {
            // end of previous range; begin a new range starting from this node
            ranges.push_back({input[start], input[i]});
            start = i + 1;
        }
    }
    // handle corner case for range starting at last element
    if (input[input.size() - 2] + 1 != input[input.size() - 1])
    {
        start = input.size() - 1;
    }
    ranges.push_back({input[start], input[input.size() - 1]});
    return ranges;
}

int main()
{
    vector<vector<int>> values = 
    {
        { 0, 1, 2, 4, 5, 7 },
    };

    for (const auto& inputs : values)
    {
        cout << "For the inputs: ";
        for (auto i : inputs)
        {
            cout << i << " ";
        }
        cout << endl;
        
        cout << "the range(s) summary are: ";
        vector<pair<int, int>> ranges = GetSummaryOfRanges(inputs);
        if (ranges.empty()) { cout << "None" << endl; continue; }
        cout << "[";
        for (size_t i = 0; i < ranges.size(); ++i)
        {
            cout << "(" << ranges[i].first << " - " << ranges[i].second << ")";
            if (i != ranges.size() - 1)
            {
                cout << ", ";
            }
        }
        cout << "]";
        cout << endl;
    }
    return 0;
}
