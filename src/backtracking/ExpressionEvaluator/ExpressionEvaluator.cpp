#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <unordered_set>
using namespace std;

int evaluateExpression(const string& expr)
{
    string numStr;
    stack<int> numStack;
    stack<char> opStack;

    for (size_t i = 0; i < expr.size(); )
    {
        if (expr[i] >= '1' && expr[i] <= '9')
        {
            while (i < expr.size() && expr[i] >= '1' && expr[i] <= '9')
            {
                numStr += expr[i];
                i++;
            }
            numStack.push(stoi(numStr));
            numStr.clear();
        }
        else if (i < expr.size() && (expr[i] == '*' || expr[i] == '+'))
        {
            if (expr[i] == '+')
            {
                while (!opStack.empty() && opStack.top() == '*')
                {
                    int num1 = numStack.top();
                    numStack.pop();
                    int num2 = numStack.top();
                    numStack.pop();
                    
                    numStack.push(num1 * num2);
                    opStack.pop();
                }
            }
            opStack.push(expr[i]);
            i++;
        }
        else
        {
            i++;
        } 
    }

    if (opStack.empty())
    {
        return numStack.empty() ? 0 : numStack.top();
    }
    else
    {
        while (!opStack.empty())
        {
            if (numStack.size() < 2)
            {
                return 0;
            }

            int num1 = numStack.top();
            numStack.pop();
            int num2 = numStack.top();
            numStack.pop();
            
            if (opStack.top() == '*')
            {
                numStack.push(num1 * num2);
            }
            else if (opStack.top() == '+')
            {
                numStack.push(num1 + num2);
            }
            opStack.pop();
        }
    }
    return numStack.empty() ? 0 : numStack.top();
}

void _expressionCreator(const string& strDigits,
    int target,
    string& result,
    unordered_set<string>& results)
{
    if (strDigits.empty())
    {
        if (evaluateExpression(result) == target)
        {
            results.insert(result);
        }
        return;
    }

    for (size_t i = 0; i < strDigits.size(); ++i)
    {
        const string& prefix = strDigits.substr(0, i+1);

        // first do join
        result += prefix;
        _expressionCreator(strDigits.substr(i+1), target, result, results);
        result.erase(result.end()-prefix.size(), result.end());

        // next try *
        if (!result.empty())
        {
            result += "*";
            result += prefix;
            _expressionCreator(strDigits.substr(i+1), target, result, results);
            result.erase(result.end()-prefix.size(), result.end());
            result.pop_back();
        }
        
        // next try +
        if (!result.empty())
        {
            result += "+";
            result += prefix;
            _expressionCreator(strDigits.substr(i+1), target, result, results);
            result.erase(result.end()-prefix.size(), result.end());
            result.pop_back();
        }
    }
}

vector<string> expressionCreator(const string& strDigits, int target)
{
    string result;
    unordered_set<string> uniqueResults;

    _expressionCreator(strDigits, target, result, uniqueResults);
    vector<string> results(uniqueResults.begin(), uniqueResults.end());
    for (auto& str : results)
    {
        str += "=" + to_string(target);
    }
    return results;
}

int main()
{
    vector<pair<string, int>> inputs = {
        make_pair<string, int>("2", 2),
        make_pair<string, int>("222", 6),
        make_pair<string, int>("222", 8),
        make_pair<string, int>("222", 24),
        make_pair<string, int>("1234", 14),
        make_pair<string, int>("222", 222),
        make_pair<string, int>("2", 1), // invalid target, should result in 0 expressions
        make_pair<string, int>("34", 59), // invalid target, should result in 0 expressions
    };

    for (const auto& p : inputs)
    {
        const string& strDigits = p.first;
        int target = p.second;

        cout << "For the string " << strDigits << " and target " << target 
        << " the resulting expressions are " << endl;
        
        vector<string>results = expressionCreator(strDigits, target);
        for (const auto& result : results)
        {
            cout << result << endl;
        }    
    }
    return 0;
}