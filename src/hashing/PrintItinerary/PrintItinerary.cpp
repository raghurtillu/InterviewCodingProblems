#include <iostream>
#include <unordered_map>
#include <unordered_set>
using namespace std;

// Given a list of tickets, find itinerary in order using the given list
// Input:
// "Chennai" -> "Banglore"
// "Bombay" -> "Delhi"
// "Goa"    -> "Chennai"
// "Delhi"  -> "Goa"

// Output: 
// Bombay->Delhi, Delhi->Goa, Goa->Chennai, Chennai->Banglore

void PrintItinerary(const unordered_map<string, string> tickets)
{
    if (tickets.empty())
    {
        return;
    }

    unordered_set<string> lookup(tickets.size());
    for (const auto iter : tickets)
    {
        lookup.insert(iter.second);
    }

    string start;
    for (const auto iter : tickets)
    {
        if (lookup.find(iter.first) == lookup.cend())
        {
            start = iter.first;
            break;
        }
    }
    if (start.empty())
    {
        cout << "Invalid itinerary" << endl;
        return;
    }

    while (true)
    {
        const auto iter = tickets.find(start);
        if (iter == tickets.cend())
        {
            break;
        }
        const string& destination = iter->second;
        cout << start << " - " << destination << endl;
        start = destination;
    }
}

int main()
{
    const unordered_map<string, string> tickets =
    {
        { "Chennai", "Banglore" },
        { "Bombay", "Delhi" },
        { "Goa", "Chennai" },
        { "Delhi", "Goa" },
    };
    cout << "For the tickets: " << endl;
    for (const auto iter : tickets)
    {
        cout << iter.first << " - " << iter.second << endl;
    }
    cout << endl;
    cout << "the itinerary is as follows: " << endl;
    PrintItinerary(tickets);
    return 0;
}