#pragma once
#include "SearchDirected.h"
#include "DfsDirected.h"

class DAGDfs : public DfsDirected
{
    std::vector<std::shared_ptr<Vertex>> tsOrder;
public:
    DAGDfs(const Graph& graph) : DfsDirected(graph)
    {
        // the order in DFS topological sort is actually in reverse order
        for (size_t i = postOrder.size() - 1; i != SIZE_MAX; --i)
        {
            tsOrder.push_back(postOrder[i]);
        }
    }
    std::vector<std::shared_ptr<Vertex>> GetTopologicalOrder() const
    {
        return tsOrder;
    }
};