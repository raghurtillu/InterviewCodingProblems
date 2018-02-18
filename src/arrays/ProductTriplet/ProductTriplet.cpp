#include <iostream>
#include <vector>
#include <utility>
using namespace std;

// This has O(nlogn) time complexity
int ProductTriplet(vector<int> inputs)
{
    if (inputs.size() < 3)
    {
        return INT_MIN;
    }

    sort(inputs.begin(), inputs.end());
    size_t n = inputs.size();
    return max(inputs[0] * inputs[1] * inputs[n-1],
        inputs[n-1] * inputs[n-2] * inputs[n-3]);
}

// This has O(n) time complexity
int ProductTripletOpt(const vector<int>& inputs)
{
    if (inputs.empty())
    {
        return 0;
    }

    int maxA = inputs[0], maxB = INT_MIN, maxC = INT_MIN;
    int minA = inputs[0], minB = INT_MAX;

    for (size_t i = 1; i < inputs.size(); ++i)
    {
        if (inputs[i] > maxA)
        {
            maxC = maxB;
            maxB = maxA;
            maxA = inputs[i];
        }
        else if (inputs[i] > maxB)
        {
            maxC = maxB;
            maxB = inputs[i];
        }
        else if (inputs[i] > maxC)
        {
            maxC = inputs[i];
        }

        if (inputs[i] < minA)
        {
            minB = minA;
            minA = inputs[i];
        }
        else if (inputs[i] < minB)
        {
            minB = inputs[i];
        }
    }
    return max(maxA * maxB * maxC, minA * minB * maxA);
}

int main()
{
    vector<vector<int>> values = 
    {
        {-3, -4, -7, -2},
        {0, 3, 5, 6, 20},
        {-10, -3, -5, -6, -20},
        {1, 4, 3, -6, -7, 0},
    };

    for (const auto& inputs : values)
    {
        cout << "For the inputs: ";
        for (auto i : inputs)
        {
            cout << i << " ";
        }
        cout << endl;
        cout << "The maximum triplet product is: " << ProductTripletOpt(inputs) << endl;
    }
    return 0;
}