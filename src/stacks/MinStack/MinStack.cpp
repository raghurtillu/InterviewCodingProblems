#include <iostream>
#include <stack>
#include <vector>
using namespace std;

void MinStack(const vector<int>& a)
{
    if (a.empty())
    {
        return;
    }

    stack<int> s, minStack;

    // insert elements into stack
    cout << "Elements in stack: " << endl;
    for (size_t i = 0; i < a.size(); ++i)
    {
        cout << a[i] << " ";
        s.push(a[i]);
        if (minStack.empty())
        {
            minStack.push(a[i]);
        }
        else
        {
            if (a[i] <= minStack.top())
            {
                minStack.push(a[i]);
            }
        }
    }
    cout << endl;
    cout << "min element is: " << minStack.top() << endl;
    while (!s.empty())
    {
        auto val = s.top();
        s.pop();
        if (val == minStack.top())
        {
            minStack.pop();
        }
        auto min = (!minStack.empty()) ? minStack.top() : INT_MIN;
        cout << "after popping " << val << ", min element is: ";
        if (min != INT_MIN)
        {
            cout << min;
        }
        else
        {
            cout << "empty";
        }
        cout << endl;
    }
}

int main()
{
    vector<vector<int>> inputs = {
        {1, 2, 3, 4, 5},
        {5, 4, 3, 2, 1},
        {1, 1, 1, 1},
        {0, 1, 0, 1, 1, 0},
        {-1, 3, -3, 7, 2, -5},
    };

    for (const auto& val : inputs)
    {
        MinStack(val);
        cout << endl;
    }
    return 0;
}