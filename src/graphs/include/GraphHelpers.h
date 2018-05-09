#pragma once
#include <unordered_set>
#include "Graph.h"
#include "Edge.h"
#include "Vertex.h"
#include "SparseGraph.h"
#include "Search.h"

Graph& Graph::getGraph(bool isDirected)
{
    Graph *pGraph = new SparseGraph(isDirected);
    return *pGraph;
}

// Given a vertex, walks the search tree to get its list of ancestors
std::vector<std::shared_ptr<Vertex>> WalkTree(const std::shared_ptr<Search>& search, std::shared_ptr<Vertex> v)
{
    if (!v) { return {}; }

    std::vector<std::shared_ptr<Vertex>> ancestors;
    ancestors.push_back(v);
    while (true)
    {
        const auto& parent = search->Parent(v);
        if (v == parent)
        {
            break;
        }
        ancestors.push_back(parent);
        v = parent;
    }
    return ancestors;
}