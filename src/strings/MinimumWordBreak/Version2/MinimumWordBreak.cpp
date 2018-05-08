// A simple program to find the largest subarray with equal number of 0s and 1s
#include <iostream>
#include <vector>
#include <string>
#include <utility>
using namespace std;

struct TrieNode 
{
    TrieNode *children[26] = { nullptr };
    bool isLeaf = false;
    static TrieNode* getTrieNode()
    {
        return new (std::nothrow) TrieNode();
    }
};

// prints the words in the input
void PrintWords(const vector<string>& words)
{
    for (size_t i = 0; i < words.size(); ++i)
    {
        cout << words[i];
        if (i != words.size() - 1)
        {
            cout << " ";
        }
    }
    cout << " (" << words.size() << ")";
    cout << endl;
}

// Inserts words into the trie
void Insert(TrieNode *root, const string& key)
{
    if (!root || key.empty())
    {
        return;
    }
    for (auto c : key)
    {
        auto index = c - 'a';
        if (!root->children[index])
        {
            root->children[index] = TrieNode::getTrieNode();
            if (!root->children[index]) { return; }
        }
        root = root->children[index];
    }
    root->isLeaf = true;
}

// Constructs the trie
TrieNode* ContructTrie(const vector<string>& dictionary)
{
	if (dictionary.empty()) { return nullptr; }

    TrieNode *root = TrieNode::getTrieNode();
    if (!root) { return nullptr; }

    for (const string& word : dictionary)
    {
        Insert(root, word);
    }
    return root;
}

// Detects if the specified word exists in the dictionary
bool IsValidWord(const TrieNode *root, const string& word)
{
    if (!root || word.empty()) { return false; }

    for (size_t i = 0; i < word.size(); ++i)
    {
        auto index = word[i] - 'a';
        if (!root->children[index]) { return false; }
        root = root->children[index];
    }
    return root->isLeaf;
}

// Breaks the given input string into appropriate words as specified in the dictionary
void _WordBreak(const TrieNode *root, const string& input, vector<string>& res, size_t& minCount)
{
    if (!root) { return; }
    else if (input.empty())
    {
        minCount = min(minCount, res.size());
        PrintWords(res);
        return;
    }

    for (size_t i = 0; i < input.size(); ++i)
    {
        const string& prefix = input.substr(0, i + 1);
        if (IsValidWord(root, prefix))
        {
        res.push_back(prefix);
        _WordBreak(root, input.substr(i+1), res, minCount);
        res.pop_back();
        }
    }
}

// Breaks the given input string into appropriate words as specified in the dictionary
size_t MinWordBreak(const vector<string>& dictionary, const string& input)
{
    TrieNode *root = ContructTrie(dictionary);
    if (!root || input.empty()) { return SIZE_MAX; }

    vector<string> result;
    size_t minCount = SIZE_MAX;
    _WordBreak(root, input, result, minCount);
    return minCount;
}

int main()
{
    vector<pair<vector<string>, string>> inputs = 
    {
        make_pair<vector<string>, string>(
        { "mobile", "samsung", "sam", "sung", "mango", "icecream", "and", "go", "i", "like", "ice", "cream"},
        "ilikesamsung"),
        make_pair<vector<string>, string>(
        { "mobile", "samsung", "sam", "sung", "mango", "icecream", "and", "go", "i", "like", "ice", "cream"},
        "icecream"),
        make_pair<vector<string>, string>(
        { "cat", "mat", "ca", "ma", "at", "c", "dog", "og", "do", "g"},
        "catmat"),
        make_pair<vector<string>, string>(
        { "cat", "mat", "ca", "ma", "at", "c", "dog", "og", "do", "g"}, 
        "dogmat"),
    };

    for (const auto& p : inputs)
    {
        const vector<string>& dictionary = p.first;
        const string& input = p.second;

        cout << "Word break for \"" << input << "\"" << endl;
        size_t minCount = MinWordBreak(dictionary, input);
        cout << "Min word break is " << minCount << endl << endl;
    }	
    return 0;
}
