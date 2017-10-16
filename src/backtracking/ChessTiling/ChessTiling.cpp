#include <iostream>
#include <vector>
using namespace std;

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

int GetPattern(int n, int i, int j)
{
    n = n >> 1;
    i = i / n;
    j = j / n;

    if (i % 2 == 0 && j % 2 == 0)
    {
        return 1;
    }
    else if (i % 2 == 0 && j % 2 != 0)
    {
        return 2;        
    }
    else if (i % 2 != 0 && j % 2 == 0)
    {
        return 3;
    }
    else
    {
        return 4;
    }
}

void FillPattern(vector<vector<int>>& board, int pattern, int n, int i, int j, int wx1, int wy1)
{
    static int count = 0;
    count++;

    if (n == 1)
    {
        switch (pattern)
        {
            case 1:
                board[i][j+1] = board[i+1][j] = board[i+1][j+1] = count;
            break;
            case 2:
                board[i][j] = board[i+1][j] = board[i+1][j+1] = count;                
            break;
            case 3:
                board[i][j] = board[i][j+1] = board[i+1][j+1] = count;
            break;
            case 4:
                board[i][j+1] = board[i+1][j] = board[i][j] = count;
            break;
        }
        return;
    }
    else
    {
        int p1 = 4, p2 = 3, p3 = 2, p4 = 1;

        i = i + n/2;
        j = j + n/2;

        int px1 = i, py1 = j;
        int px2 = i, py2 = j + 1;
        int px3 = i + 1, py3 = j;
        int px4 = i + 1, py4 = j + 1;

        switch (pattern)
        {
            case 1:
                board[i][j+1] = board[i+1][j] = board[i+1][j+1] = count;
                p1 = GetPattern((n+1)/2, wx1, wy1);
                px1 = wx1;
                py1 = wy1;
            break;
            case 2:
                board[i][j] = board[i+1][j] = board[i+1][j+1] = count;
                p2 = GetPattern((n+1)/2, wx1, wy1);
                px2 = wx1;
                py2 = wy1;
            break;
            case 3:
                board[i][j] = board[i][j+1] = board[i+1][j+1] = count;
                p3 = GetPattern((n+1)/2, wx1, wy1);
                px3 = wx1;
                py3 = wy1;
            break;
            case 4:
                board[i][j+1] = board[i+1][j] = board[i][j] = count;
                p4 = GetPattern((n+1)/2, wx1, wy1);
                px4 = wx1;
                py4 = wy1;
            break;
        }

        FillPattern(board, p1, n/2, i - (n/2), j - (n/2), px1, py1);
        FillPattern(board, p2, n/2, i - (n/2), j + 1, px2, py2);
        FillPattern(board, p3, n/2, i + 1, j - (n/2), px3, py3);
        FillPattern(board, p4, n/2, i+1, j+1, px4, py4);

    }
}

int main()
{
    // 8 x 8 matrix
    vector<vector<int>> board(8, vector<int>(8, 0));

    // defective position
    int wx1 = 2, wy1 = 2;

    int p = GetPattern(8, wx1, wy1);
    FillPattern(board, p, 7, 0, 0, wx1, wy1);

    ShowBoard(board);

    return 0;
}