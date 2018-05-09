#include <iostream>
#include <memory>
#include <vector>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include "../include/GraphHelpers.h"
#include "../include/Dfs.h"
#include "../include/Bfs.h"
using namespace std;

int main()
{
    Graph& graph = Graph::getGraph(false);

    vector<shared_ptr<Vertex>> vertices;
    for (auto i = 0; i < 10; ++i) { vertices.emplace_back(make_shared<Vertex>("")); }
    
    vector<shared_ptr<Edge>> edges = 
    {
        make_shared<Edge>(vertices[0], vertices[2]),
        make_shared<Edge>(vertices[0], vertices[5]),
        make_shared<Edge>(vertices[0], vertices[7]),
        make_shared<Edge>(vertices[1], vertices[7]),
        make_shared<Edge>(vertices[2], vertices[6]),
        make_shared<Edge>(vertices[3], vertices[4]),
        make_shared<Edge>(vertices[3], vertices[5]),
        make_shared<Edge>(vertices[4], vertices[6]),
        make_shared<Edge>(vertices[4], vertices[7]),
    };
    for (const auto& edge : edges) { graph.Insert(edge); }

    // Print search tree
    for (size_t i = 0; i < 2; ++i)
    {
        shared_ptr<Search> search;
        if (i == 0)
        {
            search = make_shared<DFS>(graph);
            cout << "DFS Search tree: " << endl;
        }
        else if (i == 1)
        {
            search = make_shared<BFS>(graph);
            cout << "BFS Search tree: " << endl;    
        }

        auto searchVertices = graph.getVertices();
        for (const auto& it : searchVertices)
        {
            vector<shared_ptr<Vertex>> ancestors = WalkTree(search, it);
            for (size_t i = 0; i < ancestors.size(); ++i)
            {
                cout << ancestors[i]->getId();
                if (i != ancestors.size() - 1)
                {
                    cout << " -> ";
                }
            }
            cout << endl;
        }
        cout << "Number of connected components: " << search->NumberOfConnectedComponents() << endl;
    }    
    return 0;
}

