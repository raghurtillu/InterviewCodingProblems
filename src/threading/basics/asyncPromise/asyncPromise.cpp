#include <iostream>
#include <thread>
#include <future>
using namespace std;

int factorial(future<int>& f)
{
    int n = f.get();
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
    promise<int> threadPromise;
    future<int> threadFuture = threadPromise.get_future();

    future<int> fu = async(launch::async, factorial, ref(threadFuture));
    
    // do some work
    // ....

    threadPromise.set_value(5);
    int result = fu.get();
    cout << "Factorial of " << n << " is " << result << endl;
    return 0;
}