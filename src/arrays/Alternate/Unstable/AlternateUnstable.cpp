#include <iostream>
#include <vector>
#include <utility>
using namespace std;

void Rearrange(vector<int>& a)
{
    if (a.empty())
    {
        return;
    }

    size_t i = 0, j = a.size()-1;
    while (i < j)
    {
        while (i < a.size() && a[i] > 0)
        {
            ++i;
        }
        while (j != SIZE_MAX && a[j] < 0)
        {
            --j;
        }
        if (i >= a.size() || j == SIZE_MAX)
        {
            break;
        }
        else if (i < j)
        {
            swap(a[i], a[j]);
        }
    }
    if (i == 0 || i >= a.size())
    {
        // nothing to arrange
        return;
    }

    size_t k = 0;
    while (i < a.size() && k < a.size())
    {
        swap(a[i], a[k]);
        i += 1;
        k += 2;
    }
}
int main()
{
    vector<vector<int>> inputs = 
    {
        {2, 3, -4, -1, 6, -9},
        {-1, -2, -3, -4, 9},
        {-1, -2, -3, -4},
        {1, 2, 3, 4, 5}
    };

    for (auto& val : inputs)
    {
        for (auto c : val)
        {
            cout << c << " ";
        }

        Rearrange(val);
        cout << endl << "after rearranging" << endl;

        for (auto c : val)
        {
            cout << c << " ";
        }
        cout << endl << endl;
    }

    return 0;
}