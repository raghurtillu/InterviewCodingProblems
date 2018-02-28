#include <iostream>
#include <vector>
using namespace std;

// Given a number prints a permutation of well formed brackets
// n = 1: ()
// n = 2: (()), ()()
// n = 3: ((())) (()()) (())() ()(()) ()()()

void _WellFormedBrackets(size_t openCount, size_t closeCount, size_t n, string& res)
{
    if (n == 0 || openCount > n || closeCount > n || closeCount > openCount)
    {
        return;
    }
    else if (openCount == n && closeCount == n)
    {
        if (!res.empty())
        {
            cout << res << " ";
        }
        return;
    }

    res.push_back('(');
    _WellFormedBrackets(openCount + 1, closeCount, n, res);
    res.pop_back();
    
    res.push_back(')');
    _WellFormedBrackets(openCount, closeCount + 1, n, res);
    res.pop_back();
}

void WellFormedBrackets(size_t n)
{
    size_t openCount = 0, closeCount = 0;
    string res;
    _WellFormedBrackets(openCount, closeCount, n, res);
}

int main()
{
    vector<size_t> inputs = 
    {
        1,
        2,
        3,
        4,
    };

    for (auto n : inputs)
    {
        cout << "Well formed brackets for n = " << n << " are as follows" << endl;
        WellFormedBrackets(n);
        cout << endl << endl;
    }
    return 0;
}
