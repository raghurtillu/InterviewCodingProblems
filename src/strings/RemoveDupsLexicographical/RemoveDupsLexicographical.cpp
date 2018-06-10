#include <iostream>
#include <string>
#include <vector>
using namespace std;
// https://leetcode.com/problems/remove-duplicate-letters/description/
// Given a string which contains only lowercase letters, remove duplicate letters
// so that every letter appear once and only once. You must make sure your result is the 
// smallest in lexicographical order among all possible results.
//
// Input: "bcabc"
// Output: "abc"
//
// Input: "cbacdcbc"
// Output: "acdb"

string RemoveDups(const string& input)
{
    if (input.size() <= 1) { return input; }
    vector<size_t> freq(256, 0);
    vector<bool> visited(256, false);
    
    for (auto c : input)
    {
        freq[c]++;
    }
    
    string res = "0";
    for (auto c : input)
    {
        freq[c]--;
        if (visited[c]) { continue; }
        while (c < res.back() && freq[res.back()])
        {
            visited[res.back()] = false;
            res.pop_back();
        }
        visited[c] = true;
        res.push_back(c);
    }
    return res.substr(1);
}

int main()
{
    vector<string> inputs =
    {
        "bcabc",
        "cbacdcbc",
        "abc",
    };
    
    cout << "Strings after removing dups and having smallest lexicographical ordering" << endl;
    for (const auto& input : inputs)
    {
        cout << input << ": " << RemoveDups(input) << endl;
    }
    return 0;
}
