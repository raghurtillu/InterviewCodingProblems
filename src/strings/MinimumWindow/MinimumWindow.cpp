#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Given a string S and a string T, find the minimum window in S which will contain all the characters in T
// S = "ayzabobecodxbanc"
// T = "abc"
// Minimum window is "banc", which contains all the letters a, b and c

// this method assumes all the characters in the strings are lower case and is in the english alphabet
// characters in pattern must be distinct
string MinimumWindow(const string& text, const string& pattern)
{
    size_t n = text.size();
    size_t m = pattern.size();

    if (n == 0 || m == 0 || m > n)
    {
        return "";
    }

    size_t textHash[26] = { 0 };
    size_t patternHash[26] = { 0 };

    for (auto i : pattern)
    {
        ++patternHash[i - 'a'];
    }
    size_t count = 0;
    size_t start = 0, startIndex = 0, wLen = SIZE_MAX;

    for (size_t i = 0; i < n; ++i)
    {
        auto index = text[i] - 'a';
        ++textHash[index];
        if (patternHash[index] != 0 && textHash[index] <= patternHash[index])
        {
            ++count;
        }
        if (count == m)
        {
            while (patternHash[text[start] - 'a'] == 0 || 
                textHash[text[start] - 'a'] > patternHash[text[start] - 'a'])
            {
                if (textHash[text[start] - 'a'] > patternHash[text[start] - 'a'])
                {
                    --textHash[text[start] - 'a'];
                }
                ++start;
            }
            if (i - start + 1 < wLen)
            {
                startIndex = start;
                wLen = i - start + 1;
            }
        }
    }
    return (wLen != SIZE_MAX) ? text.substr(startIndex, wLen) : "";
}

int main()
{
    vector<pair<string, string>> inputs = 
    {
        make_pair<string, string>("ayzabobecodxbanc", "abc"),
        make_pair<string, string>("this is a test string", "tist"),
        make_pair<string, string>("a phoenix is a bird", "phx"),
    };

    for (const auto& p : inputs)
    {
        const string& text = p.first;
        const string& pattern = p.second;

        cout << "For the input: " << "\"" << text << "\"" 
        << ", the minimum window containing all the characters of " 
        << "\"" << pattern << "\"" << " are " << endl;

        cout << MinimumWindow(text, pattern) << endl << endl;
    }
    return 0;
}