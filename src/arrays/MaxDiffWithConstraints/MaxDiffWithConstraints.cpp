#include <iostream>
#include <utility>
#include <vector>
using namespace std;

// Maximum difference between two elements such that larger element appears after the smaller number
// e.g. [2, 3, 10, 6, 4, 8, 1] then returned value should be 8 (Diff between 10 and 2)

int GetMaxDiff(const vector<int>& inputs)
{
    if (inputs.size() < 2)
    {
        // cannot form diff with < 2 elements
        return 0;
    }

    int maxDiff = INT_MIN;
    int minElement = inputs[0];

    for (size_t i = 1; i < inputs.size(); ++i)
    {
        maxDiff = max(maxDiff, inputs[i] - minElement);
        minElement = min(minElement, inputs[i]);
    }
    return maxDiff;
}
int main()
{
    vector<vector<int>> values = 
    {
        {2, 3, 10, 6, 4, 8, 1},
        {7, 9, 5, 6, 3, 2},
        {5, 1, 0, -1, -4, -6},
        {4, 9, -5, 2, 0, -1, 7},
    };

    cout << "Maximum difference between two elements such that larger element appears after the smaller number";
    cout << endl;
    for (auto inputs : values)
    {
        cout << "Inputs: ";
        for (auto i : inputs)
        {
            cout << i << " ";
        }
        cout << endl;
        cout << "Maxdiff: " << GetMaxDiff(inputs);
        cout << endl;
    }
    return 0;
}