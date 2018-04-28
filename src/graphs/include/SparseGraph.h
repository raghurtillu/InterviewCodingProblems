#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include <list>
#include <unordered_map>
#include "Graph.h"
#include "Vertex.h"

// Forward declaration
class SparseGraph;

class SparseAdjIterator : public AdjIterator
{
    const SparseGraph& sparseGraph;
    const std::shared_ptr<Vertex>& v;
    std::unordered_map<const std::shared_ptr<Vertex>, 
        std::list<std::shared_ptr<Edge>>, VertexHash>::const_iterator iter;
        
    std::list<std::shared_ptr<Edge>>::const_iterator listIter;

public:
    SparseAdjIterator(const Graph& G, const std::shared_ptr<Vertex>& startVertex);
    const std::shared_ptr<Edge>& beg();
    const std::shared_ptr<Edge>& nxt();
    bool end() const;
};

class SparseGraph : public Graph
{
    std::unordered_map<const std::shared_ptr<Vertex>, std::list<std::shared_ptr<Edge>>, VertexHash> adjList;
    static const std::shared_ptr<Edge> empty;

    bool hasNeighbour(std::shared_ptr<Vertex>& v, std::shared_ptr<Vertex>& w)
    {
        if (adjList.find(v) != adjList.cend())
        {
            for (const auto it : adjList[v])
            {
                if (it->Destination()->getId() == w->getId())
                {
                    return true;
                }
            }
        }
        return false;
    }

public:
    SparseGraph(bool isDirected) : Graph(isDirected)
    { }
    SparseGraph(bool isDirected, bool allowParallelEdges) : Graph(isDirected, allowParallelEdges)
    { }

    virtual void Insert(const std::shared_ptr<Vertex>& v)
    {
        if (!v) { return; }
        if (adjList.find(v) == adjList.cend())
        {
            std::list<std::shared_ptr<Edge>> emptyList;
            adjList[v] = emptyList;
            ++vCount;
        }
    }
    
    virtual void Remove(const std::shared_ptr<Vertex>& v)
    {
        if (!v) { return; }
        else if (adjList.find(v) == adjList.cend()) { return; }
        
        // delete edges for which v is source
        adjList[v].clear();
        adjList.erase(v);

        // delete edges for which v is destination
        for (auto iter = adjList.begin(); iter != adjList.end(); ++iter)
        {
            auto list = iter->second;
            list.remove_if([&](std::shared_ptr<Edge>& e) 
            {
                return e->Destination()->getId() == v->getId();
            });
        }
        --vCount;
    }

    virtual std::vector<const std::shared_ptr<Vertex>> getVertices() const
    {
        std::vector<const std::shared_ptr<Vertex>> vertices;
        for (auto iter = adjList.cbegin(); iter != adjList.cend(); ++iter)
        {
            vertices.push_back(iter->first);
        }
        return vertices;
    }

    virtual void Insert(const std::shared_ptr<Edge>& e)
    {
        if (!e) { return; }

        // Insert the vertices of the edges; if the vertices have already been added, its a no-op
        this->Insert(e->Source());
        this->Insert(e->Destination());        
                
        if (parallelEdges || !hasNeighbour(e->Source(), e->Destination()))
        {
            adjList[e->Source()].push_back(e);
            ++eCount;
        }
        if (!this->Directed())
        {
            if (parallelEdges || !hasNeighbour(e->Destination(), e->Source()))
            {
                auto alternateEdge = std::make_shared<Edge>(e->Destination(), e->Source());
                adjList[e->Destination()].push_back(alternateEdge);
                //adjList[e->Destination()].push_back(e);
                ++eCount;
            }
        }        
    }

    virtual void Remove(const std::shared_ptr<Edge>& e)
    {
        if (!e) { return; }
        else if (adjList.find(e->Source()) == adjList.cend()) { return; }

        size_t v = e->Source()->getId();
        size_t w = e->Destination()->getId();

        auto val = *(e->Destination());
        adjList[e->Source()].remove_if([&](std::shared_ptr<Edge>& ee)
        {
            return ee->Destination()->getId() == w;
        });

        --eCount;

        if (!this->Directed())
        {
            if (adjList.find(e->Destination()) == adjList.cend()) { return; }
            
            adjList[e->Destination()].remove_if([&](std::shared_ptr<Edge>& ee)
            {
                return ee->Source()->getId() == v;
            });
            --eCount;
        }
    }

    virtual std::vector<const std::shared_ptr<Edge>> getEdges() const
    {
        std::vector<const std::shared_ptr<Edge>> edges;
        for (auto iter = adjList.cbegin(); iter != adjList.cend(); ++iter)
        {
            auto& list = iter->second;
            for (auto listIter = list.begin(); listIter != list.cend(); ++listIter)
            {
                edges.push_back(*listIter);
            }
        }
        return edges;
    }

    virtual const std::shared_ptr<Edge>&
    IsEdge(const std::shared_ptr<Vertex> &v, const std::shared_ptr<Vertex>& w) const
    {
        if (!v || !w) { return empty; }
        else if (adjList.find(v) == adjList.cend()) { return empty; }
        else if (adjList.find(w) == adjList.cend()) { return empty; }

        auto iter = adjList.find(v);
        for (auto listIter = (iter->second).cbegin(); listIter != (iter->second).cend(); ++listIter)
        {
            if ((*listIter)->Destination()->getId() == w->getId())
            {
                return *listIter;
            }
        }
        return empty;
    }

    virtual std::shared_ptr<AdjIterator> getIterator(const std::shared_ptr<Vertex>& startVertex) const
    {
        if (!startVertex) { throw std::invalid_argument("Invalid/empty vertex specified."); }
        
        std::shared_ptr<AdjIterator> adjIterator = std::make_shared<SparseAdjIterator>(*this, startVertex);
        return adjIterator;
    }

    virtual ~SparseGraph()
    { }
    friend class SparseAdjIterator;

};
const std::shared_ptr<Edge> SparseGraph::empty = nullptr;

SparseAdjIterator::SparseAdjIterator(const Graph& G, const std::shared_ptr<Vertex>& startVertex) : 
    AdjIterator(G, startVertex),
    sparseGraph(static_cast<const SparseGraph&>(G)), // safe downcast here
    v(startVertex),
    iter(sparseGraph.adjList.find(v))
{

}
const std::shared_ptr<Edge>& SparseAdjIterator::beg()
{
    listIter = (iter->second).begin();
    return (listIter != (iter->second).end()) ? *listIter : SparseGraph::empty;
}
const std::shared_ptr<Edge>& SparseAdjIterator::nxt()
{
    listIter++;
    return (listIter != (iter->second).end()) ? *listIter : SparseGraph::empty;
}
bool SparseAdjIterator::end() const
{
    return listIter == (iter->second).end();
}
