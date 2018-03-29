#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <unordered_map>
using namespace std;

// Given a 2D grid, that represents a maze like area. Each cell in the grid can be 
// either land or water or door or key to some doors. Each type of key will only 
// open one type of door. There can be multiple identical keys of the same type.
// There can also be multiple doors of the same type. There is also a start cell
// and a goal cell on the land. 
// The goal is to find the shortest path from start to the end.
// Cells in grid are described as
// '#' = Water
// '.' = Land
// 'a' = Key of type 'a'. All lowercase letters are keys
// 'A' = Door that opens with key 'a'. All uppercase letters are doors
// '@' = Starting cell
// '+' = Ending cell (goal)
// -----------
// Constraints
// -----------
// Can travel on land, key cells and door cells but not on water cells
// Can travel in any of 4 directions (including backwards), but not diagonally
// Ok to revisit a cell
// Cannot travel through a door, unless a key to that door has been picked prior
// A key of certain type can be re-used on multiple doors of same kind
// There is exactly one starting and one goal and the path between them is guaranteed to exist

enum class PositionType
{
    Land,
    Water,
    Key,
    Door,
    Start,
    End,
    Unknown,
};

static bool isValidIndex(size_t index, size_t size)
{
    return index < size;
}

struct Position
{
    size_t x = 0;
    size_t y = 0;

    Position() = default;
    Position(size_t _x, size_t _y) : x(_x), y(_y)
    { }
    Position(const Position&) = default;

    bool operator== (const Position& rhs) const
    {
        return x == rhs.x && y == rhs.y;
    }
};

PositionType getPositionType(char c)
{
    if (c == '#') { return PositionType::Water; }
    else if (c == '.') { return PositionType::Land; }
    else if (c >= 'a' && c <= 'z') { return PositionType::Key; }
    else if (c >= 'A' && c <= 'Z') { return PositionType::Door; }
    else if (c == '@') { return PositionType::Start; }
    else if (c == '+') { return PositionType::End; }
    return PositionType::Unknown;
}

struct PositionHash
{
    size_t operator()(const Position& key) const
    {
        return std::hash<size_t>()(key.x) ^ std::hash<size_t>()(key.y);
    }
};

vector<Position> getValidPositions(const Position& pos, size_t numRows, size_t numCols)
{
    if (!isValidIndex(pos.x, numRows) || !isValidIndex(pos.y, numCols)) { return {}; }

    vector<Position> validPositions;
    if (isValidIndex(pos.y + 1, numCols)) { validPositions.push_back(Position(pos.x, pos.y + 1)); }
    if (isValidIndex(pos.x + 1, numRows)) { validPositions.push_back(Position(pos.x + 1, pos.y)); }
    if (isValidIndex(pos.y - 1, numCols)) { validPositions.push_back(Position(pos.x, pos.y - 1)); }
    if (isValidIndex(pos.x - 1, numRows)) { validPositions.push_back(Position(pos.x - 1, pos.y)); }
    return validPositions;
}

// Gets the path from source to destination
vector<Position> getPath(unordered_map<Position, Position, PositionHash>& lookup, const Position& end)
{
    vector<Position> path;
    path.push_back(end);
    Position parent = end;

    // construct the path backwards from the destination to source
    while (lookup.find(parent) != lookup.cend())
    {
        if (lookup[parent] == parent)
        {
            // a node which is parent of itself is the source
            break;
        }
        parent = lookup[parent];
        path.push_back(parent);
    }
    return path;
}

// Gets the path from destination to source
vector<Position> getPathInReverse(unordered_map<Position, Position, PositionHash>& lookup, const Position& end)
{
    vector<Position> path = getPath(lookup, end);
    reverse(path.begin(), path.end());
    return path;
}

vector<Position> _ShortestPath(const vector<string>& grid, const Position& start, const Position& end, int keyRing)
{
    if (start == end)
    {
        return {start};
    }
    else if (grid.empty())
    {
        return {};
    }

    size_t rows = grid.size(), cols = grid[0].size();
    queue<Position> q;
    unordered_map<Position, Position, PositionHash> lookup;
    vector<vector<Position>> pathFromStartToKeys(26);
    vector<Position> currentPath;

    // do a bfs
    bool foundPath = false;
    // set the source as parent of itself
    lookup[start] = start;
    q.push(start);
    while (!q.empty())
    {
        Position parent = q.front();
        q.pop();
        auto parentVal = grid[parent.x][parent.y];
        if (getPositionType(parentVal) == PositionType::Water || getPositionType(parentVal) == PositionType::Unknown)
        {
            continue;
        }
        else if (getPositionType(parentVal) == PositionType::End)
        {
            foundPath = true;
            break;
        }
        else if (getPositionType(parentVal) == PositionType::Start)
        {
            // do a reset of existing paths
            lookup.clear();

            // flush current Q state and start a new bfs from current key position
            lookup[start] = start;
            queue<Position> emptyQ;
            swap(q, emptyQ);    
        }
        else if (getPositionType(parentVal) == PositionType::Key)
        {
            auto keyValue = parentVal - 'a';
            currentPath = getPathInReverse(lookup, parent);
            if (currentPath.empty()) { continue; }

            // am I encountering the key for the first time
            if ((keyRing & (1 << keyValue)) == 0)
            {
                keyRing |= (1 << keyValue);
                // if the current path is not from start, construct complete path
                if (!(currentPath[0] == start))
                {
                    auto anotherKeyValue = grid[currentPath[0].x][currentPath[0].y] - 'a';
                    vector<Position> anotherKeyPath = pathFromStartToKeys[anotherKeyValue];
                    if (!anotherKeyPath.empty() && currentPath[0] == anotherKeyPath.back())
                    {
                        currentPath.erase(currentPath.begin());
                    }
                    currentPath.insert(currentPath.begin(), anotherKeyPath.begin(), anotherKeyPath.end());
                }
                // this key is encountered for the first time; 
                // so this path has to be the shortest path to this key seen so far
                pathFromStartToKeys[keyValue] = currentPath;

                // do a reset of existing paths
                lookup.clear();

                // flush current Q state and start a new bfs from current key position
                //lookup[start] = start;
                lookup[parent] = parent;
                queue<Position> emptyQ;
                swap(q, emptyQ);
            }
            else
            {
                size_t shortestPathToKeySize = pathFromStartToKeys[keyValue].size();
                size_t currentPathToKeySize = currentPath.size();
                // if the current path is not from start, get complete path size
                if (!(currentPath[0] == start))
                {
                    auto anotherKeyValue = grid[currentPath[0].x][currentPath[0].y] - 'a';
                    auto anotherKeyPathSize = pathFromStartToKeys[anotherKeyValue].size();
                    currentPathToKeySize += anotherKeyPathSize - 1;
                }
                if (currentPathToKeySize < shortestPathToKeySize)
                {
                    if (!(currentPath[0] == start))
                    {
                        auto anotherKeyValue = grid[currentPath[0].x][currentPath[0].y] - 'a';
                        vector<Position> anotherKeyPath = pathFromStartToKeys[anotherKeyValue];
                        if (!anotherKeyPath.empty() && currentPath[0] == anotherKeyPath.back())
                        {
                            currentPath.erase(currentPath.begin());
                        }
                        currentPath.insert(currentPath.begin(), anotherKeyPath.begin(), anotherKeyPath.end());
                    }
                    // do a reset of existing paths
                    lookup.clear();

                    // flush current Q state and start a new bfs from current key position
                    //lookup[start] = start;
                    lookup[parent] = parent;
                    queue<Position> emptyQ;
                    swap(q, emptyQ);
                }
            }
        } // end of key
        else if (getPositionType(parentVal) == PositionType::Door)
        {
            auto shiftVal = parentVal - 'A';
            if ((keyRing & (1 << shiftVal)) == 0)
            {
                // could not find key to the door
                continue;
            }
        }    
        
        vector<Position> validPositions = getValidPositions(parent, rows, cols);
        for (const auto& pos : validPositions)
        {
            // do not add if the position was seen prior
            if (lookup.find(pos) == lookup.cend())
            {
                q.push(pos);
                lookup[pos] = parent;
            }
        }
    }

    if (foundPath)
    {
        currentPath = getPathInReverse(lookup, end);
        if (!(currentPath[0] == start))
        {
            auto anotherKeyValue = grid[currentPath[0].x][currentPath[0].y] - 'a';
            vector<Position> anotherKeyPath = pathFromStartToKeys[anotherKeyValue];
            if (!anotherKeyPath.empty() && currentPath[0] == anotherKeyPath.back())
            {
                currentPath.erase(currentPath.begin());
            }
            currentPath.insert(currentPath.begin(), anotherKeyPath.begin(), anotherKeyPath.end());
        }
        return currentPath;
    }
    return {};
}

void ShortestPath(const vector<string>& grid)
{
    Position start, end;
    for (size_t i = 0; i < grid.size(); ++i)
    {
        for (size_t j = 0; j < grid[i].size(); ++j)
        {
            if (getPositionType(grid[i][j]) == PositionType::Start)
            {
                start.x = i; start.y = j;
            }
            if (getPositionType(grid[i][j]) == PositionType::End)
            {
                end.x = i; end.y = j;
            }
        }
    }
    vector<Position> path = _ShortestPath(grid, start, end, 0);

    cout << "For the grid: " << endl;
    for (const string& str : grid)
    {
        for (auto c : str)
        {
            cout << c << " ";
        }
        cout << endl;
    }
    cout << "The shortest path from (" << start.x << ", " << start.y << ")" 
    << " to (" << end.x << ", " << end.y << ") is as follows: " << endl;
}

// can only travel on land, key, door and not on water
// can travel in any of 4 directions, but not diagonally
// cannot travel through door, unless the key to that door is picked
// a key can be re-used on multiple doors of same kind
int main()
{
    vector<string> grid = 
    {
        ".dj##.f.j#efejj..@e#+G.c.",
        ".hdI#.#aAghficDe#J.CGa.ba",
    };

    ShortestPath(grid);

    return 0;
}