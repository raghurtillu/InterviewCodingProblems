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

int ElementForRank(vector<int>& inputs, size_t low, size_t high, size_t rank)
{
    if (rank >= inputs.size())
    {
        return INT_MIN;
    }
    
    size_t mid = low + ((high - low) >> 1);
    size_t rankofPivot = Partition(inputs, low, high);
    if (rankofPivot == SIZE_MAX)
    {
        // should not happen
        return INT_MIN;
    }
    
    if (rank == rankofPivot)
    {
        // found the element corresponding to the rank
        return inputs[rankofPivot];
    }
    else if (rank < rankofPivot)
    {
        return ElementForRank(inputs, low, mid, rank);
    }
    else
    {
        return ElementForRank(inputs, mid+1, high, rank);
    }
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
    for (auto rank = 0; rank < inputs.size(); ++rank)
    {
        auto tempVector = inputs;
        cout << "value of element at rank " << rank << " is ";
        auto element = ElementForRank(tempVector, 0, tempVector.size()-1, rank);
        cout << element << endl;
    }
    
	return 0;
}
