#include <iostream>
#include <queue>
#include <deque>
#include <utility>

using namespace std;

void MaximumWindow(const vector<int>& a, size_t wSize)
{
    if (a.empty() || wSize == 0 || wSize > a.size())
    {
        return;
    }
    
    deque<size_t> dq;
    size_t i = 0;
    for (i = 0; i < wSize; ++i)
    {
        while (!dq.empty() && a[i] >= a[dq.back()])
        {
            dq.pop_back();
        }
        dq.push_back(i);
    }

    size_t min = 0;
    for (; i < a.size(); ++i)
    {
        cout << "Max(" << min++ << ", " << i << "): " << a[dq.front()] << endl;
        // remove from the front of the window
        while (!dq.empty() && dq.front() <= i-wSize)
        {
            dq.pop_front();
        }
        while (!dq.empty() && a[i] >= a[dq.back()])
        {
            dq.pop_back();
        }
        dq.push_back(i);
    }
    if (!dq.empty())
    {
        cout << "Max(" << min++ << ", " << i << "): " << a[dq.front()] << endl;
    }
}

int main()
{
    vector<pair<vector<int>, size_t>> inputs = {
        make_pair<vector<int>, size_t>({1, 3, -1, -3, 5, 3, 6, 7}, 3),
        make_pair<vector<int>, size_t>({1, 2, 3, 4, 5, -1, -2, -3}, 2),
    };

    for (const auto& wPair : inputs)
    {
        const auto& val = wPair.first;
        auto wSize = wPair.second;
        for (auto c : val)
        {
            cout << c << " ";
        }
        cout << "[" << wSize << "]" << endl;
        MaximumWindow(val, wSize);
        cout << endl;
    }
    return 0;
}