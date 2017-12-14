// Minimum rotations required to get the same string
#include <iostream>
#include <string>
#include <vector>
using namespace std;

size_t MiniumRotations(const string& s)
{
    if (s.size() <= 2)
    {
        return s.size();
    }
    return (s+s).substr(1).find(s) + 1;
}

int main()
{
    vector<string> inputs = 
    {
        "bcaa",
        "aba",
        "abab",
        "aabb",
        "aaaaa",
        "abcde",
        "a",
    };

    for (const auto& str : inputs)
    {
        cout << "The minimum number of rotations to get the same for " << str 
        << " is " << MiniumRotations(str) << endl;
    }
    return 0;
}