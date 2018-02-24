#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

// Check if an array can be divided into pairs whose sum is divisible by k
// Input: arr[] = {9, 7, 5, 3}, k = 6
// Output: True
// We can divide array into (9, 3) and (7, 5). Sum of both of these pairs is a multiple of 6.

// Input: arr[] = {92, 75, 65, 48, 45, 35}, k = 10
// Output: True
// We can divide array into (92, 48), (75, 65) and (45, 35). Sum of all these pairs is a multiple of 10.

// Input: arr[] = {91, 74, 66, 48}, k = 10
// Output: False

bool CanPairsBeDivisible(const vector<int>& inputs, int k)
{
    if (inputs.empty() || k == 0)
    {
        return false;
    }
    else if (inputs.size() & 1)
    {
        // An odd length array cannot be divided into pairs
        return false;
    }

    // Create a frequency map to count occurrences of all remainders when divided by k
    unordered_map<int, int> freq;
    for (size_t i = 0; i < inputs.size(); ++i)
    {
        freq[inputs[i] % k]++;
    }

    for (size_t i = 0; i < inputs.size(); ++i)
    {
        auto rem = inputs[i] % k;
        if (rem == 0)
        {
            // If remainder is 0, then there must be two elements with 0 remainder
            if (freq[rem] & 1)
            {
                return false;
            }
        }
        else
        {
            // Else number of occurrences of remainder must be equal to number of occurrences of k - reminder
            if (freq[rem] != freq[k - rem])
            {
                return false;
            }
        }
    }
    return true;
}

int main()
{
    vector<pair<vector<int>, int>> values = 
    {
        make_pair<vector<int>, int>({92, 75, 65, 48, 45, 35}, 10),
    };

    for (const auto& p : values)
    {
        const auto& inputs = p.first;
        int k = p.second;
        cout << "For the inputs: ";
        for (auto i : inputs)
        {
            cout << i << " ";
        }
        bool res = CanPairsBeDivisible(inputs, k);
        cout << "the array " << ((res) ? "can" : "cannot") << " be divided into pairs whose sum is divisible by " << k;
    }
    return 0;
}