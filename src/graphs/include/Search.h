#pragma once
#include <vector>
#include <unordered_map>
#include "GraphHelpers.h"

// provides the search interface for a given graph
class Search
{
protected:
    void ThrowIfInvalidVertex(const std::shared_ptr<Vertex>& v)
    {
        if (!v)
        { throw std::invalid_argument("Empty vertex specified."); }
        else if (lookup.find(v->getId()) == lookup.cend())
        { throw std::invalid_argument("Invalid vertex '" + std::to_string(v->getId()) + "'" + " specified."); }
    }

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
        static bool cycle;
        static size_t connectedComponentCount;
    };
    
    const Graph& graph;
    std::unordered_map<size_t, SearchInfo> lookup;
    Search(const Graph& g) : graph(g)
    { }

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
    virtual size_t NumberOfConnectedComponents() const
    {
        return SearchInfo::connectedComponentCount;
    }
    // provides the parent of specified vertex
    virtual const std::shared_ptr<Vertex> Parent(const std::shared_ptr<Vertex>& v)
    {
        ThrowIfInvalidVertex(v);
        return lookup[v->getId()].parent;
    }
    virtual bool hasCycle() const
    {
        return SearchInfo::cycle;
    }
};

bool Search::SearchInfo::cycle = false;
size_t Search::SearchInfo::connectedComponentCount = 0;