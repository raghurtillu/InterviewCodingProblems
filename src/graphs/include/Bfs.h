#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include "Graph.h"
#include "Edge.h"
#include "SearchUndirected.h"

class BFS : public SearchUndirected
{
    virtual void SearchComponent(const std::shared_ptr<Edge>& e)
    {
        if (!e) { return; }

        std::queue<const std::shared_ptr<Edge>> bfsQ;
        bfsQ.push(e);
        while (!bfsQ.empty())
        {
            size_t w = bfsQ.front()->Destination()->getId();
            lookup.insert({w, SearchInfo(count++, cCount, bfsQ.front()->Source())});
            auto adjIterator = graph.getIterator(bfsQ.front()->Destination());
            bfsQ.pop();
            for (auto ee = adjIterator->beg(); !(adjIterator->end()); ee = adjIterator->nxt())
            {
                if (!ee) { continue; }
                size_t t = ee->Destination()->getId();
                if (lookup.find(t) == lookup.cend())
                {
                    bfsQ.push(ee);
                }
            }
        }
    }
public:
    BFS(const Graph& graph) : SearchUndirected(graph)
    { 
        SearchGraph();
    }
};