#include <iostream>
#include <vector>
using namespace std;

void _SubsetSum(const vector<int>& weights, size_t index, int sum, vector<int>& subset)
{
    if (weights.empty() || index > weights.size())
    {
        return;
    }
    else if (sum == 0) 
    {
        if (!subset.empty()) 
        {
            cout << "Subset" << endl;
            for(auto i : subset) 
            {
                cout << i << " ";
            }
            cout << endl;
        }
        return;
    }
    // do not pick the value
    _SubsetSum(weights, index + 1, sum, subset);

    // pick the value
    subset.push_back(weights[index]);
    _SubsetSum(weights, index + 1, sum - weights[index], subset);
    subset.pop_back();
}

void SubsetSum(const vector<int>& weights, int sum)
{
    if (weights.empty())
    {
        return;
    }
    vector<int> subset;
    _SubsetSum(weights, 0, sum, subset);
}

int main()
{
    vector<pair<vector<int>, int>> inputs = 
    {
        make_pair<vector<int>, int>(
            {15, 22, 14, 26, 32, 9, 16, 8},
            53), // sum of multiple values
        make_pair<vector<int>, int>(
            {15, 22, 14, 26, 32, 9, 16, 8, 20},
            50), // sum of multiple values
        make_pair<vector<int>, int>(
             {15, 22, 14, 26, 32, 9, 16, 8},
             9), // single value
        make_pair<vector<int>, int>(
            {15, 22, 14, 26, 32, 9, 16, 8},
            180) // non-existant value
    };

    for (const auto& p : inputs)
    {
        const auto& weights = p.first;
        cout << "For the inputs: " << endl;
        for (auto i : weights)
        {
            cout << i << " ";
        }
        int sum = p.second;
        cout << "subsets having the sum " << sum << " are " << endl;
        SubsetSum(weights, sum);
    }
    
    return 0;
}