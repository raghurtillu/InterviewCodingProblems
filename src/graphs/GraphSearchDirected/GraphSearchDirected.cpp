#include <iostream>
#include <memory>
#include <vector>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include "../include/GraphHelpers.h"
#include "../include/DfsDirected.h"
using namespace std;

int main()
{
    Graph& graph = Graph::getGraph(true);
    
    vector<shared_ptr<Vertex>> vertices;
    for (auto i = 0; i < 13; ++i) { vertices.emplace_back(make_shared<Vertex>("")); }

    vector<shared_ptr<Edge>> edges = 
    {
        make_shared<Edge>(vertices[0], vertices[1]),
        make_shared<Edge>(vertices[0], vertices[5]),
        make_shared<Edge>(vertices[0], vertices[6]),
        make_shared<Edge>(vertices[2], vertices[0]),
        make_shared<Edge>(vertices[2], vertices[3]),
        make_shared<Edge>(vertices[3], vertices[2]),
        make_shared<Edge>(vertices[3], vertices[5]),
        make_shared<Edge>(vertices[4], vertices[2]),
        make_shared<Edge>(vertices[4], vertices[3]),
        make_shared<Edge>(vertices[4], vertices[11]),
        make_shared<Edge>(vertices[5], vertices[4]),
        make_shared<Edge>(vertices[6], vertices[4]),
        make_shared<Edge>(vertices[6], vertices[9]),
        make_shared<Edge>(vertices[7], vertices[6]),
        make_shared<Edge>(vertices[7], vertices[8]),
        make_shared<Edge>(vertices[8], vertices[7]),
        make_shared<Edge>(vertices[8], vertices[9]),
        make_shared<Edge>(vertices[9], vertices[10]),
        make_shared<Edge>(vertices[9], vertices[11]),
        make_shared<Edge>(vertices[10], vertices[12]),
        make_shared<Edge>(vertices[11], vertices[12]),
        make_shared<Edge>(vertices[12], vertices[9]),
    };
    for (const auto& edge : edges) { graph.Insert(edge); }

    shared_ptr<Search> search = make_shared<DfsDirected>(graph);
    unordered_set<size_t> visitedVertices;
    auto searchVertices = graph.getVertices();

    // for (const auto& it : searchVertices)
    // {
    //     auto id = it->getId();
    //     if (visitedVertices.find(id) != visitedVertices.cend()) { continue; }

    //     vector<size_t> ancestors = WalkTree(search, it, visitedVertices);
    //     for (size_t i = 0; i < ancestors.size(); ++i)
    //     {
    //         cout << ancestors[i];
    //         if (i != ancestors.size() - 1)
    //         {
    //             cout << " -> ";
    //         }
    //     }
    //     cout << endl;
    // }

    cout << "Number of connected components: " << search->NumberOfConnectedComponents() << endl;
    search->hasCycle() ? cout << "The graph has a cycle" : cout << "The graph does not have a cycle";
    cout << endl;
   return 0;
}