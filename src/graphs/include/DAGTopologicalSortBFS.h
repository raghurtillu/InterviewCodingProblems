#pragma once
#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>
#include "Graph.h"
#include "Edge.h"
#include "Vertex.h"

class DAGTopologicalSortBFS
{
    const Graph& graph;
    std::vector<const std::shared_ptr<Vertex>> tsOrder;

public:
    DAGTopologicalSortBFS(const Graph& g) : graph(g)
    {
        std::unordered_map<const std::shared_ptr<Vertex>, size_t, VertexHash> vertexInDegree;
        // calculate degree of each vertex
        std::vector<const std::shared_ptr<Vertex>> vertices = graph.getVertices();
        for (size_t i = 0; i < vertices.size(); ++i)
        {
            auto adjIterator = graph.getIterator(vertices[i]);
            for (auto e = adjIterator->beg(); !(adjIterator->end()); e = adjIterator->nxt())
            {
                if (!e) { continue; }
                vertexInDegree[e->Destination()]++;
            }
        }

        std::queue<const std::shared_ptr<Vertex>> tsQueue;
        for (size_t i = 0; i < vertices.size(); ++i)
        {
            if (vertexInDegree[vertices[i]] == 0)
            {
                tsQueue.push(vertices[i]);
            }
        }

        while (!tsQueue.empty())
        {
            auto v = tsQueue.front();
            tsQueue.pop();
            tsOrder.push_back(v);

            auto adjIterator = graph.getIterator(v);
            for (auto e = adjIterator->beg(); !(adjIterator->end()); e = adjIterator->nxt())
            {
                if (!e) { continue; }
                if (--vertexInDegree[e->Destination()] == 0)
                {
                    tsQueue.push(e->Destination());
                }
            }
        }
    }
    const std::shared_ptr<Vertex> operator[] (size_t v) const
    {
        if (v >= graph.NumVertices())
        {
            throw std::invalid_argument("Invalid value " + std::to_string(v) + 
                "specified, the graph has " + std::to_string(graph.NumVertices()) + " vertices.");
        }
        else if (v >= tsOrder.size())
        {
            throw std::logic_error("Unable to retrieve the vertex associated with the order: " + std::to_string(v));
        }
        return tsOrder[v];
    }
};
