#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <string>
#include <unordered_map>
#include <set>
#include <vector>

namespace maslov
{
  struct PairHash
  {
    size_t operator()(const std::pair< std::string, std::string > & pair) const
    {
      size_t h1 = std::hash< std::string >{}(pair.first);
      size_t h2 = std::hash< std::string >{}(pair.second);
      return h1 ^ h2;
    }
  };

  struct Graph
  {
    void addEdge(const std::string & v1, const std::string & v2, int weight);
   private:
    std::set< std::string > vertexes;
    std::unordered_map<std::pair< std::string, std::string >, std::vector< int >, PairHash > edges;
  };

  void Graph::addEdge(const std::string & v1, const std::string & v2, int weight)
  {
    edges[{v1, v2}].push_back(weight);
    vertexes.insert(v1);
    vertexes.insert(v2);
  }
}

#endif
