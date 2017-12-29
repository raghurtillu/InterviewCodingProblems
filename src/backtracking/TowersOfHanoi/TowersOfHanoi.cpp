#include <iostream>
#include <vector>
#include <string>
using namespace std;

enum Towers { From = 1, To, Via };

struct DiskMovement
{
    size_t diskNum = 0;
    Towers src = From;
    Towers dest = To;

    DiskMovement(size_t _diskNum, Towers _src, Towers _dest) : diskNum(_diskNum), src(_src), dest(_dest)
    {}
    DiskMovement() = default;
};

string getTowerTypeAsString(Towers tower)
{
    switch (tower)
    {
        case From :
            return "From";
        case To :
            return "To";
        case Via : 
            return "Via";
    }
    return "";
}

vector<DiskMovement> _TowersOfHanoi(size_t numDisks, size_t diskIndex, Towers from, Towers to, Towers via)
{
    if (numDisks == 0)
    {
        return { DiskMovement() };
    }
    else if (numDisks == 1)
    {
        return { DiskMovement(diskIndex, from, to) };
    }

    vector<DiskMovement> l1 = _TowersOfHanoi(numDisks-1, diskIndex - 1, from, via, to);
    vector<DiskMovement> l2 = _TowersOfHanoi(1, diskIndex, from, to, via);
    vector<DiskMovement> l3 = _TowersOfHanoi(numDisks-1, diskIndex - 1, via, to, from);

    // append all the disk movements
    l1.insert(l1.end(), l2.begin(), l2.end());
    l1.insert(l1.end(), l3.begin(), l3.end());

    return l1;
}

vector<DiskMovement> TowersOfHanoi(size_t numDisks)
{
    Towers from = From;
    Towers to = To;
    Towers via = Via;

    size_t diskIndex = numDisks;
    return _TowersOfHanoi(numDisks, diskIndex, from, to, via);
}

int main()
{
    vector<size_t> inputs = 
    {
        1,
        2,
        3,
        4,
    };

    for (size_t i = 0; i < inputs.size(); ++i)
    {
        size_t numDisks = inputs[i];
        cout << "For " << numDisks << " disk(s), the disk movements are as follows: " << endl;
        vector<DiskMovement> results = TowersOfHanoi(numDisks);
        for (const auto& movements : results)
        {
            auto diskNum = movements.diskNum;
            const auto& src = getTowerTypeAsString(movements.src);
            const auto& dest = getTowerTypeAsString(movements.dest);

            cout << "Move disk# " << diskNum << ", " << src << " -> " << dest << endl;
        }
        cout << endl;
        cout << "Total number of disk movements: " << results.size() << endl;
        cout << endl;
    }

    return 0;
}