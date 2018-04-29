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
    std::vector<size_t> postOrder;
protected:
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
        postOrder.push_back(w);
    }
public:
    DfsDirected(const Graph& graph) : SearchDirected(graph)
    { 
        SearchGraph(reverseGraph);

        std::vector<size_t> postOrderCopy(postOrder.begin(), postOrder.end());
        count = cCount = 0;
        lookup.clear();

        std::vector<const std::shared_ptr<Vertex>> vertices = graph.getVertices();
        for (size_t i = postOrderCopy.size() - 1; i != SIZE_MAX; --i)
        {
            if (lookup.find(postOrderCopy[i]) == lookup.cend())
            {
                size_t index = getVertexIndex(vertices, postOrderCopy[i]);
                if (index == SIZE_MAX) { continue; } // should not happen

                auto dummyVertex = vertices[index];
                std::shared_ptr<Edge> dummyEdge = std::make_shared<Edge>(dummyVertex, dummyVertex);
                SearchComponent(graph, dummyEdge);
                ++cCount;
            }
            else
            {
                if (!SearchInfo::cycle)
                {
                    SearchInfo::cycle = true;
                }
            }
        }
        SearchInfo::connectedComponentCount = cCount;
    }
};

