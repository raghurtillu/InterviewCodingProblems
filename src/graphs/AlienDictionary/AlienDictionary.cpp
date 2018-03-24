#include <iostream>
#include <memory>
#include <vector>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include "../include/Graph.h"
#include "../include/Edge.h"
#include "../include/Vertex.h"
#include "../include/SparseGraph.h"
#include "../include/DAGTopologicalSortDFS.h"
#include "../include/DAGTopologicalSortBFS.h"

using namespace std;

Graph& Graph::getGraph(bool isDirected)
{
    Graph *pGraph = new SparseGraph(isDirected);
    return *pGraph;
}

void AlienDictionary(const vector<string>& words)
{
    if (words.size() <= 1)
    {
        return;
    }
    
    unordered_map<char, shared_ptr<Vertex>> lookup;
    Graph& graph = Graph::getGraph(true);
    for (size_t i = 0; i < words.size() - 1; ++i)
    {
        const string& first = words[i];
        const string& second = words[i + 1];
        for (size_t j = 0, k = 0; j < first.size() && k < second.size(); ++j, ++k)
        {
            // find first instance where the words differ; create edge between these 2 characters and break
            if (first[j] != second[k])
            {
                shared_ptr<Vertex> v1, v2;
                if (lookup.find(first[j]) == lookup.cend())
                {
                    v1 = make_shared<Vertex>(string(1, first[j]));
                    lookup[first[j]] = v1;
                }
                if (lookup.find(second[k]) == lookup.cend())
                {
                    v2 = make_shared<Vertex>(string(1, second[k]));
                    lookup[second[k]] = v2;
                }
                v1 = lookup[first[j]];
                v2 = lookup[second[k]];
                
                graph.Insert(make_shared<Edge>(v1, v2));
                break;
            }
        }
    }

    cout << "Graph state" << endl;
    graph.Directed() ? cout << "Directed: true" << endl : cout << "Directed: false" << endl;
    cout << "Vertices: " << ": ";
    {
        auto graphVertices = graph.getVertices();
        for (const auto& v : graphVertices)
        {
            cout << v->getId() << " ";
        }
        cout << "(" << graph.NumVertices() << ")" << endl;
    }
    cout << "Edges: " << graph.NumEdges() << endl;
    {
        auto graphEdges = graph.getEdges();
        for (const auto& e : graphEdges)
        {
            cout << e->Source()->getId() << " -> " << e->Destination()->getId() << endl;
        }
    }
}

int main()
{
    vector<vector<string>> inputs = 
    {
        {"baa", "abcd", "abca", "cab", "cad"},
    };

    for (const auto& words : inputs)
    {
        cout << "For the inputs: ";
        for (const auto& word : words)
        {
            cout << word << " ";
        }
        cout << endl;
        AlienDictionary(words);
    }
    // DAGTopologicalSortBFS dagDfsTS(graph);
    // cout << "Topological sort: ";
    // for (size_t i = 0; i < graph.NumVertices(); ++i)
    // {
    //     cout << dagDfsTS[i] << " ";
    // }
    // cout << endl;
    return 0;
}

