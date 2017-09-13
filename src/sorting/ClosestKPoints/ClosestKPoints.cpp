#include <iostream>
#include <utility>
#include <queue>
#include <vector>
#include <cmath>

using namespace std;

// Given a set of points, finds the k closest points to a given point
// This version has O(n, n^2) complexity
struct Point
{
    int x = 0;
    int y = 0;

    Point() = default;
    Point(const Point&) = default;
    Point(int _x, int _y) : x(_x), y(_y)
    {}

    static double GetDist(const Point& p1, const Point& p2)
    {
        return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
    }
};

typedef pair<double, pair<Point, Point>> DistancePair;

size_t Partition(vector<DistancePair>& inputs, size_t low, size_t high)
{
    if (inputs.empty() || low > high || high - low > inputs.size())
    {
        return SIZE_MAX;
    }

    auto pivot = inputs[high].first;

    size_t i = low-1;
    for (size_t j = low; j < high; ++j)
    {
        if (inputs[j].first < pivot)
        {
            i = i + 1;
            swap(inputs[i], inputs[j]);
        }
    }
    swap(inputs[i+1], inputs[high]);
    return i+1;
}

size_t GetRankofKthPoint(vector<DistancePair>& inputs, size_t low, size_t high, size_t k)
{
    if (k > inputs.size())
    {
        return SIZE_MAX;
    }

    auto rankofPivot = Partition(inputs, low, high);
    if (rankofPivot == SIZE_MAX)
    {
        // should not happen
        return SIZE_MAX;
    }

    if (k == rankofPivot)
    {
        // we found the kth closest point
        return rankofPivot;
    }
    else if (k < rankofPivot)
    {
        return GetRankofKthPoint(inputs, low, rankofPivot-1, k);
    }
    else
    {
        return GetRankofKthPoint(inputs, rankofPivot+1, high, k);
    }
}

vector<Point> ClosestKPoints(const vector<Point>& points, const Point& p, size_t k)
{
    if (points.empty() || k > points.size())
    {
        return vector<Point>();
    }
    
    vector<DistancePair> dist;
    for (const auto& pt : points)
    {
        auto d = Point::GetDist(pt, p);
        dist.push_back(make_pair(d, make_pair(p, pt)));
    }

    // k-1, as rank is 0 zero index based
    size_t rankofKthPoint = GetRankofKthPoint(dist, 0, dist.size()-1, k-1);
    if (rankofKthPoint == SIZE_MAX)
    {
        // should not happen
        return vector<Point>();
    }

    // Got the rank of the kth closest point:
    // all the points left of the kth point (inclusive) constitute the closest k points
    vector<Point> res;
    for (auto i = 0; i <= rankofKthPoint; ++i)
    {
        res.push_back(dist[i].second.second);
    }
    return res;
}

int main()
{
 
    vector<pair<vector<Point>, pair<Point, size_t>>> inputs =
    {
        make_pair<vector<Point>, pair<Point, size_t>>(
            {Point(1, 2), Point(2, 3), Point(4, 6), Point(7, 9), Point(1, 6)},
            make_pair<Point, size_t>(Point(2, 2), 2)),
        make_pair<vector<Point>, pair<Point, size_t>>(
            {Point(1, 2), Point(2, 3), Point(4, 6), Point(7, 9), Point(1, 6)},
            make_pair<Point, size_t>(Point(3, 4), 3)),
        make_pair<vector<Point>, pair<Point, size_t>>(
            {Point(1, 2)},
            make_pair<Point, size_t>(Point(3, 4), 1)),
    
    };
    
    for (const auto keyValPair : inputs)
    {
        const auto& pointsVector = keyValPair.first;
        cout << "For the points: " << endl;
        for (auto pt : pointsVector)
        {
            cout << "(" << pt.x << " ," << pt.y << ") ";
        }
        const auto& originPoint = keyValPair.second.first;
        const auto k = keyValPair.second.second;

        cout << "the closest " << k << " point(s) to ";
        cout << "(" << originPoint.x << " ," << originPoint.y << ") are " << endl;
        
        auto res = ClosestKPoints(pointsVector, originPoint, k);
        for (auto pt : res)
        {
            cout << "(" << pt.x << " ," << pt.y << ") ";
        }
        cout.flush();
        cout << endl;
   }
   
    return 0;
}