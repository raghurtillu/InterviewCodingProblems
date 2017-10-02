#include <iostream>
using namespace std;

template <typename... Args>
void AddRange(Args... args)
{
    const int size = sizeof...(args);
    cout << "Number of args:" << size << endl;
}

int main()
{
    int x = 0, y = 0, z = 0;
    AddRange(x, y, z);
    return 0;
}