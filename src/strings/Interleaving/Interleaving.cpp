// C++ program to implement multiplicative order
#include <iostream>
#include <string>
using namespace std;

// Given two strings prints all interleavings
void _StringInterleave(const string& s1, const string& s2, string& result)
{
    if (s1.empty() && s2.empty())
    {
        if (!result.empty())
        {
            cout << result << endl;
        }
        return;
    }

    if (!s1.empty())
    {
        result.push_back(s1[0]);
        _StringInterleave(s1.substr(1), s2, result);
        result.pop_back();
    }
    if (!s2.empty())
    {
        result.push_back(s2[0]);
        _StringInterleave(s1, s2.substr(1), result);
        result.pop_back();
    }
}

void StringInterleave(const string& s1, const string& s2)
{
    string result;
    cout << "String interleavings for " << s1 << " and " << s2 << endl;
    return _StringInterleave(s1, s2, result);
}

//driver program to test above function
int main()
{
	string s1 = "AB";
	string s2 = "CD";
	StringInterleave(s1, s2);
	return 0;
}
