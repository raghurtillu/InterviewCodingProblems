#include <iostream>
#include <vector>
using namespace std;

bool isMatch(const string& str, const string& pattern) 
{
    if (str.empty() && pattern.empty())
    {
        return true;
    }
    else if (pattern.size() >= 2 && pattern[0] == '*' && pattern[1] != '*' && str.empty())
    {
        return false;
    }
    else if (!str.empty() && !pattern.empty() && (pattern[0] == '.' || pattern[0] == str[0]))
    {
        return isMatch(str.substr(1), pattern.substr(1));
    }
    else if (!str.empty() && !pattern.empty() && pattern[0] == '*')
    {
        return isMatch(str.substr(1), pattern) || 
            isMatch(str, pattern.substr(1)) ||
            isMatch(str.substr(1), pattern.substr(1));
    }
    return false;
}

int main()
{
    vector<pair<string, string>> inputs = 
    {
        make_pair<string, string>("aaaaaa", ".a*"),
        make_pair<string, string>("aaaaaa", ".a*"),
        make_pair<string, string>("geeks", "g*ks"),
        make_pair<string, string>("kickstart", "hungry"),
        make_pair<string, string>("abbbcccccd", "a*b*c*d"),
        make_pair<string, string>("abcd", "abcd")
    };

    for (const auto& p : inputs)
    {
        const string& str = p.first;
        const string& pattern = p.second;

        cout << "For the text: " << "\"" << str << "\"" << ", the pattern: " << "\"" << pattern << "\"";
        bool res = isMatch(str, pattern);
        if (res)
        {
            cout << ", is a match" << endl;
        }
        else
        {
            cout << ", is not a match" << endl;
        }
    }
    return 0;
}