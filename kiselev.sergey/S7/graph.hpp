#ifndef GRAPH_HPP
#define GRAPH_HPP
#include <cstddef>
#include <unordered_map>
#include <list>
#include <map>
#include <string>
#include <functional>
#include <utility>
namespace kiselev
{
  struct PairHash
  {
    size_t operator()(const std::pair< std::string, std::string >& pair) const
    {
      size_t h1 = std::hash< std::string >()(pair.first);
      size_t h2 = std::hash< std::string >()(pair.second);
      return h1 * 7 + h2;
    }
  };
  class Graph
  {
  public:
    using Vertexes = std::pair< std::string, std::string >;
    using Edge = std::unordered_map< Vertexes, std::list< unsigned int >, PairHash >;

    void addEdge(const std::string& v1, const std::string& v2, unsigned int weight)
    {
      edges[{ v1, v2 }].push_back(weight);
    }

    bool removeEdge(const std::string& v1, const std::string& v2, unsigned int weight)
    {
      auto it = edges.find({ v1, v2 });
      if (it == edges.end())
      {
        return false;
      }
      size_t size1 = it->second.size();
      it->second.remove(weight);
      size_t size2 = it->second.size();
      if (it->second.empty())
      {
        edges.erase(it);
      }
      return size2 < size1;
    }

    std::map< std::string, std::string > getVertexes() const
    {
      std::map< std::string, std::string > vertexes;
      for (auto it = edges.begin(); it != edges.end(); ++it)
      {
        vertexes[it->first.first];
        vertexes[it->first.second];
      }
      return vertexes;
    }

    std::map< std::string, std::map< unsigned int, unsigned int > > getOutBound(const std::string& v) const
    {
      std::map< std::string, std::map< unsigned int, unsigned int > > result;
      for (auto edgeIt = edges.begin(); edgeIt != edges.end(); ++edgeIt)
      {
        if (edgeIt->first.first == v)
        {
          for (auto weightIt = edgeIt->second.begin(); weightIt != edgeIt->second.end(); ++weightIt)
          {
            result[edgeIt->first.second][*weightIt]++;
          }
        }
      }
      return result;
    }

    std::map< std::string, std::map< unsigned int, unsigned int > > getInBound(const std::string& v) const
    {
      std::map< std::string, std::map< unsigned int, unsigned int > > result;
      for (auto edgeIt = edges.begin(); edgeIt != edges.end(); ++edgeIt)
      {
        if (edgeIt->first.second == v)
        {
          for (auto weightIt = edgeIt->second.begin(); weightIt != edgeIt->second.end(); ++weightIt)
          {
            result[edgeIt->first.first][*weightIt]++;
          }
        }
      }
      return result;
    }

    const Edge& getEdges() const
    {
      return edges;
    }
  private:
    Edge edges;
  };
}
#endif
