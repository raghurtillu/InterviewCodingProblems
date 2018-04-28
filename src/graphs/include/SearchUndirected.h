#pragma once
#include <vector>
#include <unordered_map>
#include "Graph.h"
#include "Edge.h"
#include "Search.h"
#include "Vertex.h"

// provides the search interface for a given graph
class SearchUndirected : public Search
{
protected:
    size_t count = 0, cCount = 0;
    void SearchGraph()
    {
        std::vector<const std::shared_ptr<Vertex>> vertices = graph.getVertices();
        for (size_t i = 0; i < vertices.size(); ++i)
        {
            if (lookup.find(i) == lookup.cend())
            {
                // add a dummy self edge
                auto dummyVertex = vertices[i];
                std::shared_ptr<Edge> dummyEdge = std::make_shared<Edge>(dummyVertex, dummyVertex);
                SearchComponent(dummyEdge);
                ++cCount;
            }
        }
        SearchInfo::connectedComponentCount = cCount;
    }
    SearchUndirected(const Graph& graph) : Search(graph)
    { 
        if (graph.Directed())
        {
            throw std::invalid_argument("this class does not support directed graphs");
        }
    }
    virtual void SearchComponent(const std::shared_ptr<Edge>&) = 0;
};