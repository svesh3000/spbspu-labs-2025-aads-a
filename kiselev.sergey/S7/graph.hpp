#ifndef GRAPH_HPP
#define GRAPH_HPP
#include <string>
#include <unordered_map>
#include <list>
#include <map>
namespace kiselev
{
  class Graph
  {
  public:
    using Vertexes = std::pair< std::string, std::string >;
    using Edge = std::unordered_map< Vertexes, std::list< unsigned int > >;

    void addEdge(const std::string& v1, const std::string& v2, unsigned int weight)
    {
      edges[{ v1, v2 }].push_back(weight);
    }

    void removeEdge(const std::string& v1, const std::string& v2, unsigned int weight)
    {
      auto it = edges.find({ v1, v2 });
      if (it != edges.end())
      {
        it->second.remove(weight);
        if (it->second.empty())
        {
          edges.erase(it);
        }
      }
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
            result[edgeIt->first.second][*weightIt]++;
          }
        }
      }
      return result;
    }

    const Edge& getEdge() const
    {
      return edges;
    }
  private:
    Edge edges;
  };
}
#endif
