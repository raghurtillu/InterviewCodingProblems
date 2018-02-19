#include <iostream>
#include <vector>
#include <utility>
#include <cstdlib>
using namespace std;

void Shuffle(vector<int>& inputs)
{
    if (inputs.size() <= 1)
    {
        return;
    }

    size_t n = inputs.size();
    for (size_t i = 0; i < n; ++i)
    {
        auto val = (::rand() % (n - i)) + i;
        swap(inputs[i], inputs[val]);
    }
}

int main()
{
    vector<int> inputs = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    cout << "For the inputs: ";
    for (auto i : inputs)
    {
        cout << i << " ";
    }
    cout << " after shuffling, the contents are " << endl;
    
    Shuffle(inputs);
    for (auto i : inputs)
    {
        cout << i << " ";
    }
    cout << endl;
    
    return 0;
}