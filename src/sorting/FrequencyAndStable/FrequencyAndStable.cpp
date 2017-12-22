#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

// Sort an array by frequency and the order is to be stable
// Input:  arr[] = {2, 5, 2, 8, 5, 6, 8, 8}
// Output: arr[] = {8, 8, 8, 2, 2, 5, 5, 6}

struct Element
{
    size_t index = 0;
    int val = 0;
    size_t count = 0;

    Element(size_t _index, int _val, size_t _count) : index(_index), val(_val), count(_count)
    {}

    Element() = default;
};

bool FreqComp(const Element& a, const Element& b)
{
    if (a.count != b.count)
    {
        return a.count > b.count;
    }
    else
    {
        return a.index < b.index;
    }
}

vector<int> SortbyFrequency(const vector<int>& inputs)
{
    if (inputs.size() <= 1)
    {
        return inputs;
    }

    vector<Element> elements;
    for (size_t i = 0; i < inputs.size(); ++i)
    {
        elements.push_back(Element(i, inputs[i], 1));
    }

    stable_sort(elements.begin(), elements.end(), [](const Element& a, const Element& b)
    {
        return a.val < b.val;
    });

    vector<Element> tempElements;
    for (size_t i = 0; i < elements.size();)
    {
        Element e = elements[i];
        int val = e.val;
        size_t count = 0;
        while (i < elements.size() && val == elements[i].val)
        {
            ++count;
            ++i;
        }
        e.count = count;
        tempElements.push_back(e);
    }

    stable_sort(tempElements.begin(), tempElements.end(), FreqComp);

    vector<int> results(inputs.size());
    size_t rIndex = 0, index = 0;
    while (rIndex < inputs.size() && index < tempElements.size())
    {
        const Element& e = tempElements[index];
        int val = e.val;
        size_t count = e.count;
        while (rIndex < inputs.size() && count)
        {
            results[rIndex] = val;
            --count;
            ++rIndex;
        }
        ++index;
    }

    return results;
}

int main()
{
    vector<int> inputs = {2, 5, 2, 8, 5, 6, 8, 8};
    vector<int> results = SortbyFrequency(inputs);

    cout << "For the inputs: {";
    for (size_t i = 0; i < inputs.size(); ++i)
    {
        cout << inputs[i];
        if (i != inputs.size() - 1)
        {
            cout << ", ";
        }
    }
    cout << "}, the results after sorting by frequency are as follows" << endl;

    cout << "{";
    for (size_t i = 0; i < results.size(); ++i)
    {
        cout << results[i];
        if (i != results.size() - 1)
        {
            cout << ", ";
        }
    }
    cout << "}" << endl;

    return 0;
}