#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>
using namespace std;

// Find four elements a, b, c and d in an array with elements such that a + b = c + d
// Input:   {3, 4, 7, 1, 2, 9, 8}
// Output:  (3, 8) and (4, 7)
// Explanation: 3 + 8 = 4 + 7

// Input:   {3, 4, 7, 1, 12, 9};
// Output:  (4, 12) and (7, 9)
// Explanation: 4 + 12 = 7 + 9

// Input:  {65, 30, 7, 90, 1, 9, 8};
// Output:  No pairs found
void SumPair(const vector<int>& inputs)
{
    if (inputs.size() < 4)
    {
        return;
    }

    unordered_map<int, pair<int, int>> lookup;
    bool found = false;

    for (size_t i = 0; i < inputs.size(); ++i)
    {
        for (size_t j = i + 1; j < inputs.size(); ++j)
        {
            auto sum = inputs[i] + inputs[j];
            if (lookup.find(sum) != lookup.cend())
            {
                if (!found)
                {
                    found = true;
                }
                const auto& p = lookup[sum];
                cout << "(" << p.first << ", " << p.second << ") and (" << inputs[i] << ", " << inputs[j] << ")";
                cout << endl;
            }
            else
            {
                lookup[sum] = {inputs[i], inputs[j]};
            }
        }
    }

    if (!found)
    {
        cout << "No pairs Found" << endl;
    }
}

// Find four elements a, b, c and d in an array with elements such that a * b = c * d
// Input  : arr[] = {3, 4, 7, 1, 2, 9, 8}
// Output : (4, 2) and (1, 8)
// Explanation: 4 * 2 = 1 * 8
// Input  : arr[] = {1, 6, 3, 9, 2, 10};
// Output : (6, 3) and (9, 2)
// Explanation: 6 * 3 = 9 * 2
void ProductPair(const vector<int>& inputs)
{
    if (inputs.size() < 4)
    {
        return;
    }

    unordered_map<long, pair<int, int>> lookup;
    bool found = false;

    for (size_t i = 0; i < inputs.size(); ++i)
    {
        for (size_t j = i + 1; j < inputs.size(); ++j)
        {
            long product = inputs[i] * inputs[j];
            if (lookup.find(product) != lookup.cend())
            {
                if (!found)
                {
                    found = true;
                }
                const auto& p = lookup[product];
                cout << "(" << p.first << ", " << p.second << ") and (" << inputs[i] << ", " << inputs[j] << ")";
                cout << endl;
            }
            else
            {
                lookup[product] = {inputs[i], inputs[j]};
            }
        }
    }

    if (!found)
    {
        cout << "No pairs Found" << endl;
    }
}

int main()
{
    const vector<vector<int>> sumPairInputs = 
    {
        {3, 4, 7, 1, 2, 9, 8},
        {3, 4, 7, 1, 12, 9},
        {65, 30, 7, 90, 1, 9, 8},
    };

    for (const auto &inputs : sumPairInputs)
    {
        cout << "For the inputs: {";
        for (size_t i = 0; i < inputs.size(); ++i)
        {
            cout << inputs[i];
            if (i != inputs.size() - 1)
            {
                cout << ", ";
            }
        }
        cout << "}, the following pairs are sum pairs such that (a + b) = (c + d)" << endl;
        SumPair(inputs);
    }

    const vector<vector<int>> productPairInputs = 
    {
        {1, 2, 3, 4, 5, 6, 7, 8},
        {1, 6, 3, 9, 2, 10},
    };

    for (const auto &inputs : productPairInputs)
    {
        cout << "For the inputs: {";
        for (size_t i = 0; i < inputs.size(); ++i)
        {
            cout << inputs[i];
            if (i != inputs.size() - 1)
            {
                cout << ", ";
            }
        }
        cout << "}, the following pairs are product pairs such that (a * b) = (c * d)" << endl;
        ProductPair(inputs);
    }

    return 0;
}