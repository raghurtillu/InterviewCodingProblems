#include <iostream>
#include <vector>
#include <stack>
using namespace std;

// Given n non-negative integers representing an elevation map where the width of each bar is 1, 
// compute how much water it is able to trap after raining.
// https://leetcode.com/problems/trapping-rain-water/description/
int WaterTrap(const vector<int>& heights)
{
    if (heights.empty())
    {
        return 0;
    }
    
    vector<int> ngeLeft(heights.size(), 0), ngeRight(heights.size(), 0);
    // Get greatest height left
    int greatestLeft = 0;
    for (size_t i = 0; i < heights.size(); ++i)
    {
        ngeLeft[i] = greatestLeft > heights[i] ? greatestLeft : 0;
        greatestLeft = std::max(greatestLeft, heights[i]);
    }

    // Get greatest height right
    int greatestRight = 0;
    for (size_t i = heights.size() - 1; i != SIZE_MAX; --i)
    {
        ngeRight[i] = greatestRight > heights[i] ? greatestRight : 0;
        greatestRight = std::max(greatestRight, heights[i]);
    }
    
    int total = 0;
    for (size_t i = 0; i < heights.size(); ++i)
    {
        if (ngeLeft[i] == 0 || ngeRight[i] == 0)
        {
            continue;
        }
        total += std::min(ngeLeft[i], ngeRight[i]) - heights[i];
    }
    return total;
}

int main() 
{
    vector<vector<int>> inputs = 
    {
        {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1},

    };

    cout << "Water trap for input heights: " << endl;
    for (const auto& input : inputs)
    {
        for (size_t i = 0; i < input.size(); ++i)
        {
            cout << input[i];
            if (i != input.size() - 1) { cout << ", "; }
        }
        cout << ": " << WaterTrap(input) << " unit(s)" << endl;
    }
    return 0;
}