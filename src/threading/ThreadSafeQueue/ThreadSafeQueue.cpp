#include <iostream>
#include <chrono>
#include <thread>
#include "ThreadSafeQueue.hpp"
using namespace std;

template<typename T>
void ThreadSafeQueue<T>::invalidate()
{
    lock_guard<mutex> locker(lock);
    valid = false;
    signal.notify_all();

}

template <typename T>
bool ThreadSafeQueue<T>::isEmpty() const
{
    lock_guard<mutex> locker(lock);
    return tsQ.empty();
}

template <typename T>
bool ThreadSafeQueue<T>::isValid() const
{
    lock_guard<mutex> locker(lock);
    return valid;
}

template<typename T>
void ThreadSafeQueue<T>::clear()
{
    lock_guard<mutex> locker(lock);
    while (!tsQ.empty())
    {
        tsQ.pop();
    }
    signal.notify_all();
}

template<typename T>
bool ThreadSafeQueue<T>::tryPop(T& element)
{
    lock_guard<mutex> locker(lock);
    if (tsQ.empty() || !valid)
    {
        return false;
    }
    element = move(tsQ.front());
    tsQ.pop();
    return true;
}

template<typename T>
bool ThreadSafeQueue<T>::waitPop(T& element)
{
    unique_lock<mutex> locker(lock);
    signal.wait(locker, [this]() {
        return !tsQ.empty() || !valid;
    });
    if (!valid)
    {
        return false;
    }
    element = move(tsQ.front());
    tsQ.pop();
    return true;
}

template<typename T>
void ThreadSafeQueue<T>::push(T element)
{
    lock_guard<mutex> locker(lock);
    tsQ.push(move(element));
    signal.notify_one();
}

mutex printLock;
bool g_done = false;

void thread1_fn(ThreadSafeQueue<int>& q)
{
    for (size_t i = 0; i < 10; ++i)
    {
        {
            q.push(i);
            lock_guard<mutex> locker(printLock);
            std::cout << "thread " << this_thread::get_id() << ": inserting " 
            << i << " into queue" << endl;    
        }
    }
}

void thread2_fn(ThreadSafeQueue<int>& q)
{
    while (q.isValid())
    {
        int i = 0;
        bool res = q.waitPop(i);
        if (!res)
        {
            break;
        }
        {
            std::this_thread::sleep_for(std::chrono::nanoseconds(1));
            lock_guard<mutex> locker(printLock);
            std::cout << "thread " << this_thread::get_id() << ": popped " 
            << i << " from queue" << endl;        
        }
    }
}

int main()
{
    ThreadSafeQueue<int> q;
    thread t1(thread1_fn, ref(q));
    thread t2(thread2_fn, ref(q));

    g_done = true;
    t1.join();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    q.invalidate();
    t2.join();
    return 0;
}