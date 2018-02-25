#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
using namespace std;

// given a binary matrix find if there exists any rectangle or square in the given 
// matrix whose all four corners are equal to 1
// Input :
// mat[][] = { 1 0 0 1 0
//             0 0 1 0 1
//             0 0 0 1 0
//             1 0 1 0 1}
// Output :
// 1 0 1
// 0 1 0
// 1 0 1

bool HasRectangle(const vector<vector<int>>& mat)
{
    if (mat.empty() || mat[0].empty())
    {
        return false;
    }

    size_t rows = mat.size(), cols = mat[0].size();
    unordered_map<size_t, unordered_set<size_t>> lookup;

    for (size_t i = 0; i < rows; ++i)
    {
        for (size_t j = 0; j < cols; ++j)
        {
            for (size_t k = j + 1; k < cols; ++k)
            {
                // remember each combination of 2 1’s and push that into a hash-set
                // if we ever find that combination again in a later line, we get our rectangle
                if (mat[i][j] == 1 && mat[i][k] == 1)
                {
                    if (lookup.find(j) != lookup.cend() && lookup[j].find(k) != lookup[j].cend())
                    {
                        return true;
                    }
                    else if (lookup.find(k) != lookup.cend() && lookup[k].find(j) != lookup[k].cend())
                    {
                        return true;
                    }
                    lookup[j].insert(k);
                    lookup[k].insert(j);
                }
            }
        }
    }
    return false;
}

int main()
{
    vector<vector<int>> mat = 
    {
        { 1, 0, 0, 1, 0 },
        { 0, 0, 1, 0, 1 },
        { 0, 0, 0, 1, 0 },
        { 1, 0, 1, 0, 1 },
    };

    cout << "For the matrix: " << endl;
    for (const auto& r : mat)
    {
        for (const auto c :r)
        {
            cout << c << " ";
        }
        cout << endl;
    }
    bool res = HasRectangle(mat);
    cout << "There " << ((res) ? "exists" : "does not exist") 
        << " a rectangle whose all four corners are equal to 1" << endl;
    
    return 0;
}