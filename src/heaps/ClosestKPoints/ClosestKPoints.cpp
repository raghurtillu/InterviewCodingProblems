#include <iostream>
#include <utility>
#include <queue>
#include <vector>
#include <cmath>

using namespace std;

// Given a set of points, finds the k closest points to a given point
// This version has O(nlogk) complexity

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

    auto comp = [](const DistancePair& dp1, const DistancePair& dp2) {
        return dp1.first < dp2.first;
    };

    priority_queue<DistancePair, vector<DistancePair>, decltype(comp)> pq(comp);

    size_t i = 0;
    for (i = 0; i < k; ++i)
    {
        pq.push(dist[i]);
    }

    for (; i < dist.size(); ++i)
    {
        auto d = dist[i].first;
        if (d < pq.top().first)
        {
            pq.pop();
            pq.push(dist[i]);
        }
    }

    vector<Point> res;
    while (!pq.empty())
    {
        res.push_back(pq.top().second.second);
        pq.pop();
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
        cout << endl;
   }
   
    return 0;
}