#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

// given all positive numbers in an array find out minimum number of jumps to reach end of an array
// for e.g. {1, 4, 3, 7, 1, 2, 6, 7, 7, 10} minimum jumps is 3 i.e., 1->4->7->end of array
// https://www.geeksforgeeks.org/minimum-number-of-jumps-to-reach-end-of-a-given-array/

int MinJumps(const vector<int>& arr, size_t startIndex, unordered_map<size_t, int>& lookup)
{
    if (startIndex >= arr.size())
    {
        return 0;
    }
    else if (lookup.find(startIndex) != lookup.cend())
    {
        return lookup[startIndex];
    }

    int minJumps = INT_MAX;
    for (int steps = 1; steps <= arr[startIndex]; ++steps)
    {
        auto jumps = 1 + MinJumps(arr, startIndex + steps, lookup);
        minJumps = min(minJumps, jumps);
    }

    lookup[startIndex] = minJumps;
    return minJumps;
}

int MinJumps(const vector<int>& arr)
{
    if (arr.empty()) { return 0; }
    
    size_t startIndex = 0;
    unordered_map<size_t, int> lookup;
    return MinJumps(arr, startIndex, lookup);
}

int main()
{
    vector<vector<int>> inputs = 
    {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 2, 3, 4},
        {1, 4, 3, 1},
        {1, 4, 3, 7, 1, 2, 6, 7, 6, 10},
        {1, 3, 5, 8, 9, 2, 6, 7, 6, 8, 9}
    };

    cout << "Minimum jumps for array: " << endl;
    for (const auto& arr : inputs) 
    {
        for (size_t i = 0; i < arr.size(); ++i)
		{
			if (i == 0) { cout << "{"; }
            cout << arr[i];
            if (i != arr.size() - 1) { cout << ", "; }
            else { cout << "}"; }
		}
        
        int minJumps = MinJumps(arr);
        cout << " -> " << minJumps << endl;
    }
}