#include <iostream>
#include <vector>
using namespace std;

// Counts the distinct (absolute) count in a sorted array
size_t GetAbsoluteDistinctCount(const vector<int>& a)
{
    if (a.empty())
    {
        return 0;
    }

    size_t i = 0, j = a.size() - 1;
    size_t count = a.size();
    int sum = 0;

    while (i < j)
    {
        while (i < j && i < a.size()-1 && a[i] == a[i+1])
        {
            ++i;
            --count;
        }
        while (i < j && j > 0 && a[j] == a[j-1])
        {
            --j;
            --count;
        }
        if (i == j || i >= a.size() || j == 0)
        {
            return count;
        }

        sum = a[i] + a[j];
        if (sum == 0)
        {
            --count;
            ++i;
            --j;
        }
        else if (sum < 0)
        {
            ++i;
        }
        else
        {
            --j;
        }
    }
    return count;
}

int main()
{
    vector<vector<int>> inputs = {
        {-3, -2, 0, 3, 4, 5},
        {-1, -1, -1, -1, 0, 1, 1, 1, 1},
        {-1, -1, -1, -1, 0},
        {0, 0, 0},
    };

    cout << "Distinct counts " << endl;
    for (auto& val : inputs)
    {
        for (auto i : val)
        {
            cout << i << " ";
        }
        auto res = GetAbsoluteDistinctCount(val);
        cout << ": " << res << endl; 
    }
    return 0;
}