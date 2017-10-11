#include <iostream>
using namespace std;

// only works for positive powers of x
int Pow(int x, size_t n)
{
    if (x == 0 || x == 1)
    {
        return x;
    }
    else if (n == 0)
    {
        return 1;
    }
    
    if (n & 1)
    {
        // n is odd
        return x * Pow(x, n/2) * Pow(x, n/2);
    }
    else
    {
        // n is even
        return Pow(x, n/2) * Pow(x, n/2);
    }
}

// only works for positive powers of x
int Pow_Opt(int x, size_t n)
{
    if (x == 0 || x == 1)
    {
        return x;
    }
    else if (n == 0)
    {
        return 1;
    }

    auto temp = Pow(x, n/2);
    if (n & 1)
    {
        return x * temp * temp;
    }
    else
    {
        return temp * temp;
    }
}

// works for positive or negative powers of x
float Pow_AdvOpt(int x, int n)
{
    if (x == 0 || x == 1)
    {
        return x;
    }
    else if (n == 0)
    {
        return 1;
    }

    auto temp = Pow_AdvOpt(x, n/2);
    if (n % 2 == 0)
    {
        return temp * temp;
    }
    else
    {
        if (n > 0)
        {
            return x * temp * temp;
        }
        else
        {
            return (temp * temp) / x;
        }
    }
}

int main()
{
    int x = 5;
    int n = 3;

    cout << "Power of " << x << " and " << n << ": " << Pow(x, n) << endl;
    n = 5;
    cout << "Power of " << x << " and " << n << ": " << Pow_Opt(x, n) << endl;
    n = -3;
    cout << "Power of " << x << " and " << n << ": " << Pow_AdvOpt(x, n) << endl;
    return 0;
}