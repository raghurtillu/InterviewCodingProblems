#pragma once
#include <iostream>
#include <memory>
class Vertex
{
    static size_t count;
    size_t id = 0;
    std::string name;
public:
    Vertex() : Vertex("")
    { }
    Vertex(const std::string& _name) : name(_name)
    {
        id = count++;
    }
    Vertex(const Vertex&) = default;
    Vertex& operator= (const Vertex&) = default;
    
    size_t getId() const
    {
        return id;
    }
    const std::string& getName() const
    {
        return name;
    }
    virtual bool operator== (const Vertex& v) const
    {
        return id == v.id && name == v.name;
    }
    virtual bool operator== (const std::shared_ptr<Vertex>& v) const
    {
        if (v)
        {
            return id == v->id && name == v->name;
        }
        return false;
    }
};
size_t Vertex::count = 0;

struct VertexHash
{
    size_t operator() (const std::shared_ptr<Vertex>& v) const
    {
        if (v)
        {
            return std::hash<size_t>()(v->getId());
        }
        else
        {
            return SIZE_MAX;
        }
    }
};