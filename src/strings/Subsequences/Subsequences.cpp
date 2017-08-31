// C++ program to print all subsequences of a string b
// beginning with a vowel and ending with a consonant
#include <iostream>
#include <string>
#include <unordered_set>

using namespace std;

static bool isVowel(char c)
{
    static const unordered_set<char> vowels = {
        'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'
    };
    return vowels.find(c) != vowels.cend();
}

static bool isConsonant(char c)
{
    return !isVowel(c);
}

void _subsequence(const string& s, unordered_set<string>& results)
{
    if (s.empty())
    {
        return;
    }

    for (size_t i = 0; i < s.size(); ++i)
    {
        if (isConsonant(s[i]))
        {
            continue;
        }
        // s[i] is a vowel

        // find the index from reverse for a consonant character
        for (size_t j = s.size() - 1; j > i; --j)
        {
            if (isVowel(s[j]))
            {
                continue;
            }

            // found a substring beginning with a vowel and ending with a consonant
            const string& res = s.substr(i, j-i+1);
            if (res.empty())
            {
                // if the substring is empty; nothing to do
                continue;
            }

            results.insert(res);
            
            // recurse over the obtained substring by generating different subsequences,
            // as in remove characters at different positions
            for (size_t k = 0; k < res.size(); ++k)
            {
                string temp = res;
                temp.erase(k, 1);
                if (!temp.empty())
                {
                    _subsequence(temp, results);
                }
            } // end of inner most for
        } // end of inner for
    } // end of outer for
}

void subsequence(const string& s)
{
    unordered_set<string> results;
    _subsequence(s, results);
    
    cout << "For the string " << s << " the subsequences beginning with a vowel"
    << " and ending with a consonant are as follows: " << endl;
    for (const auto it: results) 
    {
        cout << it << endl;
    }
}

int main() 
{
	const string s = "xabcef";
	subsequence(s);
	return 0;
}