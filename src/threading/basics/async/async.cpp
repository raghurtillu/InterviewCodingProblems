#include <iostream>
#include <thread>
#include <future>
using namespace std;

int factorial(int n)
{
    int res = 1;
    for (auto i = n; i > 1; --i)
    {
        res *= i;
    }
    return res;
}

int main()
{
    int n = 5;
    future<int> fu = async(launch::async, factorial, n);
    int result = fu.get();
    cout << "Factorial of " << n << " is " << result << endl;
    return 0;
}