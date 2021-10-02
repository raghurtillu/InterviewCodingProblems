#include <iostream>
#include <utility>
#include <queue>
#include <vector>
#include <unordered_set>

using namespace std;

// Finds the largest k numbers in a vector
vector<int> LargestK(const vector<int>& input, size_t K)
{
    if (input.empty() || K == 0)
    {
        return vector<int>();
    }

    auto comp = [](int a, int b) { return a > b; };
    priority_queue<int, vector<int>, decltype(comp)> pq(comp);

    // insert the first K elements into pq

    // using a set to remove duplicates
    unordered_set<int> distinct;
    size_t index = 0;
    for (index = 0; index < input.size(); ++index)
    {
        if (distinct.size() == K)
        {
            break;
        }
        distinct.insert(input[index]);
    }
    // now insert the elements in the set into pq
    for (auto it : distinct)
    {
        pq.push(it);
    }

    for (; index < input.size(); ++index)
    {
        if (input[index] > pq.top() &&
            distinct.find(input[index]) == distinct.cend())
        {
            distinct.erase(pq.top());
            pq.pop();

            distinct.insert(input[index]);
            pq.push(input[index]);
        }
    }

    // pop all the elements from the pq
    vector<int> results;
    while (!pq.empty())
    {
        results.push_back(pq.top());
        pq.pop();
    }
    std::reverse(results.begin(), results.end());
    return results;
}
    
int main() 
{
    vector<pair<vector<int>, size_t>> inputs = 
    {
        make_pair<vector<int>, size_t>({23, 12, 9, 30, 30, 30, 2, 50, 50, 2}, 4),
        make_pair<vector<int>, size_t>({9, 23, 23, 9, 23, 5, 7, 23, 5, 5, 7}, 2),
        make_pair<vector<int>, size_t>({2, 4, 3, 4, 3, 2}, 3),
        make_pair<vector<int>, size_t>({54553, 201557, 858524, 95183, 665451,
            314047, 875607, 596111, 952362}, 3),
        make_pair<vector<int>, size_t>({1, 2, 2, 3, 3, 3, 4, 5, 5, 6, 7}, 2),
        make_pair<vector<int>, size_t>({7, 6, 5, 4, 3, 2, 1}, 4),
    };

    for (const auto keyValPair : inputs)
    {
        const auto values = keyValPair.first;
        auto K = keyValPair.second;
        cout << "The largest " << K << " element(s) for the inputs ";
        for (auto val : values)
        {
            cout << val << " ";
        }
        cout << "are " << endl;
        auto res = LargestK(values, K);
        for (auto i : res)
        {
            cout << i << " ";
        }
        cout << endl;
    }
    return 0;
}