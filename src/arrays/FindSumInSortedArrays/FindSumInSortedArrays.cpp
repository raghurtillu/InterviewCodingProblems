#include <iostream>
#include <vector>
using namespace std;

void PrintPairSumInSortedArrays(const vector<int>& a, const vector<int>& b, int sum)
{
    if (a.empty() || b.empty())
    {
        return;
    }

    bool found = false;
    for (size_t i = 0, j = b.size() - 1; i < a.size() && j != SIZE_MAX; )
    {
        auto val = a[i] + b[j];
        if (val == sum)
        {
            if (!found) { found = true; }

            cout << "(" << a[i] << ", " << b[j] << ") ";
            ++i;
            --j;
        }
        else if (val > sum)
        {
            --j;
        }
        else if (val < sum)
        {
            ++i;
        }
    }

    if (!found)
    {
        cout << "No pairs Found" << endl;
    }
}

int main()
{
    struct SumInput {
        vector<int> a, b;
        int sum = 0;
        SumInput(const vector<int>& i, const vector<int>& j, int s) : a(i), b(j), sum(s)
        {}
    };

    vector<SumInput> inputs = 
    {
        SumInput({1, 4, 5, 6}, {2, 3, 7, 8}, 12),
        SumInput({1, 3, 5, 7, 9, 11}, {2, 4, 6, 8, 10}, 15),
        SumInput({-3, -2}, {-11, -9, -6, -4, -3, 0, 2}, -6),
        SumInput({1, 3, 5, 7}, {2, 3, 4, 5}, 27),
    };

    for (const auto& si : inputs)
    {
        const auto& a = si.a;
        const auto& b = si.b;
        int sum = si.sum;

        cout << "For the sorted inputs, ";
        cout << "{";
        for (size_t i = 0; i < a.size(); ++i)
        {
            cout << a[i];
            if (i != a.size() - 1)
            {
                cout << ", ";
            }
        }
        cout << "}";
        cout << ", ";
        cout << "{";
        for (size_t i = 0; i < b.size(); ++i)
        {
            cout << b[i];
            if (i != b.size() - 1)
            {
                cout << ", ";
            }
        }
        cout << "}";
        cout << " the pair(s) having the sum " << sum << " are as follows: " << endl;
        PrintPairSumInSortedArrays(a, b, sum);
        cout << endl;
    }
    return 0;
}