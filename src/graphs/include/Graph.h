#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include <unordered_map>

// Forward declaration
class Edge;
class Graph;
class Vertex;

class AdjIterator
{
public:
    AdjIterator(const Graph&, const std::shared_ptr<Vertex>&)
    {

    }
    virtual ~AdjIterator()
    {

    }
    virtual const std::shared_ptr<Edge>& beg() = 0;
    virtual const std::shared_ptr<Edge>& nxt() = 0;
    virtual bool end() const = 0;
};

class Graph
{
protected:
    bool directed = false;
    size_t vCount = 0;
    size_t eCount = 0;
    bool parallelEdges = false;

public:
    static const size_t SparseGraphThreshold;
    static Graph& getGraph(bool isDirected);
    static Graph& getGraph(bool isDirected, bool allowParallelEdges);

    Graph(bool isDirected) : Graph(isDirected, false)
    { }
    Graph(bool isDirected, bool allowParallelEdges) : directed(isDirected), parallelEdges(allowParallelEdges)
    { } 
    virtual ~Graph()
    { }
    size_t NumVertices() const
    {
        return vCount;
    }
    size_t NumEdges() const
    {
        return eCount;
    }
    bool Directed() const
    {
        return directed;
    }

    virtual void Insert(const std::shared_ptr<Vertex>&) = 0;
    virtual void Remove(const std::shared_ptr<Vertex>&) = 0;
    virtual std::vector<const std::shared_ptr<Vertex>> getVertices() const = 0;

    virtual void Insert(const std::shared_ptr<Edge>&) = 0;
    virtual void Remove(const std::shared_ptr<Edge>&) = 0;
    virtual std::vector<const std::shared_ptr<Edge>> getEdges() const = 0;

    virtual const std::shared_ptr<Edge>&
    IsEdge(const std::shared_ptr<Vertex>&, const std::shared_ptr<Vertex>&) const = 0;

    virtual std::shared_ptr<AdjIterator> getIterator(const std::shared_ptr<Vertex>&) const = 0;
};