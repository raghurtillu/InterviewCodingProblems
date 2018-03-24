#pragma once
#include "SearchUndirected.h"

class DFS : public SearchUndirected
{
protected:
    virtual void SearchComponent(const std::shared_ptr<Edge>& e)
    {
        if (!e) { return; }

        //size_t v = e->Source()->getId();
        size_t w = e->Destination()->getId();
        lookup.insert({w, SearchInfo(count++, cCount, e->Source())});

        auto adjIterator = graph.getIterator(e->Destination());
        for (auto ee = adjIterator->beg(); !(adjIterator->end()); ee = adjIterator->nxt())
        {
            size_t t = ee->Destination()->getId();
            if (lookup.find(t) == lookup.cend())
            {
                SearchComponent(ee);
            }
        }
    }
public:
    DFS(const Graph& graph) : SearchUndirected(graph)
    { 
        SearchGraph();
    }
};
