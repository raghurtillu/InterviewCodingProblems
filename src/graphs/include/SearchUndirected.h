#pragma once
#include <vector>
#include <unordered_map>
#include "Graph.h"
#include "Edge.h"
#include "Vertex.h"

// provides the search interface for a given graph
class SearchUndirected
{
    void ThrowIfInvalidVertex(const std::shared_ptr<Vertex>& v)
    {
        if (!v)
        { 
            throw std::invalid_argument("Empty vertex specified.");
        }
        else if (lookup.find(v->getId()) == lookup.cend())
        {
            throw std::invalid_argument("Invalid vertex '" + std::to_string(v->getId()) + "'" + " specified.");
        }
    }

protected:
    struct SearchInfo
    {
        size_t order = 0;
        size_t connectedComponentId = 0;
        const std::shared_ptr<Vertex> parent;
        SearchInfo(size_t _order, size_t _connectedComponentId, const std::shared_ptr<Vertex> _parentId) :
            order(_order), connectedComponentId(_connectedComponentId), parent(_parentId)
        {}
        SearchInfo() = default;
        SearchInfo(const SearchInfo&) = default;
        SearchInfo& operator= (const SearchInfo&) = default;
    };

    const Graph& graph;    
    std::unordered_map<size_t, SearchInfo> lookup;
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
    }

    SearchUndirected(const Graph& g) : graph(g)
    { 
        if (g.Directed())
        {
            throw std::invalid_argument("this class does not support directed graphs");
        }
    }

    virtual void SearchComponent(const std::shared_ptr<Edge>&) = 0;
    
public:
    // provides the order of specified vertex
    virtual size_t operator[] (const std::shared_ptr<Vertex>& v)
    {
        ThrowIfInvalidVertex(v);
        return lookup[v->getId()].order;
    }

    // provides the connected component of specified vertex
    virtual size_t ConnectedComponent(const std::shared_ptr<Vertex>& v)
    {
        ThrowIfInvalidVertex(v);
        return lookup[v->getId()].connectedComponentId;
    }

    // provides the parent of specified vertex
    virtual const std::shared_ptr<Vertex> Parent(const std::shared_ptr<Vertex>& v)
    {
        ThrowIfInvalidVertex(v);
        return lookup[v->getId()].parent;
    }
};