#ifndef GRAPH_HPP
#define GRAPH_HPP
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <tree/tree-2-3.hpp>
#include <list/list.hpp>

namespace alymova
{
  using BoundMap = TwoThreeTree< std::string, List< size_t >, std::less< std::string > >;

  struct MyHash
  {
    std::size_t operator()(const std::pair< std::string, std::string >& s) const noexcept
    {
      std::size_t h1 = std::hash< std::string >{}(s.first);
      std::size_t h2 = std::hash< std::string >{}(s.second);
      return h1 ^ (h2 << 1);
    }
  };

  struct Graph
  {
    std::unordered_multimap< std::pair< std::string, std::string >, size_t, MyHash > edges;
    List< std::string > vertexes;

    void addEdge(std::string vertex1, std::string vertex2, size_t weight);
    void cutEdge(std::string vertex1, std::string vertex2, size_t weight);
    void addVertex(std::string vertex);
    bool hasVertex(std::string vertex) const;
    BoundMap getOutbound(std::string vertex) const;
    BoundMap getInbound(std::string vertex) const;
    void merge(const Graph& other);
  };

  std::istream& operator>>(std::istream& in, Graph& graph);
  std::ostream& operator<<(std::ostream& in, const Graph& graph);
}

#endif
