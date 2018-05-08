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

// TODO: revisit the signature of this function
std::vector<size_t> WalkTree(const std::shared_ptr<Search>& search, 
    std::shared_ptr<Vertex> v,
    std::unordered_set<size_t>& visitedVertices)
{
    if (!v) { return {}; }

    std::vector<size_t> ancestors;

    ancestors.push_back(v->getId());
    visitedVertices.insert(v->getId());
    
    while (true)
    {
        const auto& parent = search->Parent(v);
        if (v->getId() == parent->getId())
        {
            break;
        }
        ancestors.push_back(parent->getId());
        visitedVertices.insert(parent->getId());
        v = parent;
    }
    return ancestors;
}

// Walks the search tree from a given vertex to its root
std::vector<size_t> WalkTree(const std::shared_ptr<Search>& search, std::shared_ptr<Vertex> v)
{
    std::unordered_set<size_t> visitedVertices;
    return WalkTree(search, v, visitedVertices);
}
