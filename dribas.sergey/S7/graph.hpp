#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <string>
#include <vector>
#include <utility>
#include <iostream>
#include <set>

#include "robinHashTable.hpp"

namespace dribas
{
  struct Graph{
  public:
    Graph() = default;
    Graph(const Graph&) = default;
    Graph(Graph&&) = default;
    Graph& operator=(const Graph&) = default;
    Graph& operator=(Graph&&) = default;
    ~Graph() = default;

    Graph(const Graph&, const RobinHoodHashTable< std::string, bool >&);
    Graph(const Graph&, const Graph&);

    friend std::istream& operator>>(std::istream&, Graph&);
    friend std::ostream& operator<<(std::ostream&, const Graph&);
    std::vector< std::string > getVertexes() const;
    std::vector< std::pair< std::string, std::vector< int > > > getOutboundEdges(const std::string&) const;
    std::vector< std::pair< std::string, std::vector< int > > > getInboundEdges(const std::string&) const;
    bool addEdge(const std::string&, const std::string&, int);
    bool removeEdge(const std::string&, const std::string&, int);
    bool hasVertex(const std::string&) const;
  private:
    RobinHoodHashTable< std::pair< std::string, std::string >, std::vector< int > > faces_;
  };
  std::istream& operator>>(std::istream& in, Graph& graph);
  std::ostream& operator<<(std::ostream& out, const Graph& graph);
}
#endif