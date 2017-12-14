// Find numbers of balancing positions in string, the frequency of characters doesn’t matter
// Input : str[] = abaaba
// Output : Number of balancing positions : 3
// Explanations : All 3 balancing positions are as :
// ab|aaba, aba|aba, abaa|ba

// Input : str[] = noon
// Output : Number of balancing positions : 1
// Explanations : Balancing position is :
// no|on

#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<size_t> NumberOfBalancingPositions(const string& s)
{
    if (s.empty())
    {
        return vector<size_t>();
    }

    size_t leftVisited[26] = { 0 };
    size_t rightVisited[26] = { 0 };

    for (auto c : s)
    {
        rightVisited[c-'a']++;
    }

    vector<size_t> positions;
    for (size_t i = 0; i < s.size(); ++i)
    {
        leftVisited[s[i]-'a']++;
        rightVisited[s[i]-'a']--;

        size_t j = 0;
        for (j = 0; j < 26; ++j)
        {
            if ((leftVisited[j] == 0 && rightVisited[j] != 0) ||
                (leftVisited[j] != 0 && rightVisited[j] == 0))
            {
                break;
            }
        }
        if (j == 26)
        {
            positions.push_back(i+1);
        }
    }
    return positions;
}

void PrintStringWithBalancedPositions(const string& s, const vector<size_t>& positions)
{
    if (s.empty() || positions.empty())
    {
        return;
    }

    for (size_t pos : positions)
    {
        if (pos >= s.size()) { continue; }
        for (size_t i = 0; i < s.size(); ++i)
        {
            if (i == pos)
            {
                cout << "|";
            }
            cout << s[i];
        }
        cout << "\t";
    }
}

int main()
{
    vector<string> inputs = 
    {
        "abaaba",
        "noon",
        "abaababa",
    };

    for (const auto& str : inputs)
    {
        cout << "For the string " << str << " the balancing positions are at: ";
        vector<size_t> positions = NumberOfBalancingPositions(str);
        cout << "{";
        for (size_t i = 0; i < positions.size(); ++i)
        {
            cout << positions[i];
            if (i != positions.size()-1)
            {
                cout << ", ";
            }
        }
        cout << "}";
        cout << endl;
        PrintStringWithBalancedPositions(str, positions);
        cout << endl << endl;
    }

    return 0;
}