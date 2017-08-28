#include <iostream>
#include <limits>
#include <string>
#include <vector>

using namespace std;

// This version has O(n2) complexity

// Compares two sequences with different starting indexes
// Returns true if sequence beginning with y is lexicographically smaller
bool CompareSequence(const string& s, size_t x, size_t y)
{
    if (s.empty() || x >= s.size() || y >= s.size())
    {
        return false;
    }

    size_t n = s.size();
    for (size_t i = 0; i < n; ++i)
    {
        if (s[x] < s[y])
        {
            return false;
        }
        else if (s[y] < s[x])
        {
            return true;
        }
        x = (x + 1) % n;
        y = (y + 1) % n;
    }
    return false;
}

// Finds the starting index of lexicographically smallest sequence
size_t FindSmallestSequence(const string& s)
{
    if (s.empty())
    {
        return SIZE_MAX;
    }
    
    size_t startIndex = 0;
    for (size_t i = 1; i < s.size(); ++i)
    {
        if (CompareSequence(s, startIndex, i))
        {
            startIndex = i;
        }
    }
    return startIndex;
}

void PrintLexicographicallySmallestRotatedSequence(const string& s)
{
    if (s.empty())
    {
        return;
    }
    size_t startIndex = FindSmallestSequence(s);
    if (startIndex == SIZE_MAX)
    {
        return;
    }

    size_t n = s.size();
    for (size_t i = 0; i < n; ++i)
    {
        // print the characters in the string starting from the smallext sequence index
        cout << s[(startIndex + i) % n];
    }
}
// Driver program to test above function
int main()
{
    const vector<string> inputs = {
        "geeksforgeeks"
        "geeksquiz",
        "bcabdadab",
    };

    cout << "Lexicographically smallest rotated sequences " << endl;
    for (const auto& word : inputs)
    {
        cout << word << ": ";
        PrintLexicographicallySmallestRotatedSequence(word);
        cout << endl;
    }

    return 0;
}