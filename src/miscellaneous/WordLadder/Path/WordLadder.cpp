#include <iostream>
#include <vector>
#include <unordered_set>
#include <string>
#include <queue>
using namespace std;

// https://leetcode.com/problems/word-ladder-ii/description/
// Given two words (beginWord and endWord), and a dictionary's word list, 
// find the length of shortest transformation sequence from beginWord to endWord, such that:
// 1) Only one letter can be changed at a time.
// 2) Each transformed word must exist in the word list. Note that beginWord is not a transformed word.
//
// Input:
// beginWord = "hit",
// endWord = "cog",
// wordList = ["hot","dot","dog","lot","log","cog"]
// Output:
// [
//   ["hit","hot","dot","dog","cog"],
//   ["hit","hot","lot","log","cog"]
// ]

static vector<string> addWords(string& word, const unordered_set<string>& dict)
{
    vector<string> results;
    for (size_t i = 0; i < word.size(); ++i)
    {
        char s = word[i];
        for (char c = 'a'; c <= 'z'; ++c)
        {
            word[i] = c;
            if (dict.find(word) != dict.cend())
            {
                results.push_back(word);
            }
        }
        word[i] = s;
    }
    return results;
}

vector<vector<string>> WordLadder(const string& start, const string& end, const vector<string>& wordsList)
{
    if (start.empty() || end.empty() || wordsList.empty()) { return {{}}; }

    vector<vector<string>> results;
    unordered_set<string> visited;
    unordered_set<string> dict(wordsList.begin(), wordsList.end());
    queue<vector<string>> q;
    bool foundPath = false;

    q.push({start});
    while (!q.empty())
    {
        size_t size = q.size();
        for (size_t i = 0; i < size; ++i)
        {
            vector<string> currentList = move(q.front());
            q.pop();
            vector<string> newWordsList = addWords(currentList.back(), dict);
            for (size_t j = 0; j < newWordsList.size(); ++j)
            {
                vector<string> updatedList = currentList;
                updatedList.push_back(newWordsList[j]);
                if (newWordsList[j] == end)
                {
                    foundPath = true;
                    results.push_back(updatedList);
                }
                visited.insert(newWordsList[j]);
                q.push(updatedList);
            }
        }
        if (foundPath)
        {
            break;
        }
        for (auto it = visited.begin(); it != visited.end(); ++it)
        {
            dict.erase(*it);
        }
        visited.clear();
    }
    return results;
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

    cout << "Word ladder for the inputs" << endl;
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
            if (i != wordsList.size() - 1)
            {
                cout << ", ";
            }
        }
        cout << "]" << endl;
        vector<vector<string>> paths = WordLadder(start, end, wordsList);
        if (!paths.empty())
        {
            for (size_t i = 0; i < paths.size(); ++i)
            {
                cout << i+1 << ") [";
                for (size_t j = 0; j < paths[i].size(); ++j)
                {
                    cout << paths[i][j];
                    if (j != paths[i].size() - 1) { cout << ", "; }
                }
                cout << "]" << endl;
            }
            cout << endl;
        }
        else { cout << "[ ]" << endl << endl; }
    }
    return 0;
}