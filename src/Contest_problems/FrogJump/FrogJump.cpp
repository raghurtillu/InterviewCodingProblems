#include <iostream>
#include <vector>
using namespace std;

// https://leetcode.com/problems/frog-jump/description/
bool _CanJump(const vector<int>& stones, size_t index, int k)
{
    if (stones.empty() || index >= stones.size())
    {
        return false;
    }
    else if (index == stones.size() - 1)
    {
        return true;
    }
    for (size_t pos = index+1; pos < stones.size(); ++pos)
    {
        auto gap = stones[pos] - stones[index];
        if (gap < k - 1)
        {
            continue;
        }
        else if (gap > k + 1)
        {
            return false;
        }
        if (_CanJump(stones, pos, gap))
        {
            return true;
        }
    }
    return false;
}

bool CanJump(const vector<int>& stones)
{
    if (stones.empty())
    {
        return false;
    }
    size_t index = 0;
    int k = 0;
    return _CanJump(stones, index, k);
}

int main()
{
    vector<vector<int>> inputs = {
        {0, 1, 3, 5, 6, 8, 12, 17},
        {0, 1, 2, 3, 4, 8, 9, 11},
    };

    cout << "Frog jump for the set of stones:" << endl;
    for (const auto& stones : inputs)
    {
        for (auto i : stones)
        {
            cout << i << " ";
        }
        bool res = CanJump(stones);
        if (res) { cout << "Yes"; }
        else { cout << "No"; }
        cout << endl;
    }

    return 0;
}