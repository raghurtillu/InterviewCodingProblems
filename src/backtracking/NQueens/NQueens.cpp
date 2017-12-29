#include <iostream>
#include <vector>
using namespace std;

struct Position 
{
    size_t row = 0;
    size_t col = 0;

    Position(size_t x, size_t y) : row(x), col(y)
    {}
    Position() = default;
};

bool NQueens(size_t N, size_t row, vector<Position>& positions)
{
    if (row > N) 
    {
        return false;
    }
    else if (N == 0 || row == N)
    {
        return true;
    }
    
    // for the queen in given row, iterate through all the columns for a safe position
    for (size_t cols = 0; cols < N; ++cols) 
    {
        bool foundSafe = true;
        for (size_t i = 0; i < positions.size(); ++i) 
        {
            const auto& queenPos = positions[i];
            if (row == queenPos.row || cols == queenPos.col ||  // another queen in same row or column
                row + cols == queenPos.row + queenPos.col ||    // another queen in major diagonal
                row - cols == queenPos.row - queenPos.col)      // another queen in minow diagonal
            {
                foundSafe = false;
                break;
            }
        }
        
        if (foundSafe) 
        {
            positions.push_back(Position(row, cols));
            if (NQueens(N, row + 1, positions))
            {
                return true;
            }
            positions.pop_back();
        }
    } // end of outer for loop
    return false;
}

int main()
{
	vector<int> inputs = 
    {
        4,
        8
    };

    for (size_t i = 0; i < inputs.size(); ++i)
    {
        vector<Position> positions;
        auto N = inputs[i];
        cout << N << " Queens positions" << endl;
        if (NQueens(N, 0, positions))
        {
            for (size_t i = 0; i < positions.size(); ++i)
            {
                cout << "(" << positions[i].row << "," << positions[i].col << ")" << endl;
	        }
        }
        else
        {
            cout << "none possible" << endl;
        }
        cout << endl;
    }
	return 0;
}