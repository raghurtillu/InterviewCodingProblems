#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;

enum CellType { Normal = 0, Snake, Ladder };
struct CellInfo
{    
    size_t index = 0;
    CellType cellType = CellType::Normal;
    CellInfo() = default;
    CellInfo(size_t _index, CellType _cellType) : index(_index), cellType(_cellType)
    { }
};

vector<CellInfo> minMoves(const vector<int>& board)
{
    if (board.empty()) { return {}; }
    else if (board.size() == 1) { return { CellInfo(0, CellType::Normal) }; }

    size_t start = 0, end = board.size() - 1;
    bool foundPath = false;
    unordered_map<size_t, CellInfo> lookup;
    queue<size_t> q;

    if (board[start] == 1)
    {
        lookup[start] = CellInfo(start, CellType::Normal);
        q.push(start);
    }
    else    // if it is not Normal has to be ladder type
    {
        auto temp = board[start];
        q.push(temp);
        lookup[start] = CellInfo(start, CellType::Ladder);
        lookup[temp] = CellInfo(start, CellType::Normal);
    }

    while (!q.empty())
    {
        auto parent = q.front();
        q.pop();
        if (parent == end)
        {
            foundPath = true;
            break;
        }
        for (size_t i = 1; i <= 6; ++i)
        {
            if (parent + i < board.size() && lookup.find(parent + i) == lookup.cend())
            {            
                if (board[parent + i] == 1) // Normal cell
                {
                    q.push(parent + i);
                    lookup[parent + i] = CellInfo(parent, CellType::Normal);
                }
                else    // snake or ladder cell
                {
                    auto temp = board[parent + i];  
                    if (lookup.find(temp) == lookup.cend())
                    {
                        q.push(temp);
                        lookup[temp] = CellInfo(parent + i, CellType::Normal);
                        CellType cellType = (temp < parent + i) ? CellType::Snake : CellType::Ladder;
                        lookup[parent + i] = CellInfo(parent, cellType);
                    }
                }
            }
        }
    }
    if (foundPath)
    {
        vector<CellInfo> path;
        path.push_back(CellInfo(end, CellType::Normal));
        size_t parent = end;
        // construct the path backwards from the destination to source
        while (lookup.find(parent) != lookup.cend())
        {
            if (lookup[parent].index == parent)
            {
                break;
            }
            parent = lookup[parent].index;
            path.push_back(CellInfo(parent, lookup[parent].cellType));
        }
        reverse(path.begin(), path.end());
         // the board is not zero index based, starts from 1 instead; add 1 to all the elements in the path
        for_each(path.begin(), path.end(), [](CellInfo &ci) { ci.index += 1; });
        return path;
    }
    return {};
}

int main()
{
    vector<int> board(36, 1);
    // snakes
    board[16] = 3;
    board[19] = 5;
    board[23] = 15;
    board[31] = 29;
    board[33] = 11;
    // ladders
    board[1] = 14;
    board[4] = 6;
    board[8] = 26;
    board[17] = 28;
    board[24] = 34;

    vector<CellInfo> path = minMoves(board);
    cout << "Output format: " << "<Cell Number>(<CellType>)" << endl;
    cout << "CellType: " << "L -> Ladder, " << "N -> Normal, " << "S -> Snake" << endl;
    cout << "The minimum path to reach the end of the board is: ";
    for (size_t i = 0; i < path.size(); ++i)
    {
        cout << path[i].index;
        cout << "(";
        switch(path[i].cellType)
        {
            case CellType::Ladder : cout << "L";
                break;
            case CellType::Normal : cout << "N";
                break;
            case CellType::Snake : cout << "S";
                break;
        }
        cout << ")";
        if (i != path.size() - 1) { cout << " -> "; }
    }

    // Compute number of dice throws
    bool flag = false;
    size_t total = 0;
    for (size_t i = 0; i < path.size(); ++i)
    {
        if (path[i].cellType == CellType::Normal)
        {
            if (!flag) { flag = true; }
            else { ++total; }
        }
    }
    cout << endl;
    cout << "Total number of dice throws: " << total << endl;
    return 0;
}