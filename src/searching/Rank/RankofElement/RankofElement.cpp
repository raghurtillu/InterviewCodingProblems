#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

size_t Partition(vector<int>& inputs, size_t low, size_t high)
{
    if (inputs.empty() || low > high || high - low > inputs.size())
    {
        return SIZE_MAX;
    }

    auto pivot = inputs[high];
    
    size_t i = low-1;
    for (size_t j = low; j < high; ++j)
    {
        if (inputs[j] <= pivot)
        {
            i++;
            swap(inputs[j], inputs[i]);
        }
    }
    swap(inputs[i+1], inputs[high]);
    return i + 1;
}

size_t FindRankofElement(vector<int>& inputs, size_t low, size_t high, size_t indexofElement)
{
    if (indexofElement >= inputs.size())
    {
        return SIZE_MAX;
    }
    
    swap(inputs[indexofElement], inputs[high]);
    return Partition(inputs, low, high);
}

int main()
{
    vector<int> inputs = {12, 11, 13, 5, 6, 7};
    
    cout <<"For the inputs " << endl;
    for (auto i : inputs)
    {
        cout << i << " ";
    }
    cout << endl;

    for (auto indexofElement = 0; indexofElement < inputs.size(); ++indexofElement)
    {
        auto tempVector = inputs;
        cout << "rank of element " << tempVector[indexofElement] << " is ";
        size_t rank = FindRankofElement(tempVector, 0, tempVector.size()-1, indexofElement);
        cout << rank << endl;
    }
    
    return 0;
}
