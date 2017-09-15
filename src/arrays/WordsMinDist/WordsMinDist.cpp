#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <utility>
#include <cmath>

using namespace std;

size_t GetMinDist(const vector<string>& words, const string& word1, const string& word2)
{
    if (words.empty())
    {
        return 0;
    }
    
    unordered_map<string, vector<size_t>> lookup;
    
    for (size_t i = 0; i < words.size(); ++i) 
    {
        const auto& word = words[i];
        lookup[word].push_back(i);
    }
    
    if (lookup.find(word1) == lookup.cend() || lookup.find(word2) == lookup.cend())
    {
        return SIZE_MAX;
    }
    
    // word1 and word2 exists
    const vector<size_t>& list1 = lookup[word1];    
    const vector<size_t>& list2 = lookup[word2];
    
    size_t minDist = SIZE_MAX;
    
    auto pos1 = list1.begin();
    auto pos2 = list2.begin();

    while (pos1 != list1.end() && pos2 != list2.end())
    {
        //auto dist = abs(*pos1 - *pos2);
        size_t dist = 0;
        int temp = *pos1 - *pos2;
        if (temp < 0) { dist = -1 * temp; }
        else { dist = temp; }

        minDist = min(dist, minDist);
        
        if (*pos1 < *pos2) 
        {
            pos1++;
        }
        else
        {
            pos2++;
        }
    }
    return minDist;
} 
          

int main()
{
    vector <pair<vector<string>, pair<string, string>>> inputs = 
    { 
        make_pair<vector<string>, pair<string, string>>
        (
            {""},
            make_pair<string, string>("", "")
        ),

        make_pair<vector<string>, pair<string, string>>
        (
            {"the", "quick", "brown", "fox", "quick"},
            make_pair<string, string>("the", "fox")
        ),
    };

    for (const auto keyvaluepair : inputs)
    {
        const auto& words = keyvaluepair.first;
        const auto& word1 = keyvaluepair.second.first;
        const auto& word2 = keyvaluepair.second.second;

        cout << "For the words: ";
        for (const auto& i : words)
        {
            cout << i << " ";
        }
        cout << endl;
        auto minDist = GetMinDist(words, word1, word2);
        cout << "the min dist between " << word1 << " and " << word2 << " is " << minDist << endl;
    }
    return 0;
}