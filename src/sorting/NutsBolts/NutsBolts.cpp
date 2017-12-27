#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include <utility>

using namespace std;

void PrintVector(const vector<int>& inputs, bool flag)
{
    for (auto i : inputs)
    {
        if (flag)
        {
            cout << 'N';
        }
        else
        {
            cout << 'B';
        }
        cout << i << " ";
    }
    cout << endl;
}

// This partition is slightly different from the quicksort one
size_t Partition(vector<int>& inputs, size_t low, size_t high, int val)
{
    if (inputs.empty() || low > high || high - low > inputs.size())
    {
        return SIZE_MAX;
    }
    
    size_t i = low - 1;
    for (size_t j = low; j <= high; ++j)
    {
        if (inputs[j] < val)
        {
            i = i + 1;
            swap(inputs[i], inputs[j]);            
        }
        else if (inputs[j] == val)
        {
            if (j == high)
            {
                return high;
            }
            else
            {
                swap(inputs[j], inputs[high]);
                if (inputs[j] != inputs[high])
                {
                    j--;
                }
            }            
        }
    }
    swap(inputs[i+1], inputs[high]);
    return i + 1;
}

size_t PartitionNuts(vector<int>& nuts, size_t nLow, size_t nHigh, int val)
{
    return Partition(nuts, nLow, nHigh, val);
}

size_t PartitionBolts(vector<int>& bolts, size_t bLow, size_t bHigh, int val)
{
    return Partition(bolts, bLow, bHigh, val);
}

void MatchNutsAndBolts(vector<int>& bolts, size_t bLow, size_t bHigh,
                       vector<int>& nuts, size_t nLow, size_t nHigh)
{
    if (bolts.empty() || nuts.empty())
    {
        return;
    }
    else if (bLow >= bHigh || nLow >= nHigh)
    {
        return;
    }
    else if (bHigh - bLow != nHigh - nLow)
    {
        return;
    }
    else if (bHigh - bLow > bolts.size() || nHigh - nLow > nuts.size())
    {
        return;
    }

    int nutsVal = nuts[nHigh];
    size_t boltsPivotIndex = PartitionBolts(bolts, bLow, bHigh, nutsVal);
    if (boltsPivotIndex == SIZE_MAX)
    {
        // should not happen
        return;
    }

    int boltsVal = bolts[boltsPivotIndex];
    size_t nutsPivotIndex = PartitionNuts(nuts, nLow, nHigh, boltsVal);
    if (nutsPivotIndex == SIZE_MAX)
    {
        // should not happen
        return;
    }
    
    MatchNutsAndBolts(bolts, bLow, boltsPivotIndex - 1, nuts, nLow, nutsPivotIndex - 1);
    MatchNutsAndBolts(bolts, boltsPivotIndex + 1, bHigh, nuts, nutsPivotIndex + 1, nHigh);  
}

int main() 
{
    vector<pair<vector<int>, vector<int>>> inputs = 
    {
        // { {bolts}, {nuts} }
        make_pair<vector<int>, vector<int>>(
            {},     // bolts
            {1}),    // nuts
        make_pair<vector<int>, vector<int>>(
            {1},     // bolts
            {1}),    // nuts
        make_pair<vector<int>, vector<int>>(
            {1, 2, 3},     // bolts
            {3, 2, 1}),    // nuts
        make_pair<vector<int>, vector<int>>(
            {1, 2, 3},     // bolts
            {1, 2, 3}),    // nuts
        make_pair<vector<int>, vector<int>>(
            {1, 1, 1, 1},     // bolts
            {1, 1, 1, 1}),    // nuts
        make_pair<vector<int>, vector<int>>(
            {2, 2, 1, 1, 1, 1},     // bolts
            {2, 2, 1, 1, 1, 1}),    // nuts
        make_pair<vector<int>, vector<int>>(
            {1, 1, 1, 1, 2, 3, 3},     // bolts
            {1, 1, 1, 1, 2, 3, 3}),    // nuts
        make_pair<vector<int>, vector<int>>(
            {3, 1, 2, 4},     // bolts
            {2, 3, 4, 1}),    // nuts
        make_pair<vector<int>, vector<int>>(
            {6, 2, 1, 4, 5, 3},     // bolts
            {2, 1, 3, 6, 4, 5}),    // nuts
    };
    
    for (auto p : inputs)
    {
        auto bolts = p.first;
        auto nuts = p.second;
        cout << "Matching nuts and bolts are : " << endl;
        if (bolts.empty() || nuts.empty())
        {
            // should not happen
            continue;
        }

        MatchNutsAndBolts(bolts, 0, bolts.size()-1, nuts, 0, nuts.size()-1);
        
        PrintVector(bolts, 0);
        PrintVector(nuts, 1);
    }

    return 0;
}