#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
using namespace std;

int GetMedian(const vector<int>& a, size_t low, size_t high)
{
    if (a.empty() || low > high || high - low > a.size() || low >= a.size())
    {
        return INT_MIN;
    }
    auto size = high - low + 1;
    auto mid = low + ((high - low) >> 1);
    if (size & 1)
    {
        // odd size array
        return a[mid];
    }
    else
    {
        // even size array
        return (a[mid] + a[mid+1]) >> 1;
    }
}

bool isValidInput(const vector<int>& a, size_t low1, size_t high1,
    const vector<int>& b, size_t low2, size_t high2)
{
    if (a.empty() || b.empty())
    {
        return false;
    }
    else if (low1 > high1 || high1 - low1 > a.size() || low1 >= a.size())
    {
        return false;
    }
    else if (low2 > high2 || high2 - low2 > a.size() || low2 >= b.size())
    {
        return false;
    }
    else if (high1 - low1 != high2 - low2)
    {
        return false;
    }
    return true;
}

int FindMedian(const vector<int>& a, size_t low1, size_t high1,
    const vector<int>& b, size_t low2, size_t high2)
{
    if (!isValidInput(a, low1, high1, b, low2, high2))
    {
        return INT_MIN;
    }
    else if (high1 - low1 == 0)
    {
        // one element array
        return (a[low1] + b[low2]) >> 1;
    }
    else if (high1 - low1 == 1)
    {
        // two element array
        return (max(a[low1], b[low2]) + min(a[high1], b[high2])) >> 1;
    }

    int m1 = GetMedian(a, low1, high1);
    int m2 = GetMedian(b, low2, high2);
    
    auto mid1 = low1 + ((high1 - low1) >> 1);
    auto mid2 = low2 + ((high2 - low2) >> 1);

    if (m1 == m2)
    {
        return (m1 + m2) >> 1;
    }
    else if (m1 > m2)
    {
        // the diff of the size of the arrays cannot be greater than 1
        if (mid1 - low1 == high2 - mid2)
        {
            return FindMedian(a, low1, mid1, b, mid2, high2);
        }
        else if (mid1 - low1 == high2 - mid2 + 1)
        {
            return FindMedian(a, low1, mid1, b, mid2-1, high2);
        }
        else if (mid1 - low1 + 1 == high2 - mid2)
        {
            return FindMedian(a, low1, mid1, b, mid2+1, high2);
        }
        else
        {
            // should never reach here
            return FindMedian(a, low1, mid1, b, mid2+1, high2);
        }
    }
    else
    {
        // the diff of the size of the arrays cannot be greater than 1
        if (mid2 - low2 == high1 - mid1)
        {
            return FindMedian(a, mid1, high1, b, low2, mid2);
        }
        else if (mid2 - low2 == high1 - mid1 + 1)
        {
            return FindMedian(a, mid1 - 1, high1, b, low2, mid2);
        }
        else if (mid2 - low2 + 1 == high1 - mid1)
        {
            return FindMedian(a, mid1 + 1, high1, b, low2, mid2);
        }
        else
        {
            // should never reach here
            return FindMedian(a, mid1 + 1, high1, b, low2, mid2);
        }
    }
}

int main()
{
    vector<pair<vector<int>, vector<int>>> inputs = {
        make_pair<vector<int>, vector<int>>(
            {6},
            {4}
        ),
        make_pair<vector<int>, vector<int>>(
            {4, 5},
            {1, 2}
        ),
        make_pair<vector<int>, vector<int>>(
            {1, 2, 3, 6},
            {4, 6, 8, 10}
        ),
        make_pair<vector<int>, vector<int>>(
            {1, 5, 11, 15, 21},
            {4, 7, 14, 17, 19}
        ),
    };

    for (const auto& p : inputs)
    {
        const auto& a = p.first;
        const auto& b = p.second;
        if (a.empty() || b.empty())
        {
            continue;
        }
        cout << "For the inputs:" << endl;
        for (auto i : a)
        {
            cout << i << " ";
        }
        cout << " and " << endl;
        for (auto i : b)
        {
            cout << i << " ";
        }
        cout << endl;
        auto median = FindMedian(a, 0, a.size()-1, b, 0, b.size()-1);
        cout << "The median is: " << median << endl;
    }
    return 0;
}