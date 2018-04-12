#include <iostream>
#include <vector>
#include <unordered_set>
#include <string>
#include <queue>
using namespace std;

// Given two words (beginWord and endWord), and a dictionary's word list, find all
// shortest transformation sequence(s) from beginWord to endWord, such that
// . Only one letter can be changed at a time
// . Each transformed word must exist in the word list. Note that beginWord is not a transformed word
// beginWord = "hit"
// endWord = "cog"
// wordList = {"hot","dot","dog","lot","log","cog"}
// {"hit","hot","dot","dog","cog"}
// {"hit","hot","lot","log","cog"}
//
vector<string> addWords(string& word, const unordered_set<string>& dict)
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

vector<vector<string>> WordLadder(string& start, string& end, const vector<string>& wordsList)
{
    if (start.empty() || end.empty() || wordsList.empty())
    {
        return {{}};
    }

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
    vector<string> wordsList = 
    {
        "hot", "dot", "dog", "lot", "log", "cog",
    };
    cout << "For the dictionary: ";
    for (const auto& word : wordsList)
    {
        cout << word << " ";
    }
    
    vector<pair<string, string>> inputs =
    {
        {"hit", "cog"},
    };
    cout << endl;
    for (const auto& p : inputs)
    {
        cout << "Transforming from " << "\"" << p.first << "\"" << " to " 
        << "\"" << p.second << "\"" << " is as follows:" << endl;
        string start = p.first;
        string end = p.second;
        vector<vector<string>> results = WordLadder(start, end, wordsList);
        for (const auto& result : results)
        {
            for (size_t i = 0; i < result.size(); ++i)
            {
                cout << result[i];
                if (i != result.size() - 1) { cout << " -> "; }
            }
            cout << endl;
        }
    }
    return 0;
}