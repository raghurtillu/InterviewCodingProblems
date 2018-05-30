#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>
using namespace std;

// https://leetcode.com/problems/word-ladder/description/
// Given two words (beginWord and endWord), and a dictionary's word list, 
// find the length of shortest transformation sequence from beginWord to endWord, such that:
// 1) Only one letter can be changed at a time.
// 2) Each transformed word must exist in the word list. Note that beginWord is not a transformed word.
//
// Input:
// beginWord = "hit",
// endWord = "cog",
// wordList = ["hot","dot","dog","lot","log","cog"]
// Output: 5
// Explanation: As one shortest transformation is "hit" -> "hot" -> "dot" -> "dog" -> "cog",
// return its length 5.

static vector<string> addWords(string& word, const unordered_set<string>& dict)
{
    if (word.empty() || dict.empty()) { return {}; }
    
    vector<string> newWords;
    for (size_t i = 0; i < word.size(); ++i)
    {
        char s = word[i];
        for (char c = 'a'; c <= 'z'; ++c)
        {
            word[i] = c;
            if (dict.find(word) != dict.cend())
            {
                newWords.push_back(word);
            }
        }
        word[i] = s;
    }
    return newWords;
}

int LadderLength(const string& start, const string& end, const vector<string>& wordList) 
{
    if (start.empty() || end.empty() || wordList.empty()) { return 0; }
    
    unordered_set<string> visited;
    unordered_set<string> dict(wordList.begin(), wordList.end());
    
    size_t pathLen = 1;
    bool foundPath = false;
    
    static string delimiter = "";
    // using empty string as a delimiter
    queue<string> q;
    q.push(start);
    q.push(delimiter);
    while (!q.empty())
    {
        auto word = move(q.front());
        q.pop();
        if (word != delimiter)
        {
            vector<string> newWords = addWords(word, dict);
            for (size_t i = 0; i < newWords.size(); ++i)
            {
                if (newWords[i] == end)
                {
                    ++pathLen;
                    foundPath = true;
                    break;
                }
                q.push(newWords[i]);
                visited.insert(newWords[i]);
            }    
        }
        else
        {
            // delimiter
            ++pathLen;
            if (!q.empty() && q.front() != delimiter)
            {
                q.push(delimiter);
            }
        }
        if (foundPath) { break; }
        
        for (auto it = visited.begin(); it != visited.end(); ++it)
        {
            dict.erase(*it);
        }
        visited.clear();
    }   // end of while
    return foundPath ? pathLen : 0;
}
int main() 
{
    struct Element
    {
        string start;
        string end;
        vector<string> wordsList;
        Element(const string& _start, const string& _end, const vector<string>& _wordsList) :
            start(_start), end(_end), wordsList(_wordsList)
        {}
    };
    
    vector<Element> inputs = 
    {
        Element("hit", "cog", {"hot", "dot", "dog", "lot", "log", "cog"}),
        Element("hit", "cog", {"hot", "dot", "dog", "lot", "log"}),
    };

    cout << "Word ladder length for the inputs" << endl;

    for (const auto& input : inputs)
    {
        const auto& start = input.start;
        const auto& end = input.end;
        const auto& wordsList = input.wordsList;
        cout << "Start word: " << start << endl;
        cout << "End word: " << end << endl;
        cout << "Words list: [";
        for (size_t i = 0; i < wordsList.size(); ++i)
        {
            cout << wordsList[i];
            if (i != wordsList.size() - 1) { cout << ", "; }
        }
        cout << "]" << endl;
        cout << "Ladder length: " << LadderLength(start, end, wordsList) << endl << endl;
    }
    return 0;
}