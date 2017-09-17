#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <utility>
using namespace std;

vector<string> SumZero(const vector<int>& intArr)
{    
    if (intArr.empty())
    {
        return vector<string>();
    }
    
    unordered_map<int, size_t> lookup;
    int sum = 0;
    vector<pair<size_t, size_t>> locations;

    for (size_t i = 0; i < intArr.size(); ++i)
    {
        sum += intArr[i];
        if (intArr[i] == 0 || sum == 0)
        {
            if (intArr[i] == 0)
            {
                locations.push_back({i, i});
            }
            else if (sum == 0)
            {
                locations.push_back({lookup[sum], i});
            }
        }
        else if (lookup.find(sum) != lookup.cend())
        {
            locations.push_back({lookup[sum]+1, i});
        }
        lookup[sum] = i;
    }

    vector<string> results;
    for (auto loc : locations)
    {
        auto first = loc.first;
        auto second = loc.second;
        if (first == second)
        {
            results.push_back(to_string(intArr[first]));
        }
        else
        {
            string res;
            for (; first < second; ++first)
            {
                res += to_string(intArr[first]);
                res += ",";
            }
            res += to_string(intArr[first]);
            results.push_back(res);
        }
    }
    return results;
}

int main()
{
    vector<vector<int>> values = 
    {
        {1, 2, -3, 7, -4},
        {1, 4, -2, -2, 5, -4, 3},
        {-3, 2, 3, 1, 6},
        {0, 1, 2, 3, 4, -10},
    };

    for (const auto& inputs : values)
    {
        cout << "For the inputs: " << endl;
        for (auto i : inputs)
        {
            cout << i << " ";
        }
        cout << endl;
        cout << "zero sum arrays are: " << endl;
        auto results = SumZero(inputs);
        for (size_t i = 0; i < results.size(); ++i)
        {
            cout << results[i] << endl;
        }
    }

    return 0;
}