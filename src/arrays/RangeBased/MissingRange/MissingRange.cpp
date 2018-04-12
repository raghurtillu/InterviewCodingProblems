#include <iostream>
#include <vector>
#include <utility>
#include <initializer_list>
using namespace std;

// https://leetcode.com/problems/missing-ranges/
// Given a sorted integer array where the range of elements are in the inclusive range [lower, upper], return its missing ranges.
// For example, given [0, 1, 3, 50, 75], lower = 0 and upper = 99, return [(2 - 2), (4 - 49), (51 - 74), (75 - 99)]
// Time complexity O(n)

vector<pair<int, int>> GetMissingRanges(const vector<int>& values, int low, int high)
{
    if (values.empty() || low > high)
    {
        return {};
    }

    vector<pair<int, int>> missingRange;
    if (low < values[0])
    {
        missingRange.push_back({low, values[0]-1});
    }
    for (size_t i = 0; i < values.size() - 1; ++i)
    {
        if (values[i] == values[i+1])
        {
            // skip dups
            continue;
        }
        else if (values[i] + 1 != values[i + 1])
        {
            // missing range
            missingRange.push_back({values[i] + 1, values[i + 1] - 1});
        }
    }
    if (high > values[values.size() - 1])
    {
        missingRange.push_back({values[values.size() - 1] + 1, high});
    }
    return missingRange;
}

int main()
{
    struct Input
    {
        vector<int> val;
        int low;
        int high;
        Input(const initializer_list<int>& il, int _low, int _high) : val(il), low(_low), high(_high)
        {
            if (low > high)
            {
                throw invalid_argument("low " + to_string(low) + " must be lower than " + to_string(high));
            }
        }
    };

    vector<Input> inputs = 
    {
        // Input({array of values}, range low, range high)
        Input({0, 1, 3, 50, 75}, 0, 99),
    };
    
    for (const auto& ip : inputs)
    {
        cout << "For the range: " << ip.low << ", " << ip.high << " and the inputs: ";
        for (size_t i = 0; i < ip.val.size(); ++i)
        {
            cout << ip.val[i] << " ";
        }
        cout << endl;

        cout << "the missing range(s) are: ";
        vector<pair<int, int>> missingRange = GetMissingRanges(ip.val, ip.low, ip.high);
        if (missingRange.empty()) { cout << "None" << endl; continue; }
        cout << "[";
        for (size_t i = 0; i < missingRange.size(); ++i)
        {
            cout << "(" << missingRange[i].first << " - " << missingRange[i].second << ")";
            if (i != missingRange.size() - 1)
            {
                cout << ", ";
            }
        }
        cout << "]";
        cout << endl;
    }
    return 0;
}