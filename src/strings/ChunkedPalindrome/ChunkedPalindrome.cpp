#include <iostream>
#include <string>
#include <vector>
using namespace std;

// http://www.geeksforgeeks.org/longest-possible-chunked-palindrome/
size_t _ChunkedPalindrome(const string& str, size_t& low, size_t& high)
{
    if (str.empty() || low > high)
    {
        return 0;
    }
    else if (low == high)
    {
        return 1;
    }
    else if (low == high-1)
    {
        return str[low] == str[high] ? 2 : 1;
    }

    size_t start = low;
    size_t end = high;
    while (low < high)
    {
        const string& s1 = str.substr(start, low - start+1);
        const string& s2 = str.substr(high, end - high+1);
        if (!s1.empty() && !s2.empty() && s1 == s2)
        {
            low++;
            high--;
            return _ChunkedPalindrome(str, low, high) + 2;
        }
        else
        {
            low++;
            high--;    
        }
    }
    return 1;
}

size_t ChunkedPalindrome(const string& word)
{
    if (word.empty())
    {
        return 0;
    }
    
    size_t low = 0, high = word.size()-1;
    return _ChunkedPalindrome(word, low, high);
}

int main()
{
    const vector<string> inputs = 
    {
        "ghiabcdefhelloadamhelloabcdefghi",
        "abccab",
        "a",
        "ab",
        "aa",
        "merchant",
        "antaprezatepzapreanta",
        "geeksforgeeks",
        "randomrandom"
    };
    cout << endl << "Number of chunked palindromes: " << endl;
    for (const auto& word : inputs)
    {
        size_t count = ChunkedPalindrome(word);
        cout << word << ": " << count << endl;
    }
    cout << endl;
    return 0;
}