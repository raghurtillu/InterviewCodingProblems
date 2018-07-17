#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

// https://www.geeksforgeeks.org/largest-divisible-subset-array/
// Given an array the task is to largest divisible subset in array. 
// A subset is called divisible if for every pair (x, y) in subset, either x divides y or y divides x
// Input  : arr[] = {1, 16, 7, 8, 4}
// Output : 16 8 4 1
// Input  : arr[] = {2, 4, 3, 8}
// Output : 8 4 2

vector<int> MaxDivisibleSubset(vector<int> arr)
{
    if (arr.size() <= 1) { return arr; }
    
    sort(arr.begin(), arr.end());
    unordered_map<int, int> divisors, parent;
    // populate the divisors and parent
    for (auto val : arr)
    {
        divisors[val] = 1;
        parent[val] = val;
    }

    int maxDivisor = arr[0];
    for (size_t i = 1; i < arr.size(); ++i)
    {
        for (size_t j = 0; j < i; ++j)
        {
            if (arr[j] == 0) { continue; }              // dividend cannot be zero
            else if (arr[i] == arr[j]) { continue; }    // divisor and dividend are the same
            else if (arr[i] % arr[j] == 0)
            {
                if (divisors[arr[i]] < divisors[arr[j]] + 1)
                {
                    divisors[arr[i]] = divisors[arr[j]] + 1;
                    parent[arr[i]] = arr[j];
                }
            }
        }   // end of inner for loop
        if (divisors[maxDivisor] < divisors[arr[i]])
        {
            maxDivisor = arr[i];
        }
    }   // end of outer for loop

    // walk up the parent tree for the maxDivisor and construct the subset
    vector<int> res = { maxDivisor };
    int val = maxDivisor;
    while (true)
    {
        if (parent.find(val) == parent.cend() || parent[val] == val)
        {
            break;
        }
        val = parent[val];
        res.push_back(val);
    }
    return res;
}

int main() 
{
    vector<vector<int>> inputs = 
	{
		{1, 2},
        {1, 2, 3, 4},
        {1, 2, 3, 4, 5, 6, 7, 8, 16},
        {3, 3, 0, 5, 13, 7},
        {1, 16, 7, 8, 4}
	};

	cout << "Maximum divisible subset for the inputs: " << endl;
	for (const auto& arr : inputs)
	{
		for (size_t i = 0; i < arr.size(); ++i)
		{
			if (i == 0) { cout << "{"; }
			cout << arr[i];
			if (i != arr.size() - 1) { cout << ", "; }
			else { cout << "}"; }
		}
        vector<int> res = MaxDivisibleSubset(arr);
        cout << ": ";
        for (size_t i = 0; i < res.size(); ++i)
		{
			if (i == 0) { cout << "{"; }
			cout << res[i];
			if (i != res.size() - 1) { cout << ", "; }
			else { cout << "}"; }
		}
        cout << endl;
	}
    cout << endl;
}