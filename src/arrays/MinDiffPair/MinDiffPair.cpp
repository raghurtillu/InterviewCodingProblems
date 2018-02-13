#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

// Smallest difference pair of values between two unsorted arrays

// Input : A[] = {l, 3, 15, 11, 2}
//         B[] = {23, 127, 235, 19, 8} 
// Output : 3, (11, 8)
// Input : A[] = {l0, 5, 40}
//         B[] = {50, 90, 80} 
// Output : 10, (40, 50)

pair<int, int> MinDiffPair(vector<int> arr1, vector<int> arr2)
{
    if (arr1.empty() || arr2.empty())
    {
        return {};
    }

    sort(arr1.begin(), arr1.end());
    sort(arr2.begin(), arr2.end());

    int minDiff = INT_MAX;
    pair<int, int> result;
    
    for (size_t p1 = 0, p2 = 0; p1 < arr1.size() && p2 < arr2.size(); )
    {
        auto diff = abs(arr1[p1] - arr2[p2]);
        if (diff < minDiff)
        {
            result = {arr1[p1], arr2[p2]};
            minDiff = diff;
        }
        if (arr1[p1] < arr2[p2])
        {
            ++p1;
        }
        else
        {
            ++p2;
        }
    }
    return result;
}

int main()
{
    vector<pair<vector<int>, vector<int>>> inputs = 
    {
        make_pair<vector<int>, vector<int>>(
            {1, 3, 15, 11, 2},
            {23, 127, 235, 19, 8}),
        make_pair<vector<int>, vector<int>>(
            {0, 3, 5, 6, 20},
            {-10, -3, -5, -6, -20}),
    };

    for (const auto& p : inputs)
    {
        const auto& arr1 = p.first;
        cout << "For the inputs: " << endl;
        for (auto i : arr1)
        {
            cout << i << " ";
        }
        cout << "and ";
        const auto& arr2 = p.second;
        for (auto i : arr2)
        {
            cout << i << " ";
        }
        cout << endl;
        pair<int, int> res = MinDiffPair(arr1, arr2);
        cout << "The closest pair is: (" << res.first << ", " << res.second << ")" << endl;
    }
    return 0;
}