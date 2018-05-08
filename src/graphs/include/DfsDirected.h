#pragma once
#include "SearchDirected.h"

// given a vertex id, gets the index of the matching vertex id from a list of vertices
static size_t getVertexIndex(const std::vector<const std::shared_ptr<Vertex>>& vertices, size_t id)
{
    for (size_t i = 0; i < vertices.size(); ++i)
    {
        if (id == vertices[i]->getId()) { return i; }
    }
    return SIZE_MAX;
}

// implements Kosaraju's algorithm to detect strongly connected components in a directed graph
class DfsDirected : public SearchDirected
{
private:
    Graph& reverseGraph;
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
    std::vector<std::shared_ptr<Vertex>> postOrder;
    void SearchComponent(const Graph& graph, const std::shared_ptr<Edge>& e)
    {
        if (!e) { return; }

        size_t w = e->Destination()->getId();
        lookup.insert({w, SearchInfo(count++, cCount, e->Source())});

        auto adjIterator = graph.getIterator(e->Destination());
        for (auto ee = adjIterator->beg(); !(adjIterator->end()); ee = adjIterator->nxt())
        {
            if (!ee) { continue; }
            size_t t = ee->Destination()->getId();
            if (lookup.find(t) == lookup.cend())
            {
                SearchComponent(graph, ee);
            }
        }
        postOrder.push_back(e->Destination());
    }
public:
    DfsDirected(const Graph& graph) : SearchDirected(graph), reverseGraph(Graph::getGraph(graph.Directed()))
    { 
        ReverseGraph();

        SearchGraph(reverseGraph);

        std::vector<std::shared_ptr<Vertex>> postOrderCopy(postOrder.begin(), postOrder.end());
        count = cCount = 0;
        lookup.clear();
        postOrder.clear();

        std::vector<const std::shared_ptr<Vertex>> vertices = graph.getVertices();
        for (size_t i = postOrderCopy.size() - 1; i != SIZE_MAX; --i)
        {
            if (lookup.find(postOrderCopy[i]->getId()) == lookup.cend())
            {
                size_t index = getVertexIndex(vertices, postOrderCopy[i]->getId());
                if (index == SIZE_MAX) { continue; } // should not happen

                auto dummyVertex = vertices[index];
                std::shared_ptr<Edge> dummyEdge = std::make_shared<Edge>(dummyVertex, dummyVertex);
                SearchComponent(graph, dummyEdge);
                ++cCount;
            }
            else
            {
                // TODO: Detected of cycle here is buggy; revisit this code
                if (!SearchInfo::cycle)
                {
                    SearchInfo::cycle = true;
                }
            }
        }
        // Override the number of connected components if need be here;
        SearchInfo::connectedComponentCount = cCount;
    }
};