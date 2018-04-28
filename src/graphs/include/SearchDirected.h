#pragma once
#include <vector>
#include <unordered_map>
#include "Graph.h"
#include "Edge.h"
#include "Search.h"
#include "Vertex.h"

class SearchDirected : public Search
{
private:
    std::vector<std::shared_ptr<Vertex>> reverseVertices;
    std::vector<std::shared_ptr<Edge>> reverseEdges;
    void ReverseGraph()
    {
        for (size_t i = 0; i < graph.NumVertices(); ++i) 
        { reverseVertices.emplace_back(std::make_shared<Vertex>("")); }

        std::vector<const std::shared_ptr<Vertex>> vertices = graph.getVertices();
        for (size_t i = 0; i < vertices.size(); ++i)
        {
            auto adjIterator = graph.getIterator(vertices[i]);
            for (auto e = adjIterator->beg(); !(adjIterator->end()); e = adjIterator->nxt())
            {
                if (!e) { continue; }
                auto& srcVertex = e->Source();
                auto& destVertex = e->Destination();
                reverseEdges.emplace_back(std::make_shared<Edge>(destVertex, srcVertex));
            }
        }

        for (auto& ee : reverseEdges)
        { reverseGraph.Insert(ee); }
    }

protected:
    Graph& reverseGraph;
    size_t count = 0, cCount = 0;
    void SearchGraph(const Graph& graph)
    {
        std::vector<const std::shared_ptr<Vertex>> vertices = graph.getVertices();
        for (size_t i = 0; i < vertices.size(); ++i)
        {
            if (lookup.find(i) == lookup.cend())
            {
                // add a dummy self edge
                auto dummyVertex = vertices[i];
                std::shared_ptr<Edge> dummyEdge = std::make_shared<Edge>(dummyVertex, dummyVertex);
                SearchComponent(graph, dummyEdge);
                ++cCount;
            }
        }
    }

    SearchDirected(const Graph& graph) : Search(graph), reverseGraph(Graph::getGraph(graph.Directed()))
    {
        if (!graph.Directed())
        {
            throw std::invalid_argument("this class does not support undirected graphs");
        }
        ReverseGraph();
    }
    virtual void SearchComponent(const Graph& graph, const std::shared_ptr<Edge>&) = 0;
};
