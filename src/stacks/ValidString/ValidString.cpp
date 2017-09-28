#include <iostream>
#include <stack>
#include <string>
#include <utility>
#include <vector>
using namespace std;

int maxLenMatchingParen(const string& expr)
{
    if (expr.empty())
    {
        return 0;
    }

    int maxLen = 0;
    stack<int> s;
    s.push(-1);
    for (auto i = 0; i < expr.size(); ++i)
    {
        if (expr[i] == '(')
        {
            s.push(i);
        }
        else if (expr[i] == ')')
        {
            if (!s.empty())
            {
                s.pop();
                if (!s.empty())
                {
                    maxLen = max(maxLen, i-s.top());
                }
                else
                {
                    s.push(i);
                }
            }
            else
            {
                s.push(i);
            }
        }
    }
    return maxLen;
}

int main()
{
    vector<string> inputs = {
        "((((())(((()",
        "()()()",
        "((((((",
        "",
    };
    for (const auto& expr : inputs)
    {
        cout << expr << ": " << maxLenMatchingParen(expr) << endl;
    }
    return 0;
}