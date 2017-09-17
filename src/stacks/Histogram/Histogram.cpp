#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

struct Histogram
{
    size_t height = 1;
    size_t width = 1;

    Histogram(size_t _height, size_t _width) : height(_height), width(_width)
    {}

    Histogram(size_t _height) : height(_height)
    {}
};

size_t LargestAreaInHistogram(const vector<Histogram>& hist)
{
    if (hist.empty())
    {
        return 0;
    }

    stack<size_t> hStack, pStack;
    size_t maxArea = 0, area = 0;
    size_t tempPos = 0, tempHeight = 0;
    size_t i = 0;
    for (i = 0; i < hist.size(); ++i)
    {
        auto h = hist[i].height;
        if (i == 0 || (!hStack.empty() && h >= hStack.top()))
        {
            hStack.push(h);
            pStack.push(i);
        }
        else if (!hStack.empty() && h < hStack.top())
        {
            while (!hStack.empty() && h < hStack.top())
            {
                // hstack and pstack should be in sync
                tempHeight = hStack.top();
                tempPos = pStack.top();

                area = tempHeight * (i - tempPos);
                maxArea = max(area, maxArea);

                hStack.pop();
                pStack.pop();
            }
            hStack.push(h);
            pStack.push(tempPos);
        }
    }

    while (!hStack.empty())
    {
        tempHeight = hStack.top();
        tempPos = pStack.top();

        area = tempHeight * (i - tempPos);
        maxArea = max(area, maxArea);

        hStack.pop();
        pStack.pop();
    }

    return maxArea;
}
int main()
{
    const vector<vector<Histogram>> values = {
        {{6}, {2}, {5}, {4}, {5}, {1}, {6}},
        {{1}, {3}, {2}, {1}, {2}},
    };

    for (const auto& hist : values)
    {
        cout << "For the histogram heights: " << endl;
        for (auto i : hist)
        {
            cout << i.height << " ";
        }
        cout << endl;
        auto res = LargestAreaInHistogram(hist);
        cout << "the largest area is " << res << endl;
    }
    return 0;
}