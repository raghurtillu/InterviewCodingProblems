#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

// Given a graph of parent child nodes as follows: determine given two nodes if
// they are connected by a common ancestor
// 1   2   4
//  \ /   / \
//   3   5   8
//    \ / \   \
//     6   7   9
        
// parentChildPairs, 3, 8 => false
// parentChildPairs, 5, 8 => true, 4 is common ancestor
// parentChildPairs, 6, 8 => true, 4 is common ancestor
// parentChildPairs, 8, 9 => true, 8 is common ancestor

unordered_map<int, size_t> getVertexDegree(const vector<pair<int, int>>& pairs)
{
    unordered_map<int, size_t> inDegree;
    for (const auto& p : pairs)
    {
        inDegree[p.first] = 0;
        inDegree[p.second]++;
    }
    return inDegree;
}

vector<int> getNeighbours(const vector<pair<int, int>>& pairs, int node)
{
    vector<int> neighbours;
    for (const auto& p : pairs)
    {
        if (p.first == node) 
        {
            neighbours.push_back(p.second); 
        }
    }
    return neighbours;
}

void ConstructSearchTree(const vector<pair<int, int>>& pairs,
        int currentNode,
        int parentNode,
        unordered_map<int, int>& searchTree)
{
    searchTree[currentNode] = parentNode;
    auto neighbours = getNeighbours(pairs, currentNode);
    for (size_t i = 0; i < neighbours.size(); ++i)
    {
        if (searchTree.find(neighbours[i]) == searchTree.cend())
        {
            ConstructSearchTree(pairs, neighbours[i], currentNode, searchTree);
        }
    }
}

bool IsNodePresent(int node, const unordered_map<int, int>& searchTree)
{
    for (auto& it : searchTree)
    {
        if (it.first == node || it.second == node) 
        {
            return true;
        }
    }
    return false;
}

bool parentChildPair(const vector<pair<int, int>>& pairs, int from, int to)
{
    if (pairs.empty()) { return false; }

    auto inDegree = getVertexDegree(pairs);
    for (auto& it : inDegree)
    {
        unordered_map<int, int> searchTree;
        if (it.second == 0)
        {
            ConstructSearchTree(pairs, it.first, it.first, searchTree);
            if (IsNodePresent(from, searchTree) && IsNodePresent(to, searchTree))
            {
                return true;
            }
        }
    }
    return false;
}

int main() 
{
    vector<pair<int, int>> parentChildPairs = 
    {
        std::make_pair(1, 3),
        std::make_pair(2, 3),
        std::make_pair(3, 6),
        std::make_pair(5, 6),
        std::make_pair(5, 7),
        std::make_pair(4, 5),
        std::make_pair(4, 8),
        std::make_pair(8, 9)
    };

    vector<pair<int, int>> input
    {
        {3, 5},
        {5, 8},
        {6, 8},
        {8, 9},
        {5, 15},    // 15, non existent node
    };

    cout << "Checking if the following nodes are connected by an ancestor: " << endl;
    for (const auto& p : input)
    {
        cout << "{" << p.first << ", " << p.second << "}: ";
        bool res = parentChildPair(parentChildPairs, p.first, p.second);
        (res) ? cout << "Yes" : cout << "No";
        cout << endl;
    }
    return 0;
}