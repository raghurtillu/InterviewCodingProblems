#include <iostream>
#include <vector>
using namespace std;

// Divide two integers without using multiplication, division or modulo operators
// 
int divide(int dividend, int divisor) 
{
    if (divisor == 0 || (dividend == INT_MIN && divisor == -1))
    {
        return INT_MAX;
    }    
    bool sign = (dividend < 0) ^ (divisor < 0);
    long long dvd = abs(dividend);
    long long dvs = abs(divisor);
    int res = 0;
    while (dvd >= dvs)
    { 
        long long temp = dvs, multiple = 1;
        while (dvd >= (temp << 1))
        {
            temp <<= 1;
            multiple <<= 1;
        }
        dvd -= temp;
        res += multiple;
    }
    return sign ? -res : res;
}
int main()
{
    vector<pair<int, int>> inputs = 
    {
        {15, 3},
        {-5, 3},
        {5, 11},
        {1378, 2},
        {-33, -4},
        {-17, 1},
    };

    cout << "Division without divide, multiplication or modulo operators: " << endl;
    for (const auto& p: inputs)
    {
        int dividend = p.first;
        int divisor = p.second;
        cout << dividend << "/" << divisor << ": " << divide(dividend, divisor) << endl;
    }
    return 0;
}
