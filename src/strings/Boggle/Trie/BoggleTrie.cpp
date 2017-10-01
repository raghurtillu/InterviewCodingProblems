// C++ program for Boggle game
#include <iostream>
#include <vector>
using namespace std;

static const int ROWS = 3;
static const int COLS = 3;

struct TrieNode
{
    TrieNode *children[26] = { nullptr };
    bool isLeaf = false;
};

TrieNode* getNode()
{
    return new(std::nothrow) TrieNode();    
}

void insert(TrieNode *root, const string& key)
{
    if (!root || key.empty())
    {
        return;
    }
    for (size_t i = 0; i < key.size(); ++i)
    {
        auto index = key[i] - 'a';
        if (!root->children[index])
        {
            root->children[index] = getNode();
        }
        root = root->children[index];
    }
    root->isLeaf = true;
}

TrieNode* ConstructTrie(const vector<string>& words)
{
    TrieNode *root = getNode();
    if (!root)
    {
        return nullptr;
    }
    if (words.empty())
    {
        return root;
    }
    for (const auto& word : words)
    {
        insert(root, word);
    }
    return root;
}

bool isValidRowIndex(int rIndex, int ROWS)
{
    return rIndex >= 0 && rIndex < ROWS;
}

bool isValidColIndex(int cIndex, int COLS)
{
    return cIndex >= 0 && cIndex < ROWS;
}

void _findwords(const char boggle[ROWS][COLS], const TrieNode *root,
            bool visited[ROWS][COLS], int i, int j, string& res)
{
    if (!root || visited[i][j])
    {
        return;
    }
    else if (root->isLeaf)
    {
        cout << res << endl;
    }

    visited[i][j] = true;

    for (auto r = i - 1; r <= i+1; ++r)
    {
        for (auto c = j - 1; c <= j+1 ; ++c)
        {
            if (isValidRowIndex(r, ROWS) && isValidColIndex(c, COLS))
            {
                auto index = boggle[r][c] - 'a';
                if (root->children[index])
                {
                    res.push_back(boggle[r][c]);
                    _findwords(boggle, root->children[index], visited, r, c, res);
                    res.pop_back();
                }
            }
        } // end of inner for
    } // end of outer for

    visited[i][j] = false;
}

void findWords(const vector<string>& dictionary, const char boggle[ROWS][COLS])
{
    const TrieNode *root = ConstructTrie(dictionary);
    if (!root)
    {
        return;
    }

    bool visited[ROWS][COLS] = { {false} };
    string res;
    cout << "Boggle words" << endl;
    for (int i = 0; i < ROWS; ++i) 
    {
        for (int j = 0; j < COLS; ++j)
        {
            auto index = boggle[i][j] - 'a';
            if (root->children[index])
            {
                res.push_back(boggle[i][j]);
                _findwords(boggle, root->children[index], visited, i, j, res);
                res.pop_back();
            }
        }
    }
}

int main()
{
	vector<string>dictionary = {"geeks", "for", "quiz", "gee"};
	const char boggle[ROWS][COLS] = {
	    {'g','i','z'},
		{'u','e','k'},
		{'q','s','e'}
	};

    findWords(dictionary, boggle);

	return 0;
}
