#include <iostream>
#include <vector>
#include <stack>
using namespace std;

// Given n non-negative integers representing an elevation map where the width of each bar is 1, 
// compute how much water it is able to trap after raining.
// https://leetcode.com/problems/trapping-rain-water/description/
void GetGreatestHeightLeftandRight(const vector<int>& height, vector<int>& ngeLeft, vector<int>& ngeRight)
{
    if (height.empty() || ngeLeft.size() != height.size() || ngeRight.size() != height.size()) { return; }
    
    // get greatest height to the left
    stack<int> lStk;
    for (size_t i = 0; i < height.size(); ++i)
    {
        while (!lStk.empty() && height[i] >= lStk.top())
        {
            lStk.pop();
        }
        ngeLeft[i] = !lStk.empty() ? lStk.top() : 0;
        if (lStk.empty() || height[i] > lStk.top())
        {
            lStk.push(height[i]);
        }
    }
    // get greatest height bar to the right
    stack<int> rStk;
    for (size_t i = height.size() - 1; i != SIZE_MAX; --i)
    {
        while (!rStk.empty() && height[i] >= rStk.top())
        {
            rStk.pop();
        }
        ngeRight[i] = !rStk.empty() ? rStk.top() : 0;
        if (rStk.empty() || height[i] > rStk.top())
        {
            rStk.push(height[i]);
        }
    }
}

int WaterTrap(const vector<int>& height) 
{
    if (height.empty()) { return 0; }
    vector<int> ngeLeft(height.size()), ngeRight(height.size());
    GetGreatestHeightLeftandRight(height, ngeLeft, ngeRight);
    int total = 0;
    for (size_t i = 0; i < height.size(); ++i)
    {
        if (ngeLeft[i] == 0 || ngeRight[i] == 0) { continue; }
        total += min(ngeLeft[i], ngeRight[i]) - height[i];
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