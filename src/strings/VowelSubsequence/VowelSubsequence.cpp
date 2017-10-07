#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
using namespace std;

bool isVowel(char c)
{
    static const unordered_set<char> vowels = {'a', 'e', 'i', 'o', 'u'};
    return vowels.find(c) != vowels.cend();
}

void Subsequences(const string& s, unordered_set<string>& res)
{
    if (s.empty())
    {
        return;
    }
    for (size_t i = 0; i < s.size(); ++i)
    {
        if (!isVowel(s[i])) { continue; }
        
        for (size_t j = s.size()-1; j > i; --j)
        {
            if (isVowel(s[j])) { continue; }

            string val = s.substr(i, j-i+1);
            res.insert(val);
            
            for (size_t k = 0; k < val.size(); ++k)
            {
                string temp = val;
                Subsequences(temp.erase(k, 1), res);
            }
        }
    }
}

int main()
{
    const vector<string> inputs = {
        "xabcef",
    };

    cout << "Vowel and consonant subsequences" << endl;
    for (const auto& word : inputs)
    {
        unordered_set<string> res;
        Subsequences(word, res);
        cout << word << ": ";
        for (const auto& val : res)
        {
            cout << val << " ";
        }
        cout << endl;
    }
    //cout << endl;
    return 0;
}