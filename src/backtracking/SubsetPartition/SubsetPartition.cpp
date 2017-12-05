#include <iostream>
#include <vector>
using namespace std;

void PrintSubset(const vector<int>& val)
{
    cout << "{";
    for (size_t i = 0; i < val.size(); ++i)
    {
        if (i == val.size()-1)
        {
            cout << val[i];
        }
        else
        {
            cout << val[i] << ",";
        }
    }
    cout << "}";
}

void SubsetPartition(const vector<int>& inputs, size_t pos, 
    vector<int>& left, int lSum, vector<int>& right, int rSum)
{
    if (inputs.empty() || pos > inputs.size())
    {
        return;
    }
    else if (pos == inputs.size())
    {
        if (lSum == rSum)
        {
            PrintSubset(left);
            cout << "  ";
            PrintSubset(right);
            cout << endl;
            return;
        }
        else
        {
            return;
        }
    }

    auto val = inputs[pos];
    left.push_back(val);
    lSum += val;
    SubsetPartition(inputs, pos+1, left, lSum, right, rSum);
    left.pop_back();
    lSum -= val;

    right.push_back(val);
    rSum += val;
    SubsetPartition(inputs, pos+1, left, lSum, right, rSum);
    right.pop_back();
    rSum -= val;    
}

int main()
{
    vector<vector<int>> values = 
    {
        {1, 5, 11, 5},
        {4, 7, 2, 1},
    };

    for (const auto& inputs : values)
    {
        cout << endl;
        cout << "For the inputs ";
        PrintSubset(inputs);

        cout << " partitioned subsets are as follows" << endl;
        vector<int> left, right;
        int lSum = 0, rSum = 0;
        size_t pos = 0;

        SubsetPartition(inputs, pos, left, lSum, right, rSum);
    }
    return 0;
}