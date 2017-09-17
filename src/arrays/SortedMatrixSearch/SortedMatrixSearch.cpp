#include <iostream>
#include <vector>

using namespace std;
static const size_t N = 4;

// find an element in a sorted matrix (sorted both row and column wise)
bool SortedMatrixSearch(const int matrix[N][N], int key)
{    
    if (key < matrix[0][0] || key > matrix[N-1][N-1])
    {
        return false;
    }

    size_t r = 0, c = N-1;
    while (r < N && c != SIZE_MAX)
    {
        if (key == matrix[r][c])
        {
            return true;
        }
        else if (key < matrix[r][c])
        {
            // go left
            c--;
        }
        else if (key > matrix[r][c])
        {
            // go down
            r++;
        }
    }
    return false;
}

int main()
{
    const int matrix[N][N] = {
        {2, 6, 7, 11},
        {3, 8, 10, 12},
        {4, 9, 11, 13},
        {5, 15, 16, 18}
    };

    vector<int> keys = {
        1,
        9,
        5,
        16,
        18,
        27        
    };

    for (auto i : keys)
    {
        auto res = SortedMatrixSearch(matrix, i);
        if (res)
        {
            cout << "The key " << i << " was found" << endl;
        }
        else
        {
            cout << "The key " << i << " was not found" << endl;
        }
    }
    return 0;
}