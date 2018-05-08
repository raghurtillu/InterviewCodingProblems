#include <iostream>
#include "../include/GraphHelpers.h"
#include "../include/DAGDfs.h"
using namespace std;

void AlienDictionary(const vector<string>& words)
{
    if (words.empty()) { return; }
    else if (words.size() == 1)
    { 
        for (auto c : words[0])
        { cout << c << " "; }
        return;
    }
    
    // assumption: words consist of lowercase english alphabet
    vector<shared_ptr<Vertex>> vertices (26, 0);
    vector<shared_ptr<Edge>> edges;

    // mapping between vertex id and index into word array
    unordered_map<size_t, size_t> lookup;
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
                if (vertices[first[j] - 'a'] == nullptr)
                {
                    vertices[first[j] - 'a'] = make_shared<Vertex>(string(1, first[j]));
                    lookup[vertices[first[j] - 'a']->getId()] = i;
                }
                if (vertices[second[k] - 'a'] == nullptr)
                {
                    vertices[second[k] - 'a'] = make_shared<Vertex>(string(1, second[k]));
                    lookup[vertices[second[k] - 'a']->getId()] = i + 1;
                }
                edges.push_back(make_shared<Edge>(vertices[first[j] - 'a'], vertices[second[k] - 'a']));
                graph.Insert(edges.back());
                break;
            }
        }
    }

    // cout << "Graph state" << endl;
    // graph.Directed() ? cout << "Directed: true" << endl : cout << "Directed: false" << endl;
    // cout << "Vertices: " << ": ";
    // {
    //     auto graphVertices = graph.getVertices();
    //     for (const auto& v : graphVertices)
    //     {
    //         cout << v->getId() << " ";
    //     }
    //     cout << "(" << graph.NumVertices() << ")" << endl;
    // }
    // cout << "Edges: " << graph.NumEdges() << endl;
    // {
    //     auto graphEdges = graph.getEdges();
    //     for (const auto& e : graphEdges)
    //     {
    //         cout << e->Source()->getName() << " -> " << e->Destination()->getName() << endl;
    //     }
    // }

    shared_ptr<DAGDfs> search = make_shared<DAGDfs>(graph);
    auto tsVertices = search->GetTopologicalOrder();
    for (const auto& it : tsVertices)
    {
        cout << it->getName() << " ";
    }
    cout << endl;
}

int main()
{
    vector<vector<string>> inputs = 
    {
        {"abcd"},
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
        cout << "The ordering of alphabet are: ";
        AlienDictionary(words);
        cout << endl;
    }
    return 0;
}

