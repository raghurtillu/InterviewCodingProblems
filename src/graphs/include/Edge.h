#pragma once
#include <memory>
// Forward declaration
class Vertex;

class Edge
{
    std::shared_ptr<Vertex>& source;
    std::shared_ptr<Vertex>& destination;
    int wt = 0;

public:
    Edge() = default;
    Edge(const Edge&) = default;
    Edge(std::shared_ptr<Vertex>& src, std::shared_ptr<Vertex>& dest, int _wt = 0)
        : source(src), destination(dest), wt(_wt)
    {}
    std::shared_ptr<Vertex>& Source() const
    {
        return source;
    }
    std::shared_ptr<Vertex>& Destination() const
    {
        return destination;
    }
    bool From(std::shared_ptr<Vertex>& v) const
    {
        return v == source;
    }
    const std::shared_ptr<Vertex>& Other(std::shared_ptr<Vertex>& v) const
    {
        return From(v) ? destination : source;
    }
    int Weight() const
    {
        return wt;
    }
};
