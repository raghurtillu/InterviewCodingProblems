#include <iostream>
#include <vector>
#include <queue>
#include <utility>
using namespace std;

// Given two integer arrays nums1 and nums2 sorted in ascending order and an integer k.
// Define a pair (u,v) which consists of one element from the first array and one element from the second array.
// Find the k pairs (u1,v1),(u2,v2) ...(uk,vk) with the smallest sums
// e.g.
// Given nums1 = [1,7,11], nums2 = [2,4,6],  k = 3
// Return: [1,2],[1,4],[1,6]
// The first 3 pairs are returned from the sequence:
// [1,2],[1,4],[1,6],[7,2],[7,4],[11,2],[7,6],[11,4],[11,6]

vector<pair<int, int>> KPairs(const vector<int>& num1, const vector<int>& num2, size_t k)
{
    if (num1.empty() || num2.empty() || k == 0)
    {
        return {};
    }
    auto comp = [](const pair<pair<int, int>, size_t>& a, const pair<pair<int, int>, size_t>& b)
    {
        return a.first.first + a.first.second > b.first.first + b.first.second;
    };

    priority_queue<pair<pair<int, int>, size_t>, vector<pair<pair<int, int>, size_t>>, decltype(comp)> pq(comp);
    size_t size = min(k, num1.size());
    for (size_t i = 0; i < size; ++i)
    {
        pq.push(make_pair<pair<int, int>, size_t>({num1[i], num2[0]}, 0));
    }

    vector<pair<int, int>> result;
    while (--k != SIZE_MAX && !pq.empty())
    {
        auto p = pq.top();
        pq.pop();
        result.push_back({p.first.first, p.first.second});
        size_t index = p.second;
        if (index + 1 < num2.size())
        {
            pq.push(make_pair<pair<int, int>, size_t>({p.first.first, num2[index + 1]}, index + 1));
        }
    }
    return result;
}

int main()
{
    struct Input
    {
        vector<int> first;
        vector<int> second;
        size_t k;
        Input(const vector<int>& _first, const vector<int>& _second, size_t _k) :
            first(_first), second(_second), k(_k)
        {

        }
    };

    vector<Input> inputs = 
    {
        Input({1, 7, 11}, {2, 4, 6}, 3),
        Input({1, 7, 11}, {2, 4, 6}, 5),
        Input({1, 1, 2}, {1, 2, 3}, 4),
        Input({1, 2}, {3}, 3),
    };

    for (const auto& ip : inputs)
    {
        const auto& first = ip.first;
        const auto& second = ip.second;
        size_t k = ip.k;
        cout << "For the inputs: ";
        for (auto i : first)
        {
            cout << i << " ";
        }
        cout << "and ";
        for (auto i : second)
        {
            cout << i << " ";
        }
        cout << "the minimum " << k << " pairs are as follows: " << endl;
        vector<pair<int, int>> results = KPairs(first, second, k);
        for (const auto& p : results)
        {
            cout << "(" << p.first << ", " << p.second << ") ";
        }
        cout << endl;
    }
    return 0;
}