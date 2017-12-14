// http://www.geeksforgeeks.org/maximum-length-substring-having-all-same-characters-after-k-changes/
// k = changes you can make
// Input : k = 2
// str = ababa
// Output : maximum length = 5
// which will be (aaaaa)

#include <iostream>
#include <string>
#include <utility>
#include <vector>
using namespace std;

size_t _MaxLengthSubstringSameCharactersAfterKChanges(const string& s, size_t k, char ch)
{
    if (s.empty() || k == 0)
    {
        return 0;
    }

    size_t l = 0, r = 0;
    size_t count = 0, maxLen = 0;
    size_t n = s.size();

    while (r < n)
    {
        if (s[r] != ch)
        {
            ++count;
        }

        while (count > k)
        {
            if (s[l] != ch)
            {
                --count;
            }
            ++l;
        }
        
        maxLen = max(maxLen, r-l+1);
        ++r;
    }

    return maxLen;
}
size_t MaxLengthSubstringSameCharactersAfterKChanges(const string& s, size_t k)
{
    if (s.empty() || k == 0)
    {
        return 0;
    }

    size_t maxLen = 0;
    for (size_t i = 0; i < 26; ++i)
    {
        maxLen = max(maxLen, _MaxLengthSubstringSameCharactersAfterKChanges(s, k, 'a' + i));
    }
    return maxLen;
}

int main()
{
    vector<pair<string, size_t>> inputs = 
    {
        make_pair<string, size_t>("ababa", 2),
        make_pair<string, size_t>("ababa", 1),
        make_pair<string, size_t>("a", 1),
        make_pair<string, size_t>("ab", 1),
        make_pair<string, size_t>("abcdef", 3),
        make_pair<string, size_t>("aaaaaa", 1),
        make_pair<string, size_t>("ababa", 6),
        make_pair<string, size_t>("ababa", 0),
    };

    for (const auto& p : inputs)
    {
        const string& s = p.first;
        size_t k = p.second;

        cout << "For the string " << "\"" << s  << "\"" << " and number of changes allowed = " << k << endl;
        
        size_t maxLen = MaxLengthSubstringSameCharactersAfterKChanges(s, k);
        cout << "the maximum length of the substring having same characters is " << maxLen << endl << endl;
    }
    return 0;
}