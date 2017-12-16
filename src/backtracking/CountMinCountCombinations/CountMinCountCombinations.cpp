// C++ program to count number of possible strings with n characters.
#include <iostream>
#include <vector>
using namespace std;

int rgb(int total, int rCount, int rMinCount, int gCount, int gMinCount, int bCount, int bMinCount)
{
    if (total < 0)
    {
        return 0;
    }
    else if (rMinCount < 0 || gMinCount < 0 || bMinCount < 0)
    {
        return 0;
    }
    else if (rMinCount + gMinCount + bMinCount > total)
    {
        return 0;
    }
    else if (rCount < 0 || gCount < 0 || bCount < 0)
    {
        return 0;
    }
    else if (rCount + gCount + bCount > total)
    {
        return 0;
    }
    else if (rCount + gCount + bCount == total)
    {
        if (rCount < rMinCount || gCount < gMinCount || bCount < bMinCount)
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
    
    return
    rgb(total, rCount + 1, rMinCount, gCount, gMinCount, bCount, bMinCount) +
    rgb(total, rCount, rMinCount, gCount + 1, gMinCount, bCount, bMinCount) +
    rgb(total, rCount, rMinCount, gCount, gMinCount, bCount + 1, bMinCount);
}

int possibleStrings(int total, int rMinCount, int gMinCount, int bMinCount)
{
    int rCount = 0, gCount = 0, bCount = 0;
    return rgb(total, rCount, rMinCount, gCount, gMinCount, bCount, bMinCount);
}

// Drivers code
int main()
{
	struct Counts
    {
        int total = 0;
        int rMinCount = 0;
        int gMinCount = 0;
        int bMinCount = 0;

        Counts(int _total, int _rMinCount, int _gMinCount, int _bMinCount) :
            total(_total), rMinCount(_rMinCount), gMinCount(_gMinCount), bMinCount(_bMinCount)
        {

        }
    };

    // {total, rMinCount, gMinCount, bMinCount}
    vector<Counts> values = 
    {
        {3, 0, 0, 0},
        {3, 1, 0, 0},
        {3, 1, 1, 0},
        {3, 1, 1, 1},
        {4, 2, 1, 0},
        {4, 2, 1, 1},
        {6, 2, 1, 1},
        {6, 4, 2, 1}, // 0; mincounts sum is > total count; 4 + 2 + 1 > 6
    };
    
    cout << "The number of strings using the given combinations" << endl;
    for (const auto& val: values)
    {
        int total = val.total;
        int rMinCount = val.rMinCount;
        int gMinCount = val.gMinCount;
        int bMinCount = val.bMinCount;

        cout << "rgb total count: " << total << ", rMinCount: " << rMinCount
            << ", gMinCount: " << gMinCount
            << ", bMinCount: " << bMinCount << " --> ";
        cout << possibleStrings(total, rMinCount, gMinCount, bMinCount) << endl;
    }
}
