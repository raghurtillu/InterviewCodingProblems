#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

std::pair<int, int> MinMax(const vector<int>& inputs)
{
    if (inputs.empty())
    {
        return {INT_MAX, INT_MIN};
    }
    
    int minSoFar = INT_MAX;
    int maxSoFar = INT_MIN;

    for (size_t i = 0; i + 1 < inputs.size(); i+=2)
    {
        if (inputs[i] > inputs[i+1])
        {
            maxSoFar = max(maxSoFar, inputs[i]);
            minSoFar = min(minSoFar, inputs[i+1]);
        }
        else
        {
            maxSoFar = max(maxSoFar, inputs[i+1]);
            minSoFar = min(minSoFar, inputs[i]);
        }
    }
    maxSoFar = max(maxSoFar, inputs[inputs.size()-1]);
    minSoFar = min(minSoFar, inputs[inputs.size()-1]);

    return {minSoFar, maxSoFar};
}

int main()
{
    vector<vector<int>> values = 
    {
        {},
        {1},
        {2, 1},
        {3, 1, 2},
        {1, 2, 3, 4},
        {5, -4, 3, -11},
        {5, 11, 6, 9, 10, 40},
        {11, 5, -9, 6, -10, 4, -11},
        {-11, 5, 9, 6, 10, 4, 11},
        {11, 5, 9, 6, 10, 4, 1, -4}
    };

    for (auto inputs : values)
    {
        cout << "For inputs: ";
        for (auto i : inputs)
        {
            cout << i << " ";
        }
        cout << endl;

        auto result = MinMax(inputs);

        cout << "Min: " << result.first << ", Max: " << result.second << endl;
    }
    return 0;
}