#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

// Given three strings a, b and c, determine if a is an interleave of a and b. 
// c is said to be interleave of a and b, if it contains all characters of a and b and order 
// of all characters in the individual strings is preserved

bool dfs(const string& s1, const string& s2, const string& s3,
    size_t i, size_t j, size_t k, unordered_map<size_t, size_t>& lookup)
{
    if (lookup.find(i) != lookup.cend() && lookup[i] == j) 
    {
        return false;
    }
    else if (k >= s3.size())
    {
        return true;
    }

    bool res = false;
    if (i < s1.size() && s1[i] == s3[k])
    {
        res = dfs(s1, s2, s3, i + 1, j, k + 1, lookup);
    }
    if (!res && j < s2.size() && s2[j] == s3[k])
    {
        res = dfs(s1, s2, s3, i, j + 1, k + 1, lookup);
    }
    if (!res)
    {
        lookup[i] = j;
    }
    return res;
}

bool isInterleave(const string& s1, const string& s2, const string& s3)
{
    if (s1.size() + s2.size() != s3.size())
    {
        return false;
    }
    size_t i = 0, j = 0, k = 0;  
    unordered_map<size_t, size_t> lookup;
    return dfs(s1, s2, s3, i, j, k, lookup);
}
int main()
{
    vector<vector<string>> inputs = 
    {
        {"aa", "ab", "abaa"},
        {"xxy", "xxz", "xxzxxxy"},
        {"ab", "cd", "cdab"},
        {"ab", "a", "aab"},
        {"yx", "x", "xxy"},
        {"aab", "aac", "aaaacb"},
    };
    cout << "Is string interleave: " << endl;
    for (const auto& input : inputs)
    {
        if (input.size() != 3) { continue; }
        const string& s1 = input[0];
        const string& s2 = input[1];
        const string& s3 = input[2];
        bool res = isInterleave(s1, s2, s3);
        
        cout << s3 << " is";
        res ? cout << " an " : cout << " not an ";
        cout << "interleave between " << s1 << " and " << s2 << endl;
    }
    return 0;
}
