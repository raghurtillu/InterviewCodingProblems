#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

// Input: arr[] = {1, 0, 1, 1, 1, 0, 0}
// Output: 1 to 6 (Starting and Ending indexes of output subarray)

// Input: arr[] = {1, 1, 1, 1}
// Output: No such subarray

// Input: arr[] = {0, 0, 1, 1, 0}
// Output: 0 to 3 Or 1 to 4

struct Pos
{
    size_t index = 0;
    size_t len = 0;

    Pos() = default;
    Pos (size_t _index, size_t _len) : index(_index), len(_len)
    {}
};

void PrintValues(const vector<int>& inputs, const Pos& res)
{
    if (inputs.empty() || res.index >= inputs.size() || res.index + res.len >= inputs.size()) 
    {
        return;
    }
    
    size_t start = res.index;
    size_t end = (res.len > 0) ? (res.index + res.len) : res.index;
    
    cout << "{ ";
    for (size_t i = 0; i < inputs.size(); ++i) 
    {
        if (i == start && res.len != 0)
        {
            cout << "[ ";
        }
        cout << inputs[i];
        if (i == end && res.len != 0)
        {
            cout << " ]";
        }
        if (i < inputs.size() - 1)
        {
            cout << ", ";
        }
    }
    cout << " }";
}

Pos FindLargestSubarrayEqual0sAnd1s(const vector<int>& inputs)
{
    if (inputs.empty())
    {
        return Pos();
    }

    size_t startIndex = 0;
    int sum = 0;
    Pos res;
    unordered_map<int, Pos> lookup;

    for (size_t i = 0; i < inputs.size(); ++i)
    {
        sum += inputs[i] == 0 ? -1 : inputs[i];
        if (sum == 0)
        {
            if (res.len < i)
            {
                res.len = i;
                res.index = 0;
            }
        }
        else if (lookup.find(sum) != lookup.cend())
        {   
            // if we have seen the sum before then we have a sub array of equal number of 0's and 1's,
            // starting from the next index of prior value of sum
            if (res.len < i - lookup[sum].index)
            {
                res.len = i - lookup[sum].index;
                res.index = lookup[sum].index;
            }
        }
        else
        {
            startIndex += 1;
            Pos p(startIndex, i - startIndex);
            lookup[sum] = p;
        }
    }
    return res;
}

int main()
{
    vector<vector<int>>inputs = 
    { 
        {1, 1, 1, 1, 1, 1, 0, 1, 1, 1},
        {1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1},
        {1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1},
        {1, 0, 1, 1, 1, 0, 0},
        {1, 1, 1, 1},
        {0, 0, 1, 1, 0},
        {1, 0, 1, 0, 0, 1, 0, 0, 0},
        {0, 1, 1, 0, 0, 1},
    };
	
    cout << "For the following arrays, the largest subarray of equal 0s and 1s are as follows: " << endl;
    for (const auto& input : inputs)
    {
        Pos res = FindLargestSubarrayEqual0sAnd1s(input);
        PrintValues(input, res);
        cout << " " << res.index << " to " << res.index + res.len << " (" << res.len << ")" << endl;
	}
    return 0;
}