# pragma once
#include <atomic>
#include <mutex>
#include <queue>
#include <condition_variable>

template <typename T>
class ThreadSafeQueue
{
    std::atomic_bool valid {true};
    mutable std::mutex lock;
    std::condition_variable signal;
    std::queue<T> tsQ;

public:
    void invalidate();
    bool isEmpty() const;
    bool isValid() const;
    void clear();
    bool tryPop(T& element);
    bool waitPop(T& element);
    void push(T element);
    ~ThreadSafeQueue()
    {
        invalidate();
    }
};

