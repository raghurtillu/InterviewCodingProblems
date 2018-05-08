#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
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

void insert(TrieNode *root, const string& key)
{
    if (!root || key.empty()) { return; }

    for (auto c : key)
    {
        auto index = c - 'a';
        if (!root->children[index])
        {
            root->children[index] = TrieNode::getTrieNode();
        }
        root = root->children[index];
    }
    root->isLeaf = true;
}

void wordBreak(const TrieNode *root, const string& key, size_t start, size_t& minCount, size_t count)
{
    if (!root || key.empty() || start > key.size())
    {
        return;
    }
    else if (start == key.size())
    {
        minCount = min(minCount, count);
        return;
    }

    const TrieNode *pCrawl = root;
    for (size_t i = start; i < key.size(); ++i)
    {
        auto index = key[i] - 'a';
        if (!pCrawl->children[index])
        {
            return;
        }
        else if (pCrawl->children[index]->isLeaf)
        {
            wordBreak(root, key, i + 1, minCount, count + 1);
        }
        pCrawl = pCrawl->children[index];
    }
}

size_t minWordBreak(const TrieNode* root, const string& key)
{
    if (!root || key.empty())
    {
        return 0;
    }
    
    size_t start = 0, minCount = SIZE_MAX, count = 0;

    wordBreak(root, key, start, minCount, count);
    return minCount;
}

int main()
{
    const vector<string> dictionary = 
    { 
        "cat", "mat", "ca", "ma", "at", "c", "dog", "og", "do"
    };

    TrieNode *root = TrieNode::getTrieNode();
    if (!root) { return 1; }

    for (const auto& word : dictionary)
    {
        insert(root, word);
    }

    string key = "catmat";
    minWordBreak(root, key);

    return 0;
}
