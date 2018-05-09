#include <iostream>
#include <memory>
#include <vector>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include "../include/GraphHelpers.h"
#include "../include/DfsDirected.h"
#include "../include/DAGDfs.h"
#include "../include/DAGTopologicalSortBFS.h"
using namespace std;

// given a vertex id, gets the index of the matching vertex id from a list of vertices
static size_t getVertexIndex(const std::vector<std::shared_ptr<Vertex>>& vertices, size_t id)
{
    for (size_t i = 0; i < vertices.size(); ++i)
    {
        if (id == vertices[i]->getId()) { return i; }
    }
    return SIZE_MAX;
}

int main()
{
    Graph& graph = Graph::getGraph(true);

    vector<shared_ptr<Vertex>> vertices;
    for (auto i = 0; i < 10; ++i) { vertices.emplace_back(make_shared<Vertex>("")); }
    vector<double> wt(vertices.size(), 0.0);
    vector<shared_ptr<Edge>> edges = 
    {
        make_shared<Edge>(vertices[0], vertices[1], 0.41),
        make_shared<Edge>(vertices[0], vertices[7], 0.41),
        make_shared<Edge>(vertices[0], vertices[9], 0.41),
        make_shared<Edge>(vertices[1], vertices[2], 0.51),
        make_shared<Edge>(vertices[2], vertices[2], 0.50),
        make_shared<Edge>(vertices[3], vertices[3], 0.36),
        make_shared<Edge>(vertices[4], vertices[4], 0.38),
        make_shared<Edge>(vertices[5], vertices[5], 0.45),
        make_shared<Edge>(vertices[6], vertices[3], 0.21),
        make_shared<Edge>(vertices[6], vertices[8], 0.21),
        make_shared<Edge>(vertices[7], vertices[3], 0.32),
        make_shared<Edge>(vertices[7], vertices[8], 0.32),
        make_shared<Edge>(vertices[8], vertices[2], 0.32),
        make_shared<Edge>(vertices[9], vertices[4], 0.29),
        make_shared<Edge>(vertices[9], vertices[6], 0.29),
    };
    for (const auto& edge : edges) { graph.Insert(edge); }

    shared_ptr<DAGDfs> search = make_shared<DAGDfs>(graph);
    auto tsVertices = search->GetTopologicalOrder();
    cout << "Topological sort: ";
    for (const auto& it : tsVertices)
    {
        cout << it->getId() << " ";
    }
    cout << endl;

    unordered_map<size_t, shared_ptr<Vertex>> lookup;
    for (size_t i = 0; i < tsVertices.size(); ++i)
    {
        auto adjIterator = graph.getIterator(tsVertices[i]);
        for (auto e = adjIterator->beg(); !(adjIterator->end()); e = adjIterator->nxt())
        {
            if (!e) { continue; }
            size_t v = e->Source()->getId();
            size_t w = e->Destination()->getId();
            if (wt[w] < wt[v] + e->Weight())
            {
                wt[w] = wt[v] + e->Weight();
                if (v != w)
                {
                    lookup[w] = e->Source();
                }
            }
        }
    }
    size_t maxPathWeightVertexId = 0;
    double maxPathWeight = 0;
    cout << "Vertex path weights" << endl;
    for (size_t i = 0; i < wt.size(); ++i)
    {
        cout << i << ": " << wt[i] << endl;
        if (wt[i] > wt[maxPathWeightVertexId])
        {
            maxPathWeightVertexId = i;
            maxPathWeight = wt[i];
        }
    }
    cout << "Weight of the longest path in the DAG: " << maxPathWeight << endl;
    size_t index = getVertexIndex(vertices, maxPathWeightVertexId);
    if (index == SIZE_MAX)
    {
        cout << "An error occurred while getting the vertex associated with identifier: " 
            << maxPathWeightVertexId << endl;
        return 1;
    }
    
    size_t vId = vertices[index]->getId();
    vector<size_t> ancestors = { vId };
    while (true)
    {
        if (lookup.find(vId) == lookup.cend() || lookup[vId]->getId() == vId)
        {
            break;
        }
        size_t parentId = lookup[vId]->getId();
        ancestors.push_back(parentId);
        vId = parentId;
    }
    
    cout << "Longest path: ";
    for (size_t i = 0; i < ancestors.size(); ++i)
    {
        cout << ancestors[i];
        if (i != ancestors.size() - 1)
        {
            cout << " -> ";
        }
    }
    cout << endl;
    return 0;
}