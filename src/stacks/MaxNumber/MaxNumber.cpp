#include <iostream>
#include <vector>
#include <stack>
using namespace std;

// Given an array of positive numbers and a number k, form maximum number from the input array
// of length k while maintaining relative order of the numbers in the array
// for e.g. if k = 2 and array is [4, 5, 3, 2, 1, 6, 0, 8], maximum number formed is 68
// for k = 3, maximum number formed is 568

int GetMaxNumber(const vector<int>& inputs, size_t k)
{
    if (k == 0 || k > inputs.size())
    {
        return 0;
    }

    stack<int> stk;
    for (size_t i = 0; i < inputs.size(); ++i)
    {
        if (stk.empty())
        {
            // if the stack is empty; simply push the element
            stk.push(inputs[i]);
        }
        else if (inputs[i] < stk.top())
        {
            if (stk.size() < k)
            {
                // if there is space in the stack; push the element
                stk.push(inputs[i]);
            }
        }
        else if (inputs[i] > stk.top())
        {
            while (!stk.empty() && inputs[i] > stk.top())
            {
                if (k - stk.size() + 1 <= inputs.size() - i)
                {
                    stk.pop();
                }
                else
                {
                    break;
                }
            }
            stk.push(inputs[i]);
        }
    }

    int num = 0;
    size_t units = 1;
    while (!stk.empty())
    {
        num = units * stk.top() + num;
        units *= 10;
        stk.pop();
    }
    return num;
}
int main()
{
    vector<pair<vector<int>, size_t>> inputs = 
    {
        make_pair<vector<int>, size_t>({4, 5, 3, 2, 1, 6, 0, 8}, 1),
        make_pair<vector<int>, size_t>({4, 5, 3, 2, 1, 6, 0, 8}, 2),
        make_pair<vector<int>, size_t>({4, 5, 3, 2, 1, 6, 0, 8}, 3),
        make_pair<vector<int>, size_t>({4, 5, 3, 2, 1, 6, 0, 8}, 4),
        make_pair<vector<int>, size_t>({4, 5, 3, 2, 1, 6, 0, 8}, 5),
        make_pair<vector<int>, size_t>({4, 5, 3, 2, 1, 6, 0, 8}, 6),
        make_pair<vector<int>, size_t>({4, 5, 3, 2, 1, 6, 0, 8}, 7),
        make_pair<vector<int>, size_t>({4, 5, 3, 2, 1, 6, 0, 8}, 8),
        make_pair<vector<int>, size_t>({4, 5, 3, 2, 1, 6, 0, 8}, 9),
        make_pair<vector<int>, size_t>({3, 6, 4, 8, 1, 2, 5}, 1),
        make_pair<vector<int>, size_t>({3, 6, 4, 8, 1, 2, 5}, 2),
        make_pair<vector<int>, size_t>({3, 6, 4, 8, 1, 2, 5}, 3),
        make_pair<vector<int>, size_t>({3, 6, 4, 8, 1, 2, 5}, 4),
        make_pair<vector<int>, size_t>({3, 6, 4, 8, 1, 2, 5}, 5),
        make_pair<vector<int>, size_t>({3, 6, 4, 8, 1, 2, 5}, 6),
        make_pair<vector<int>, size_t>({3, 6, 4, 8, 1, 2, 5}, 7),
        make_pair<vector<int>, size_t>({1, 2, 3, 4, 5}, 1),
        make_pair<vector<int>, size_t>({1, 2, 3, 4, 5}, 2),
        make_pair<vector<int>, size_t>({1, 2, 3, 4, 5}, 3),
        make_pair<vector<int>, size_t>({1, 2, 3, 4, 5}, 4),
        make_pair<vector<int>, size_t>({1, 2, 3, 4, 5}, 5),
    };
    for (size_t i = 0; i < inputs.size(); ++i)
    {
        const auto& p = inputs[i];
        if (i == 0 || inputs[i].first != inputs[i-1].first)
        {
            cout << "For the inputs: ";
            cout << "{";
            for (size_t j = 0; j < p.first.size(); ++j)
            {
                cout << p.first[j];
                if (j != p.first.size() - 1)
                {
                    cout << ", ";
                }
            }
            cout << "}" << endl;
        }
        cout << "Maximum number with " << p.second << " digits is: ";
        auto num = GetMaxNumber(p.first, p.second);
        cout << num << endl;
    }
    cout << endl;
    return 0;
}
