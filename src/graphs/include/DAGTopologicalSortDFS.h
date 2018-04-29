#pragma once
#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include "Graph.h"
#include "Edge.h"
#include "Vertex.h"

class DAGTopologicalSortDFS
{
    const Graph& graph;
    size_t postOrderCount = 0;
    std::unordered_set<size_t> visited;
    std::unordered_map<size_t, std::shared_ptr<Vertex>> postOrder;
    std::vector<const std::shared_ptr<Vertex>> tsOrder;
    
    virtual void TopologicalSort(const std::shared_ptr<Vertex>& v)
    {
        visited.insert(v->getId());
        auto adjIterator = graph.getIterator(v);
        for (auto e = adjIterator->beg(); !(adjIterator->end()); e = adjIterator->nxt())
        {
            if (!e) { continue; }
            size_t w = e->Destination()->getId();
            if (visited.find(w) == visited.cend())
            {
                TopologicalSort(e->Destination());
            }
        }
        postOrder[postOrderCount++] = v;
    }

public:
    DAGTopologicalSortDFS(const Graph& g) : graph(g)
    { 
        std::vector<const std::shared_ptr<Vertex>> vertices = graph.getVertices();
        for (size_t i = 0; i < vertices.size(); ++i)
        {
            if (visited.find(vertices[i]->getId()) == visited.cend())
            {
                TopologicalSort(vertices[i]);
            }
        }
        
        // the order in DFS topological sort is actually in reverse order
        for (size_t i = postOrderCount - 1; i != SIZE_MAX; --i)
        {
            tsOrder.push_back(std::move(postOrder[i]));
        }
        postOrder.clear();
    }
    const std::shared_ptr<Vertex> operator[] (size_t v) const
    {
        if (v >= graph.NumVertices())
        {
            throw std::invalid_argument("Invalid value " + std::to_string(v) + 
                " specified, the graph has " + std::to_string(graph.NumVertices()) + " vertices.");
        }
        else if (v >= tsOrder.size())
        {
            throw std::logic_error("Unable to retrieve the vertex associated with the order: " + std::to_string(v));
        }
        return tsOrder[v];
    }
};