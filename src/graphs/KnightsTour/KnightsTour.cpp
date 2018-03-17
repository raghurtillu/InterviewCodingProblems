#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <unordered_map>
using namespace std;

static bool isValidIndex(size_t index, size_t size)
{
    return index < size;
}

struct Position
{
    size_t x = 0;
    size_t y = 0;

    Position() = default;
    Position(const Position&) = default;
    Position(const std::pair<size_t, size_t>& p) :
        x(p.first), y(p.second)
    {

    }
    bool operator== (const Position& rhs) const
    {
        return x == rhs.x && y == rhs.y;
    }
};

class ChessPiece
{
protected:
    Position curPos;
public:
    ChessPiece(const Position& pos) : curPos(pos)
    { }
    virtual std::vector<Position> validMoves() = 0;
};

class Knight : public ChessPiece
{
    size_t numRows = 0;
    size_t numCols = 0;
public:
    Knight(const Position& pos, size_t _numRows, size_t _numCols) 
        : ChessPiece(pos), numRows(_numRows), numCols(_numCols)
    {}

    // There are 8 potential positions that a knight can move from a given position
    //-----------------------------------------------------------------------
    //  #   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |
    //-----------------------------------------------------------------------
    //  0   |       |       |       |       |       |       |       |       |
    //-----------------------------------------------------------------------
    //  1   |       |       | Pos8  |       | Pos1  |       |       |       |
    //-----------------------------------------------------------------------
    //  2   |       | Pos7  |       |       |       | Pos2  |       |       |
    //-----------------------------------------------------------------------
    //  3   |       |       |       |Knight |       |       |       |       |
    //-----------------------------------------------------------------------
    //  4   |       | Pos6  |       |       |       | Pos3  |       |       |
    //-----------------------------------------------------------------------
    //  5   |       |       | Pos5  |       | Pos4  |       |       |       |
    //-----------------------------------------------------------------------
    //  6   |       |       |       |       |       |       |       |       |
    //-----------------------------------------------------------------------
    //  7   |       |       |       |       |       |       |       |       |
    //-----------------------------------------------------------------------
    virtual std::vector<Position> validMoves()
    {
        size_t curRow = curPos.x;
        size_t curCol = curPos.y;

        std::vector<Position> possibleMoves;
        // Pos1: {curRow - 2, curCol + 1}
        if (isValidIndex(curRow - 2, numRows) && isValidIndex(curCol + 1, numCols))
        {
            possibleMoves.push_back(Position({curRow - 2, curCol + 1}));
        }
        // Pos2: {curRow - 1, curCol + 2}
        if (isValidIndex(curRow - 1, numRows) && isValidIndex(curCol + 2, numCols))
        {
            possibleMoves.push_back(Position({curRow - 1, curCol + 2}));
        }
        // Pos3: {curRow + 1, curCol + 2}
        if (isValidIndex(curRow + 1, numRows) && isValidIndex(curCol + 2, numCols))
        {
            possibleMoves.push_back(Position({curRow + 1, curCol + 2}));
        }
        // Pos4: {curRow + 2, curCol + 1}
        if (isValidIndex(curRow + 2, numRows) && isValidIndex(curCol + 1, numCols))
        {
            possibleMoves.push_back(Position({curRow + 2, curCol + 1}));
        }
        // Pos5: {curRow + 2, curCol - 1}
        if (isValidIndex(curRow + 2, numRows) && isValidIndex(curCol - 1, numCols))
        {
            possibleMoves.push_back(Position({curRow + 2, curCol - 1}));
        }
        // Pos6: {curRow + 1, curCol - 2}
        if (isValidIndex(curRow + 1, numRows) && isValidIndex(curCol - 2, numCols))
        {
            possibleMoves.push_back(Position({curRow + 1, curCol - 2}));
        }
        // Pos7: {curRow - 1, curCol - 2}
        if (isValidIndex(curRow - 1, numRows) && isValidIndex(curCol - 2, numCols))
        {
            possibleMoves.push_back(Position({curRow - 1, curCol - 2}));
        }
        // Pos8: {curRow - 2, curCol - 1}
        if (isValidIndex(curRow - 2, numRows) && isValidIndex(curCol - 1, numCols))
        {
            possibleMoves.push_back(Position({curRow - 2, curCol - 1}));
        }
        return possibleMoves;
    }
};

struct PairHash
{
    size_t operator()(const Position& key) const
    {
        return std::hash<int>()(key.x) ^ std::hash<int>()(key.y);
    }
};

vector<Position> _getKnightTour(const Position& start, const Position& end, size_t numRows, size_t numCols)
{
    if (start == end)
    {
        return {start};
    }

    queue<Position> q;
    unordered_map<Position, Position, PairHash> lookup;
    bool foundPath = false;

    q.push(start);
    lookup[start] = start;
    while (!q.empty())
    {
        Position parent = q.front();
        q.pop();
        if (parent == end)
        {
            foundPath = true;
            break;
        }
        Knight knight(parent, numRows, numCols);
        vector<Position> validPositions = knight.validMoves();
        for (const auto& pos : validPositions)
        {
            if (lookup.find(pos) == lookup.cend())
            {
                q.push(pos);
                lookup[pos] = parent;
            }
        }
    }

    if (foundPath)
    {
        vector<Position> path;
        path.push_back(end);
        Position parent = end;
        while (lookup.find(parent) != lookup.cend())
        {
            if (lookup[parent] == parent)
            {
                break;
            }
            parent = lookup[parent];
            path.push_back(parent);
        }
        reverse(path.begin(), path.end());
        return path;
    }
    return {};
}

size_t getKnightTour(size_t rows, size_t cols, size_t startRow, size_t startCol, size_t endRow, size_t endCol)
{
    if (rows == 0 || cols == 0 
        || startRow >= rows || startCol >= cols  
        || endRow >= rows || endCol >= cols)
    {
        return 0;
    }
    size_t minRows = endRow >= startRow ? endRow - startRow : startRow - endRow;
    size_t minCols = endCol >= startCol ? endCol - startCol : startCol - endCol;
    if (minRows > rows || minCols > cols)
    {
        return 0;
    }

    Position start({startRow, startCol});
    Position end({endRow, endCol});

    cout << "For the positions, " << "(" << start.x << ", " << start.y << ")";
    cout << " and " << "(" << end.x << ", " << end.y << ")" << " the tour is: ";
    vector<Position> path = _getKnightTour(start, end, rows, cols);
    if (!path.empty())
    {
        for (size_t i = 0; i < path.size(); ++i)
        {
            cout << "(" << path[i].x << ", " << path[i].y << ")";
            if (i != path.size() - 1)
            {
                cout << " -> ";
            }
        }
        cout << ", total number of moves: ";
        path.size() > 0 ? cout << path.size() - 1 << endl : cout << "0" << endl;
        return path.size();
    }
    else
    {
        cout << "No path found." << endl;
        return 0;
    }
}

int main()
{
    struct KnightTourInputs
    {
        size_t rows = 0;
        size_t cols = 0;
        size_t startRow = 0;
        size_t startCol = 0;
        size_t endRow = 0;
        size_t endCol = 0;

        KnightTourInputs(size_t _rows, size_t _cols, size_t _startRow, size_t _startCol, 
            size_t _endRow, size_t _endCol) :
            rows(_rows), cols(_cols), startRow(_startRow), startCol(_startCol), endRow(_endRow), endCol(_endCol)
        {}
    };

    vector<KnightTourInputs> inputs = 
    {
        {KnightTourInputs(5, 5, 0, 0, 4, 1)},
        {KnightTourInputs(2, 7, 0, 5, 0, 1)},
        {KnightTourInputs(3, 8, 0, 6, 1, 5)},
        {KnightTourInputs(3, 8, 0, 6, 2, 0)},
        {KnightTourInputs(4999, 20, 4998, 0, 4998, 19)},
    };

    for (const auto& input : inputs)
    {
        getKnightTour(input.rows, input.cols, input.startRow, input.startCol, input.endRow, input.endCol);
    }
    return 0;
}