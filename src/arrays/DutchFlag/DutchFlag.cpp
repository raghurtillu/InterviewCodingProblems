#include <iostream>
#include <vector>
#include <utility>
using namespace std;

// 3 way partition problem
void DutchFlag(vector<char>& inputs)
{
    if (inputs.empty())
    {
        return;
    }

    // arrange in r, g, b order
    // rIndex -> [0..r]
    // gIndex -> [r+1..g]
    // bIndex -> [b..)
    // [g+1..b] -> unknown
    size_t rIndex = 0, gIndex = 0, bIndex = inputs.size()-1;
    while (gIndex <= bIndex && bIndex != SIZE_MAX)
    {
        if (inputs[gIndex] == 'r')
        {
            swap(inputs[gIndex], inputs[rIndex]);
            rIndex++;
            gIndex++;
        }
        else if (inputs[gIndex] == 'g')
        {
            gIndex++;
        }
        else if (inputs[gIndex] == 'b')
        {
            swap(inputs[bIndex], inputs[gIndex]);
            bIndex--;
        }
    }
}

int main()
{
    vector<vector<char>> values = 
    {
        {'b', 'g', 'r', 'r', 'g', 'b', 'r', 'g', 'b', 'g'},
        {'b', 'b', 'b', 'b'},
        {'b', 'b', 'r', 'g'},
        {'r', 'b', 'b', 'g', 'r', 'b'},
    };
    
    for (auto& inputs : values)
    {
        cout << "Input: ";
        for (auto c: inputs)
        {
            cout << c;
        }
        cout << endl;

        DutchFlag(inputs);

        cout << "Output: ";
        for (auto c: inputs)
        {
            cout << c;
        }
        cout << endl;
    }
    return 0;
}