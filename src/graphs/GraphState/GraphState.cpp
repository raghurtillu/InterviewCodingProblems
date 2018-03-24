#include <iostream>
#include <memory>
#include <vector>
#include <list>
#include <unordered_map>
#include "../include/Graph.h"
#include "../include/Edge.h"
#include "../include/Vertex.h"
#include "../include/SparseGraph.h"

using namespace std;

Graph& Graph::getGraph(bool isDirected)
{
    Graph *pGraph = new SparseGraph(isDirected);
    return *pGraph;
}

int main()
{
    Graph& graph = Graph::getGraph(true);

    vector<shared_ptr<Vertex>> vertices;
    for (auto i = 0; i < 13; ++i) { vertices.emplace_back(make_shared<Vertex>("")); }
    
    vector<shared_ptr<Edge>> edges = 
    {
        make_shared<Edge>(vertices[0], vertices[1]),
        make_shared<Edge>(vertices[0], vertices[2]),
        make_shared<Edge>(vertices[0], vertices[3]),
        make_shared<Edge>(vertices[0], vertices[5]),
        make_shared<Edge>(vertices[0], vertices[6]),
        make_shared<Edge>(vertices[2], vertices[3]),
        make_shared<Edge>(vertices[3], vertices[4]),
        make_shared<Edge>(vertices[3], vertices[5]),
        make_shared<Edge>(vertices[4], vertices[9]),
        make_shared<Edge>(vertices[6], vertices[4]),
        make_shared<Edge>(vertices[6], vertices[9]),
        make_shared<Edge>(vertices[7], vertices[6]),
        make_shared<Edge>(vertices[8], vertices[7]),
        make_shared<Edge>(vertices[9], vertices[10]),
        make_shared<Edge>(vertices[9], vertices[11]),
        make_shared<Edge>(vertices[9], vertices[12]),
        make_shared<Edge>(vertices[11], vertices[12]),
    };

    for (const auto& edge : edges) { graph.Insert(edge); }

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
    return 0;
}