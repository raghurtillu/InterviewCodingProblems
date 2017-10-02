#include <iostream>
#include <thread>

using namespace std;

int factorial(int n)
{
    int res = 1;
    for (auto i = n; i > 1; --i)
    {
        res *= i;
    }
    cout << "Factorial of " << n << " is " << res << endl;
    return res;
}
int main()
{
    thread t1(factorial, 5);
    t1.join();
    return 0;
}