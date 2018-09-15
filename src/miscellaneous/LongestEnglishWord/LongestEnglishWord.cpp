#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
using namespace std;

// Todo: can optimze by memoizing
bool _getLongestWord(const unordered_set<string>& periodicTable, string word)
{
    if (word.empty())
    {
        return true;
    }
    else if (word.size() == 1)
    {
        return periodicTable.find(string(1, word[0])) != periodicTable.cend();
    }
    else if (word.size() == 2)
    {
        return periodicTable.find(word) != periodicTable.cend();
    }
    
    if (!periodicTable.count(string(1, word[0])) && !periodicTable.count(word.substr(0, 2)))
    {
        return false;    
    }
    
    if (periodicTable.count(string(1, word[0])))
    {
        if (_getLongestWord(periodicTable, word.substr(1)))
        {
            return true;
        }
    }
    
    if (periodicTable.count(word.substr(0, 2)))
    {
        if (_getLongestWord(periodicTable, word.substr(2)))
        {
            return true;
        }
    }
    
    return false;
}

string getLongestWord(const vector<string>& dictionary, const unordered_set<string>& periodicTable)
{
    if (dictionary.empty() || periodicTable.empty())
    {
        return "";
    }
    
    // Assume the dictonary is sorted by longest word to shortest
    for (auto temp : dictionary)
    {
        string word = temp;
        if (_getLongestWord(periodicTable, word))
        {
            return word;
        }
    }
    return "";
}

int main() {
    
    // Todo, add more test cases
    const vector<string> dictionary = { "abcde", "abcd", "ab" };
    const unordered_set<string> periodic = {"a", "b", "bc", "d", "e"};
    string result = getLongestWord(dictionary, periodic);
    cout << "Longest word is: " << result << endl;
    return 0;
}
