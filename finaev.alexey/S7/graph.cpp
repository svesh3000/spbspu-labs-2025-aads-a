#include "graph.hpp"
#include <algorithm>

void finaev::Graph::addVertex(const std::string & str) 
{
  vertexes_.insert(std::make_pair(str, true));
}

void finaev::Graph::addEdge(std::string first, std::string second, size_t weigth)
{
  addVertex(first);
  addVertex(second);
  edges_[std::make_pair(first, second)][weigth]++;
}

void finaev::Graph::addEdges(const Graph& other)
{
  for (auto iter = other.edges_.cbegin(); iter != other.edges_.cend(); ++iter)
  {
    for (auto iter2 = iter->second.cBegin(); iter2 != iter->second.cEnd(); ++iter2)
    {
      for (size_t i = 0; i < iter2->second; ++i)
      {
        addEdge(iter->first.first, iter->first.second, iter2->first);
      }
    }
  }
}

bool finaev::Graph::removeEdge(const std::string& first, const std::string& second, size_t weigth)
{
  auto it = edges_.find({ first, second });
  if (it == edges_.end())
  {
    return false;
  }
  auto pos = it->second.find(weigth);
  if (pos == it->second.end()) 
  {
    return false;
  }
  it->second.erase(pos);
  if (it->second.empty())
  {
    edges_.erase(it);
  }
  return true;
}

finaev::AVLtree< std::string, bool > finaev::Graph::getVertexes() const
{
  return vertexes_;
}

std::unordered_map< std::pair< std::string, std::string >, finaev::AVLtree< size_t, size_t >, finaev::HashForPair  > finaev::Graph::getEdges() const
{
  return edges_;
}

bool finaev::Graph::hasVert(const std::string& str) const
{
  return vertexes_.find(str) != vertexes_.cEnd();
}

finaev::AVLtree< std::string, finaev::AVLtree< size_t, size_t > > finaev::Graph::getOutBound(const std::string& str) const
{
  if (!hasVert(str))
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
  AVLtree< std::string, AVLtree< size_t, size_t > > temp;
  for (auto i = edges_.cbegin(); i != edges_.cend(); ++i)
  {
    const AVLtree< size_t, size_t >& weights = i->second;
    if (i->first.first == str)
    {
      temp[i->first.second] = weights;
    }
  }
  return temp;
}

finaev::AVLtree< std::string, finaev::AVLtree< size_t, size_t > > finaev::Graph::getInBound(const std::string& str) const
{
  if (!hasVert(str))
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
  AVLtree< std::string, AVLtree< size_t, size_t > > temp;
  for (auto i = edges_.cbegin(); i != edges_.cend(); ++i)
  {
    const AVLtree< size_t, size_t >& weights = i->second;
    if (i->first.second == str)
    {
      temp[i->first.first] = weights;
    }
  }
  return temp;
}
