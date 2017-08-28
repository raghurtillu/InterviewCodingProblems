#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// This version has O(n2logn) complexity
void PrintLexicographicallySmallestRotatedSequence(const string& s)
{
    if (s.empty())
    {
        return;
    }

    const string& temp = s + s;
    vector<string> rotations(s.size());

    // generate different rotations of the string
    for (size_t i = 0; i < s.size(); ++i)
    {
        rotations[i] = temp.substr(i, s.size());
    }

    // sort the rotated sequences, the first entry is the smallest rotated sequence
    sort(rotations.begin(), rotations.end());
    cout << rotations[0];
}

// Driver program to test above function
int main()
{
    const vector<string> inputs = {
        "geeksforgeeks",
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