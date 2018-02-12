#include <iostream>
#include <vector>
#include <utility>
using namespace std;

// Given a set, we need to find maximum and minimum possible product among all subsets of the set
// Input : arr[] = {4, -2, 5};
// Output: Maximum product = 20, Minimum product = -40
// Maximum product is obtained by multiplying
// 4 5
// Minimum product is obtained by multiplying 
// 4, -2, 5

// Input : arr[] = {-4, -2, 3, 7, 5, 0, 1};
// Output: Maximum product = 840, Minimum product = -420
// Maximum product is obtained by multiplying
// -4, -2, 3, 7, 5
// Minimum product is obtained by multiplying 
// -4, 3, 7, 5

pair<int, int> MaxMinProductSubsets(const vector<int>& inputs)
{
    if (inputs.empty())
    {
        return {INT_MAX, INT_MIN};
    }
    else if (inputs.size() == 1)
    {
        return {inputs[0], inputs[0]};
    }

    int currMaxProduct = inputs[0], currMinProduct = inputs[0];
    int prevMaxProduct = inputs[0], prevMinProduct = inputs[0];
    int maxProduct = inputs[0], minProduct = inputs[0];

    for (size_t i = 1; i < inputs.size(); ++i)
    {
        // Current maximum product is maximum of following
		// 	1) prevMax * curelement (when curelement is +ve)
		// 	2) prevMin * curelement (when curelement is -ve)
		// 	3) Element itself
		// 	4) Previous max product 
        currMaxProduct = max(prevMaxProduct * inputs[i], 
                            max(prevMinProduct * inputs[i], 
                                max(inputs[i], prevMaxProduct)));

        // Current min product computation is similar to current max product
        currMinProduct = min(prevMaxProduct * inputs[i], 
                            min(prevMinProduct * inputs[i], 
                                min(inputs[i], prevMinProduct)));
        
        maxProduct = max(maxProduct, currMaxProduct);
        minProduct = min(minProduct, currMinProduct);

        prevMaxProduct = currMaxProduct;
        prevMinProduct = currMinProduct;
    }
    return {maxProduct, minProduct};
}

int main()
{
    vector<vector<int>> values = 
    {
        {4, -2, 5},
        {-4, -2, 3, 7, 5, 0, 1},
    };

    for (const auto& inputs : values)
    {
        cout << "For the inputs: ";
        for (auto i : inputs)
        {
            cout << i << " ";
        }
        cout << endl;
        pair<int, int> p = MaxMinProductSubsets(inputs);
        cout << "The maximum and minimum product of the subsets are: " <<
            p.first << " and " << p.second << endl;
    }
    return 0;    
}