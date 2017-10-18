#include <iostream>
#include <vector>
using namespace std;

struct DefectiveChessboard
{
    pair<size_t, size_t> defectivePositions;
    vector<vector<int>> board;
    static int tile;
    DefectiveChessboard(const pair<size_t, size_t>& dPos, size_t boardSize) :
        defectivePositions(dPos), board(boardSize, vector<int>(boardSize, 0))
    {

    }
};
int DefectiveChessboard::tile = 0;

bool isPowerOfTwo(size_t x)
{
    return (x != 0) && ((x & (x - 1)) == 0);
}

void ShowBoard(const vector<vector<int>>& board)
{
    for (const auto& vec : board)
    {
        for (auto i : vec)
        {
            cout << i << "\t";
        }
        cout << endl;
    }
    cout << endl;
}

void _ChessBoard(vector<vector<int>>& board,
    size_t tr, size_t tc, 
    size_t dr, size_t dc, 
    size_t size)
{
    if (size == 1)
    {
        return;
    }
    size_t s = size >> 1;
    DefectiveChessboard::tile++;

    size_t dr1 = 0, dc1 = 0;
    size_t dr2 = 0, dc2 = 0;
    size_t dr3 = 0, dc3 = 0;
    size_t dr4 = 0, dc4 = 0;

    if (dr < tr + s && dc < tc + s)
    {
        // Tromino type
        //     +++++
        //     |   |
        // +++++++++
        // |   |   |
        // +++++++++
        //
        board[tr + s - 1][tc + s] = board[tr + s][tc + s - 1] = board[tr + s][tc + s] = DefectiveChessboard::tile;
        dr1 = dr; dc1 = dc;
        dr2 = tr + s - 1; dc2 = tr + s;
        dr3 = tr + s; dc3 = tc + s - 1;
        dr4 = tr + s; dc4 = tc + s;
    }
    else if (dr < tr + s && dc >= tc + s)
    {
        // Tromino type
        // +++++
        // |   |   
        // +++++++++
        // |   |   |
        // +++++++++
        //
        board[tr + s - 1][tc + s - 1] = board[tr + s][tc + s - 1] = board[tr + s][tc + s] = DefectiveChessboard::tile;
        dr1 = tr + s - 1; dc1 = tc + s - 1;
        dr2 = dr; dc2 = dc;
        dr3 = tr + s; dc3 = tc + s - 1;
        dr4 = tr + s; dc4 = tc + s;
    }
    else if (dr >= tr + s && dc < tc + s)
    {
        // Tromino type
        // +++++++++
        // |   |   |
        // +++++++++
        //     |   |
        //     +++++
        //
        board[tr + s - 1][tc + s - 1] = board[tr + s - 1][tc + s] = board[tr + s][tc + s] = DefectiveChessboard::tile;
        dr1 = tr + s - 1; dc1 = tc + s - 1;
        dr2 = tr + s - 1; dc2 = tc + s;
        dr3 = dr; dc3 = dc;
        dr4 = tr + s; dc4 = tc + s;
    }
    else if (dr >= tr + s && dc >= tc + s)
    {
        // Tromino type
        // +++++++++
        // |   |   |
        // +++++++++
        // |   |   
        // +++++
        //
        board[tr + s - 1][tc + s - 1] = board[tr + s - 1][tc + s] = board[tr + s][tc + s - 1] = DefectiveChessboard::tile;
        dr1 = tr + s - 1; dc1 = tc + s - 1;
        dr2 = tr + s - 1; dc2 = tc + s;
        dr3 = tr + s; dc3 = tc + s - 1;
        dr4 = dr; dc4 = dc;
    }

    _ChessBoard(board, tr, tc, dr1, dc1, s);
    _ChessBoard(board, tr, tc + s, dr2, dc2, s);
    _ChessBoard(board, tr + s, tc, dr3, dc3, s);
    _ChessBoard(board, tr + s, tc + s, dr4, dc4, s);
}

void ChessBoard(vector<vector<int>>& board, size_t dr, size_t dc)
{
    size_t size = board.size();

    // input validation
    if (size == 0)
    {
        return;
    }
    else if (!isPowerOfTwo(size))
    {
        cerr << "The board is not a power of 2" << endl;
        return;
    }
    else if (dr >= size)
    {
        cerr << "defective row index " << dr <<  " out of bounds" << endl;
        return;
    }
    else if (dc >= board[dr].size())
    {
        cerr << "defective col index " << dc <<  " out of bounds" << endl;
        return;
    }
    else
    {
        for (size_t r = 0; r < size; ++r)
        {
            if (board[r].size() != size)
            {
                cerr << "board " << r << " size " << board[r].size() 
                <<  " does not match with " << size << endl;
                return;
            }
        }
    }
    
    board[dr][dc] = -1;

    cout << "Board initial position" << endl;
    ShowBoard(board);

    size_t tr = 0, tc = 0;
    _ChessBoard(board, tr, tc, dr, dc, size);

    cout << "Board final position" << endl;
    ShowBoard(board);    
}

int main()
{
    vector<DefectiveChessboard> values = {
        // {defective row pos, defective col pos}, board size
        DefectiveChessboard(make_pair<size_t, size_t>(1, 0), 7), // invalid board size
        DefectiveChessboard(make_pair<size_t, size_t>(1, 0), 4),
        DefectiveChessboard(make_pair<size_t, size_t>(3, 3), 4),
        DefectiveChessboard(make_pair<size_t, size_t>(4, 2), 8),
        //DefectiveChessboard(make_pair<size_t, size_t>(2, 2), 16),
    };

    for (auto& dc : values)
    {
        DefectiveChessboard::tile = 0;
        ChessBoard(dc.board, dc.defectivePositions.first, dc.defectivePositions.second);
    }
    return 0;
}