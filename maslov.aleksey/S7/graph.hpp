#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <string>
#include <unordered_map>
#include <set>
#include <vector>
#include <algorithm>
#include <stdexcept>

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
    void addVertex(const std::string & v);
    void deleteEdge(const std::string & v1, const std::string & v2, int weight);
    std::vector< std::string > getVertexes() const;
    bool hasVertex(const std::string & vertex) const;
    bool hasEdge(const std::string & v1, const std::string & v2, int weight) const;
    std::vector< std::pair< std::string, int > > getOutbound(const std::string & vertex) const;
    std::vector< std::pair< std::string, int > > getInbound(const std::string & vertex) const;
    void merge(const Graph & graph);
    void extract(const Graph & graph, const std::set< std::string > & extractVertexes);
   private:
    std::set< std::string > vertexes;
    std::unordered_map<std::pair< std::string, std::string >, std::vector< int >, PairHash > edges;
  };

  void Graph::extract(const Graph & graph, const std::set< std::string > & extractVertexes)
  {
    for (auto it = extractVertexes.begin(); it != extractVertexes.end(); it++)
    {
      addVertex(*it);
    }
    for (auto it = graph.edges.begin(); it != graph.edges.end(); it++)
    {
      const auto vertexes = it->first;
      if (hasVertex(vertexes.first) && hasVertex(vertexes.second))
      {
        for (auto itWeight = it->second.begin(); itWeight != it->second.end(); ++itWeight)
        {
          addEdge(vertexes.first, vertexes.second, *itWeight);
        }
      }
    }
  }

  void Graph::merge(const Graph & graph)
  {
    for (auto it = graph.edges.begin(); it != graph.edges.end(); it++)
    {
      for (auto itWeight = it->second.begin(); itWeight != it->second.end(); ++itWeight)
      {
        addEdge(it->first.first, it->first.second, *itWeight);
      }
    }
    for (auto it = graph.vertexes.begin(); it != graph.vertexes.end(); it++)
    {
      addVertex(*it);
    }
  }

  void Graph::addVertex(const std::string & v)
  {
    vertexes.insert(v);
  }

  bool Graph::hasVertex(const std::string & vertex) const
  {
    return vertexes.find(vertex) != vertexes.end();
  }

  bool Graph::hasEdge(const std::string & v1, const std::string & v2, int weight) const
  {
    auto it = edges.find({v1, v2});
    if (it == edges.end())
    {
      return false;
    }
    for (int existWeight: it->second)
    {
      if (existWeight == weight)
      {
        return true;
      }
    }
    return false;
  }

  void Graph::addEdge(const std::string & v1, const std::string & v2, int weight)
  {
    if (hasEdge(v1, v2, weight))
    {
      return;
    }
    edges[{v1, v2}].push_back(weight);
    vertexes.insert(v1);
    vertexes.insert(v2);
  }

  void Graph::deleteEdge(const std::string & v1, const std::string & v2, int weight)
  {
    auto it = edges.find({v1, v2});
    if (it == edges.end())
    {
      throw std::logic_error("ERROR: there is no such edge");
    }
    auto weights = it->second;
    for (auto itWeight = weights.begin(); itWeight != weights.end(); itWeight++)
    {
      if (*itWeight == weight)
      {
        weights.erase(itWeight);
        return;
      }
    }
    throw std::logic_error("ERROR: there is no such edge");;
  }

  std::vector< std::string > Graph::getVertexes() const
  {
    return {vertexes.begin(), vertexes.end()};
  }

  std::vector< std::pair< std::string, int > > Graph::getOutbound(const std::string & vertex) const
  {
    std::vector< std::pair< std::string, int > > result;
    for (auto it = edges.begin(); it != edges.end(); it++)
    {
      if (it->first.first == vertex)
      {
        for (int weight: it->second)
        {
          result.push_back({it->first.second, weight});
        }
      }
    }
    std::sort(result.begin(), result.end());
    return result;
  }

  std::vector< std::pair< std::string, int > > Graph::getInbound(const std::string & vertex) const
  {
    std::vector< std::pair< std::string, int > > result;
    for (auto it = edges.begin(); it != edges.end(); it++)
    {
      if (it->first.second == vertex)
      {
        for (int weight: it->second)
        {
          result.push_back({it->first.first, weight});
        }
      }
    }
    std::sort(result.begin(), result.end());
    return result;
  }
}

#endif
