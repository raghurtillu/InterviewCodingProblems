#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

// Given three strings a, b and c, determine if a is an interleave of a and b. 
// c is said to be interleave of a and b, if it contains all characters of a and b and order 
// of all characters in the individual strings is preserved

struct Element
{
    size_t x = 0, y = 0, z = 0;

    Element(size_t _x, size_t _y, size_t _z) : x(_x), y(_y), z(_z)
    {}
    Element() = default;
    Element& operator= (const Element& ) = default;
    bool operator== (const Element &rhs) const
    {
        return x == rhs.x && y == rhs.y && z == rhs.z;
    }
};
struct ElementHash
{
    size_t operator()(const Element& key) const
    {
        return std::hash<size_t>()(key.x) ^ std::hash<size_t>()(key.y) ^ std::hash<size_t>()(key.z);
    }
};

bool _isInterleave(const string& s1, const string& s2, const string& s3,
    size_t i, size_t j, size_t k, 
    unordered_map<Element, bool, ElementHash>& lookup)
{
    if (i > s1.size() || j > s2.size() || k > s3.size())
    {
        return false;
    }
    else if (i == s1.size() && j == s2.size() && k == s3.size())
    {
        return true;
    }
    else if (lookup.find(Element(i, j, k)) != lookup.cend())
    {
        return lookup[Element(i, j, k)];
    }

    Element e(i, j, k);
    bool res = false;
    if (i < s1.size() && s1[i] == s3[k])
    {
        res = _isInterleave(s1, s2, s3, i + 1, j, k + 1, lookup);
    }
    if (!res && j < s2.size() && s2[j] == s3[k])
    {
        res = _isInterleave(s1, s2, s3, i, j + 1, k + 1, lookup);
    }
    lookup[e] = res;
    return lookup[e];
}

bool isInterleave(const string& s1, const string& s2, const string& s3)
{
    if (s1.size() + s2.size() != s3.size())
    {
        return false;
    }
    size_t i = 0, j = 0, k = 0;
    unordered_map<Element, bool, ElementHash> lookup;
    return _isInterleave(s1, s2, s3, i, j, k, lookup);
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
