#ifndef GRAPH_HPP
#define GRAPH_HPP
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>

namespace alymova
{
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
  };

  std::istream& operator>>(std::istream& in, Graph& graph);
  std::ostream& operator<<(std::ostream& in, const Graph& graph);
}

#endif
