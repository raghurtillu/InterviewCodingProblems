#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// Input : str = geeksforgeeks, k = 3
// Output : r
// First non-repeating character is f, second is o and third is r.

// Input : str = geeksforgeeks, k = 2
// Output : o

// Input : str = geeksforgeeks, k = 4
// Output : Less than k non-repeating characters in input.

// this method assumes the english alphabet and all the characters in the string are lower case
char KthNonRepeatingCharacter(const string& str, size_t k)
{
    if (str.empty() || k <= 0 || k > str.size() || k > 26)
    {
        return '\0';
    }

    struct CountIndex
    {
        size_t index = SIZE_MAX;
        size_t freq = 0;

        bool operator< (const CountIndex& rhs) const
        {
            if (this->freq == 0 || rhs.freq == 0)
            {
                return this->index < rhs.index;
            }
            else if (this->freq == 1 && rhs.freq == 1)
            {
                return this->index < rhs.index;
            }
            else
            {
                return this->freq < rhs.freq && this->index < rhs.index;
            }
        }
    };

    vector<CountIndex> ci(26);
    for (size_t i = 0; i < str.size(); ++i)
    {
        auto j = str[i] - 'a';
        ++ci[j].freq;
        if (ci[j].freq == 1)
        {
            ci[j].index = i;
        }
        else
        {
            ci[j].index = SIZE_MAX;
        }
    }

    sort(ci.begin(), ci.end());
    size_t kthIndex = ci[k-1].index;

    return (kthIndex != SIZE_MAX) ? str[kthIndex] : '\0';
}

int main()
{
    vector<pair<string, size_t>> inputs
    {
        make_pair<string, size_t>("geeksforgeeks", 1),
        make_pair<string, size_t>("geeksforgeeks", 2),
        make_pair<string, size_t>("geeksforgeeks", 3),
        make_pair<string, size_t>("geeksforgeeks", 4),
    };

    for (const auto& p : inputs)
    {
        const string& str = p.first;
        size_t k = p.second;

        cout << "For the string: " << str << " the " << k << " non repeating character is: ";
        char c = KthNonRepeatingCharacter(str, k);
        if (c != '\0')
        {
            cout << c;
        }
        else
        {
            cout << "Not available";
        }
        cout << endl;
    }
    return 0;
}