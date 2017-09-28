#include <iostream>
#include <vector>
#include <utility>
using namespace std;

struct Building
{
    int x1 = 0;
    int x2 = 0;
    int h = 0;
    Building(int _x1, int _x2, int _h) : x1(_x1), x2(_x2), h(_h)
    {}
};

struct KeyPoint
{
    int x = 0;
    int y = 0;

    KeyPoint() = default;
    KeyPoint(int _x, int _y) : x(_x), y(_y)
    {}
};

vector<KeyPoint> MergeSkylines(const vector<KeyPoint>& skylineLeft, const vector<KeyPoint>& skylineRight)
{
    int h1 = 0, h2 = 0;
    vector<KeyPoint> mergedSkylines;
    size_t lIndex = 0, rIndex = 0;

    while (lIndex < skylineLeft.size() && rIndex < skylineRight.size())
    {
        KeyPoint merged;

        // get key points from both the skylines
        const auto& kp1 = skylineLeft[lIndex];
        const auto& kp2 = skylineRight[rIndex];

        // comparing x coordinates of current key points of both the skylines
        if (kp1.x < kp2.x)
        {
            // 0: x coordinate, 1: height
            merged.x = kp1.x;
            merged.y = kp1.y;

            // if y coordinate for key point from skylineLeft is less than last seen height of skylineRight
            // then we need to update merged key point's y coordinate to last seen height of skylineRight
            if (kp1.y < h2)
            {
                merged.y = h2;
            }

            // update the last seen height for skylineLeft
            // note that last seen height for skylineRight is not updated 
            h1 = kp1.y;
            ++lIndex;
        }
        else if (kp2.x < kp1.x)
        {
            merged.x = kp2.x;
            merged.y = kp2.y;
            if (kp2.y < h1)
            {
                merged.y = h1;
            }
            h2 = kp2.y;
            ++rIndex;
        }
        else
        {
            // if x coordinates of key points for both skylines are same
            // then choose the key point with greater y value
            // advance key points for both and hence update last seen height for both
            merged.x = kp1.x;
            merged.y = max(kp1.y, kp2.y);
            h1 = kp1.y;
            h2 = kp2.y;
            ++lIndex;
            ++rIndex;
        }
        mergedSkylines.push_back(merged);
    }

    while (lIndex < skylineLeft.size())
    {
        mergedSkylines.push_back(skylineLeft[lIndex++]);
    }
    while (rIndex < skylineRight.size())
    {
        mergedSkylines.push_back(skylineRight[rIndex++]);
    }

    // remove redundant key points from merged skyline if any
    size_t current = 0;
    while (current < mergedSkylines.size())
    {
        bool dupFound = true;
        while (current < mergedSkylines.size() - 1 && dupFound)
        {
            if (mergedSkylines[current].y == mergedSkylines[current+1].y)
            {
                mergedSkylines.erase(mergedSkylines.begin() + current + 1);
            }
            else
            {
                dupFound = false;
            }
        }
        current++;
    }
    return mergedSkylines;
}

vector<KeyPoint> GetSkyline(const vector<Building>& buildings, size_t low, size_t high)
{
    if (buildings.empty() || low > high || high - low > buildings.size())
    {
        return vector<KeyPoint>();
    }
    else if (low == high)
    {
        // base case
        // if there is only one building, only two key points define the skyline for it
        auto x1 = buildings[low].x1;
        auto x2 = buildings[low].x2;
        auto h = buildings[low].h;

        KeyPoint kp1(x1, h); // first key point
        KeyPoint kp2(x2, 0); // second key point

        return {kp1, kp2};
    }

    size_t mid = low + ((high - low) / 2);

    vector<KeyPoint> skyLineLeft = GetSkyline(buildings, low, mid);
    vector<KeyPoint> skyLineRight = GetSkyline(buildings, mid+1, high);

    vector<KeyPoint> mergedSkylines = MergeSkylines(skyLineLeft, skyLineRight);
    return mergedSkylines;
}

int main()
{
    vector<Building> buildings = 
    {
        {2, 9, 10}, 
        {3, 6, 15}, 
        {5, 12, 12}, 
        {13, 16, 10}, 
        {13, 16, 10}, 
        {15, 17, 5},
    };
    cout << "For the buildings: " << endl;
    for (const auto& val : buildings)
    {
        cout << "(" << val.x1 << "," << val.x2 << "," << val.h << ") ";
    }
    cout << endl;
    cout << "the skyline would look like: " << endl;
    auto res = GetSkyline(buildings, 0, buildings.size()-1);
    for (const auto& val : res)
    {
        cout << "(" << val.x << "," << val.y << ") ";
    }
    cout << endl;
    return 0;
}