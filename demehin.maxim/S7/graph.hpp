#ifndef GRAPH_HPP
#define GRAPH_HPP
#include <string>
#include <unordered_map>
#include <dynamic_array.hpp>
#include <tree/tree.hpp>

namespace demehin
{
  struct PairHash
  {
    size_t operator()(const std::pair< std::string, std::string >& p) const
    {
      return std::hash< std::string >()(p.first) ^ std::hash< std::string >()(p.second);
    }
  };

  class Graph
  {
  public:
    void addEdge(const std::string&, const std::string&, unsigned int);
    Tree< std::string, std::string > getVrts() const;

  private:
    std::unordered_map< std::pair< std::string, std::string >, DynamicArray< unsigned int >, PairHash > edges;
  };
}

#endif
