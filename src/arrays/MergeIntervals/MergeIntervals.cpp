#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct Interval 
{
    int start = 0;
    int end = 0;

    Interval() = default;
    Interval(int _start, int _end) : start(_start), end(_end)
    {} 
};

vector<Interval> MergeOverlappedIntervals(vector<Interval> intervals)
{
    if (intervals.empty())
    {
        return intervals;
    }

    // sort the intervals based on start time
    sort(intervals.begin(), intervals.end(), [](const Interval& a, const Interval& b)
    {
        return a.start < b.start;
    });

    vector<Interval> merged = { intervals[0] };
    for (size_t i = 1; i < intervals.size(); ++i)
    {
        auto& last = merged.back();
        if (intervals[i].start < last.end)
        {
            // overlap
            last.end = max(last.end, intervals[i].end);
        }
        else
        {
            // no overlap
            merged.push_back(intervals[i]);
        }
    }

    return merged;
}

int main()
{
    vector<vector<Interval>> values = 
    {
        { {6,8}, {2,4}, {4,7}, {7,9} },
        { {2,4}, {1,3}, {6,8}, {5,7} },
        { {1,3}, {4,9}, {3,10} },
    };

    for (const auto& inputs : values)
    {
        cout << "For the inputs: " << endl;
        for (size_t i = 0; i < inputs.size(); ++i)
        {
            cout << "{" << inputs[i].start << "," << inputs[i].end << "} ";
        }
        cout << endl;
    
        auto res = MergeOverlappedIntervals(inputs);
        cout << "the merged intervals are: ";
        for (size_t i = 0; i < res.size(); ++i)
        {
            cout << "{" << res[i].start << "," << res[i].end << "} ";
        }
        cout << endl;
    }
    
    return 0;
}