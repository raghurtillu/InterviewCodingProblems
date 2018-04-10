#include <iostream>
#include <vector>
using namespace std;

// Given a m x n matrix, if an element is 0, set its entire row and column to 0. Do it in place
void PrintMatrix(const vector<vector<bool>>& matrix)
{
    for (size_t i = 0; i < matrix.size(); ++i)
    {
        for (size_t j = 0; j < matrix[0].size(); ++j)
        {
            matrix[i][j] ? cout << "1" << " " : cout << "0" << " ";
        }
        cout << endl;
    }
}

void ZeroMatrix(vector<vector<bool>>& matrix)
{
    if (matrix.empty() || matrix[0].empty())
    {
        return;
    }

    bool rowZero = false, colZero = false;
    // Determine whether the first row or first column is true
    for (size_t i = 0; i < matrix.size(); ++i)
    {
        rowZero |= matrix[0][i];
    }
    for (size_t i = 0; i < matrix.size(); ++i)
    {
        colZero |= matrix[i][0];
    }

    // For each cell not in the first row/column, if it is true, set the cell in 
    // the first row/same column and first column/same row to be true
    for (size_t i = 1; i < matrix.size(); ++i)
    {
        for (size_t j = 1; j < matrix[0].size(); ++j)
        {
            if (matrix[i][j])
            {
                matrix[i][0] = matrix[0][j] = true;
            }
        }
    }
    
    // Go through the first column and set each row to true where cell in the first 
    // column is true
    for (size_t i = 1; i < matrix.size(); ++i)
    {
        if (matrix[i][0])
        {
            for (size_t j = 1; j < matrix.size(); ++j)
            {
                matrix[i][j] = true;
            }
        }
    }

    // Repeat for the rows
    for (size_t j = 1; j < matrix[0].size(); ++j)
    {
        if (matrix[0][j])
        {
            for (size_t i = 1; i < matrix.size(); ++i)
            {
                matrix[i][j] = true;
            }
        }
    }

    // Set first row/column to true if necessary
    if (rowZero)
    {
        for (size_t i = 0; i < matrix[0].size(); ++i)
        {
            matrix[0][i] = true;
        }
    }
    if (colZero)
    {
        for (size_t i = 0; i < matrix.size(); ++i)
        {
            matrix[i][0] = true;
        }
    }
}

int main()
{
    vector<vector<vector<bool>>> inputs = 
    {
        {
            {true, false, false},
            {false, false, false},
            {false, false, true},
        },
        {
            {true, false, true},
            {false, false, false},
            {false, false, true},
        },
    };

    cout << "Zero matrix: " << endl;
    for (auto& input : inputs)
    {
        cout << "Input" << endl;
        PrintMatrix(input);
        ZeroMatrix(input);
        cout << "Output" << endl;
        PrintMatrix(input);
        cout << endl;
    }
    
    return 0;
}