#include <iostream>
#include <vector>
#include <utility>
#include <initializer_list>
using namespace std;

// Given two sorted arrays and a number x, find the pair
// whose sum is closest to x and the pair has an element from each array

// Input:  ar1[] = {1, 4, 5, 7};
//         ar2[] = {10, 20, 30, 40};
//         x = 32      
// Output:  1 and 30

// Input:  ar1[] = {1, 4, 5, 7};
//         ar2[] = {10, 20, 30, 40};
//         x = 50      
// Output:  7 and 40

pair<int, int> ClosestPair(const vector<int>& arr1, const vector<int>& arr2, int target)
{
    if (arr1.empty() || arr2.empty())
    {
        return {};
    }

    int minDiff = INT_MAX;
    size_t l = 0, r = arr2.size() - 1;
    pair<int, int> result;

    while (l < arr1.size() && r != SIZE_MAX)
    {
        auto diff = abs(arr1[l] + arr2[r] - target);
        if (diff < minDiff)
        {
            result = {arr1[l], arr2[r]};
            minDiff = diff;
        }
        if (arr1[l] + arr2[r] > target)
        {
            --r;
        }
        else if (arr1[l] + arr2[r] < target)
        {
            ++l;
        }
    }
    return result;
}

int main()
{
    struct Inputs
    {
        vector<int> arr1;
        vector<int> arr2;
        int target = 0;

        Inputs(const vector<int>& _arr1, const vector<int>& _arr2, int _target) : 
            arr1(_arr1), arr2(_arr2), target(_target)
        {

        }
        Inputs(const initializer_list<int>& _il1, const initializer_list<int>& _il2, int _target) : 
            arr1(_il1), arr2(_il2), target(_target)
        {

        }
    };

    vector<Inputs> values = 
    {
        Inputs({1, 4, 5, 7}, {10, 20, 30, 40}, 32),
        Inputs({1, 4, 5, 7}, {10, 20, 30, 40}, 50),
    };

    for (const auto& value : values)
    {
        cout << "For the inputs ";
        for (auto val : value.arr1)
        {
            cout << val << " ";
        }
        cout << "and ";
        for (auto val : value.arr2)
        {
            cout << val << " ";
        }
        cout << "and target as " << value.target << endl;
        pair<int, int> res = ClosestPair(value.arr1, value.arr2, value.target);
        cout << "The closest pair is: (" << res.first << ", " << res.second << ")" << endl;
    }
    return 0;
}