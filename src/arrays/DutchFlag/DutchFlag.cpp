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

    size_t rIndex = 0, gIndex = 0, bIndex = inputs.size()-1;
    while (gIndex <= bIndex && bIndex != SIZE_MAX)
    {
        if (inputs[gIndex] == 'b')
        {
            swap(inputs[bIndex], inputs[gIndex]);
            bIndex--;
        }
        else if (inputs[gIndex] == 'r')
        {
            swap(inputs[gIndex], inputs[rIndex]);
            rIndex++;
            gIndex++;
        }
        else
        {
            gIndex++;
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