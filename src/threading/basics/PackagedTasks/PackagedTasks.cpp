#include <iostream>
#include <mutex>
#include <deque>
#include <condition_variable>
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

deque<packaged_task<int()>> taskQ;
mutex mu;
condition_variable cond;

void thread_1()
{
    packaged_task<int()> t;
    
    {
        unique_lock<mutex> locker(mu);
        cond.wait(locker, [](){ return !taskQ.empty(); });
        t = move(taskQ.front());
        taskQ.pop_front();
    }
    
    t();
}

int main()
{
    int n = 6;
    thread t1(thread_1);
    packaged_task<int()> threadPackagedTask(bind(factorial, n));
    future<int> threadFuture = threadPackagedTask.get_future();
    
    {
        unique_lock<mutex> locker(mu);
        taskQ.push_back(move(threadPackagedTask));
        cond.notify_one();
    }

    int result = threadFuture.get();
    cout << "Factorial of " << n << " is " << result << endl;
    t1.join();
    return 0;
}