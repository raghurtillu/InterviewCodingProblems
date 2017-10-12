#include <iostream>
#include <limits>
#include <vector>
using namespace std;

int FindMaxInBitonicArray(const vector<int>& a, size_t low, size_t high)
{
    if (a.empty() || low > high || high - low > a.size() || low >= a.size())
    {
        return INT_MIN;
    }
    else if (low == high)
    {
        // one element
        return a[low];
    }
    else if (low == high - 1)
    {
        // two elements
        return a[low] >= a[high] ? a[low] : a[high];
    }

    // three or more elements
    auto mid = low + ((high - low) >> 1);
    if (a[mid-1] < a[mid] && a[mid] < a[mid+1])
    {
        return FindMaxInBitonicArray(a, mid+1, high);
    }
    else if (a[mid-1] > a[mid] && a[mid] > a[mid+1])
    {
        return FindMaxInBitonicArray(a, low, mid);
    }
    else
    {
        if (a[mid-1] > a[mid] && a[mid] < a[mid+1])
        {
            return a[mid-1] >= a[mid+1] ? a[mid-1] : a[mid+1];
        }
        else if (a[mid-1] < a[mid] && a[mid] > a[mid+1])
        {
            return a[mid];
        }
        return a[mid];
    }
}

int main()
{
    vector<vector<int>> inputs = {
        {8, 10, 20, 80, 100, 200, 400, 500, 3, 2, 1},
        {1, 3, 50, 10, 9, 7, 6},
        {10, 20, 30, 40, 50},
        {120, 100, 80, 20, 0},
    };

    for (const auto& input : inputs)
    {
        if (input.empty()) { continue; }

        cout << "For the inputs: " << endl;
        for (auto i : input)
        {
            cout << i << " ";
        }

        int max = FindMaxInBitonicArray(input, 0, input.size()-1);
        cout << "the max element is " << max << endl;
        cout << endl;
    }
    return 0;
}