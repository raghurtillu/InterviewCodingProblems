#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct TrieNode
{
	TrieNode *children[26] = { nullptr };
    vector<int> pos; // To store palindromic positions in str
	int id;
	bool isLeaf = false;

    static TrieNode* getTrieNode()
    {
        return new(nothrow) TrieNode();
    }
};

bool isPalindrome(const string& str, size_t low, size_t high)
{
    if (str.empty())
    {
        return false;
    }
    else if (low >= str.size() || high >= str.size() || low > high || high - low > str.size())
    {
        return false;
    }
    
    while (low < high)
    {
        if (str[low++] != str[high--])
        {
            return false;
        }
    }
    return true;
}

void insert(TrieNode* root, const string& key, int id)
{
	for (int level = key.size() - 1; level >= 0; --level)
	{
		// If it is not available in Trie, then
		// store it
		int index = key[level] - 'a';
		if (!root->children[index]) 
        {
		    root->children[index] = TrieNode::getTrieNode();
		}

		// If current word is palindrome till this
		// level, store index of current word.
		if (isPalindrome(key, 0, level)) 
        {
		    root->pos.push_back(id);
		}
		root = root->children[index];
	}
	root->id = id;
	root->pos.push_back(id);
	root->isLeaf = true;
}

// Returns true if key presents in Trie, else false
void search(const TrieNode *root, const string& key, int id, vector<vector<int>> &result)
{
	for (int level = 0; level < key.length(); ++level) 
    {
		int index = key[level] - 'a';
		if (root->id >= 0 && root->id != id && isPalindrome(key, level, key.size()-1)) 
        {
            // ends up here if key is not yet completed
            // but the TrieNode traversal is potentially completed
            // e.g. consider strings "geekf", "keeg" 
            // TrieNode is built for reverse of string -> "geek"
            // key geek(f) is partial match for geek
            result.push_back({id, root->id});    
		}
			
		// If not present then return
		if (!root->children[index]) 
        {
		    return;
		}
		root = root->children[index];
	}

	for (int i : root->pos)
    {
	    // Will end up here if key is empty but the 
	    // TrieNode is not yet reached the leaf
	    
	    // e.g. consider strings "abc", "xyxcba", TrieNode is built for
	    // reverse of string -> "abcxyx"
	    // key abc is completed matching partially abc(xyx) 
		if (i == id)
        {
		    continue;
		}
		result.push_back({id, i});
	}
}

// Function to check if a palindrome pair exists
void checkPalindromePair(const vector<string>& vect)
{
	// Construct trie
	TrieNode *root = TrieNode::getTrieNode();
	for (int i = 0; i < vect.size(); ++i) 
    {
        insert(root, vect[i], i);   
	}

    cout << "For the words: ";
	// Search for different keys
	vector<vector<int> > result;
	for (int i = 0; i < vect.size(); ++i) 
    {
		cout << vect[i] << " ";
        search(root, vect[i], i, result);
	}

    cout << endl;
    cout << "Palindromic pairs are: ";
    for (int i = 0; i < result.size(); ++i) 
    {
        const auto& val = result[i];
        for (const auto& temp : val) 
        {
            cout << vect[temp] << " ";
        }
        if (i != result.size() - 1)
        {
            cout << ", ";
        }
    }
    cout << endl << endl;
}

// Driver code
int main()
{
	vector<vector<string>> vect = 
    {
        {"geekf", "geeks", "or", "keeg", "abc", "bc"},
        {"abc", "xyxcba", "geekst", "or","keeg", "bc"}
	};

	for (int i = 0; i < vect.size(); ++i) 
    {
	    checkPalindromePair(vect[i]);    
	}
	return 0;
}
