#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <string>
#include "hash_table.hpp"

namespace tkach
{
  struct HashPair
  {
    size_t operator()(const std::pair< std::string, std::string >& p) const
    {
      size_t h1 = std::hash< std::string >()(p.first);
      size_t h2 = std::hash< std::string >()(p.second);
      return h1 ^ (h2 + 0x9e3779b9 + (h1 << 6) + (h1 >> 2));
    }
  };

  class Graph
  {
  public:
    void addEdge(const std::string& vert1, const std::string& vert2, size_t weight);
  private:
    HashTable< std::pair< std::string, std::string >, HashDynAry< size_t >, HashPair > edges_; 
  };
}
#endif