#include <iostream>
#include <vector>

using namespace std;

void _LexicographicalOrder(int val, int n, vector<int>& res)
{
    if (val > n)
    {
        return;
    }

    res.push_back(val);

    _LexicographicalOrder(val*10, n, res);
    if (val%10 != 9)
    {
        _LexicographicalOrder(val+1, n, res);
    }
}
vector<int> LexicographicalOrder(int n)
{
    if (n < 0)
    {
        return vector<int>();
    }
    vector<int> res;
    _LexicographicalOrder(1, n, res);
    return res;
}

int main()
{
    int n = 17;
    
    vector<int> res = LexicographicalOrder(n);

    cout << "Lexicographical order is: " << endl;
    for (auto i : res)
    {
        cout << i << " ";
    }
    cout << endl;
    return 0;
}