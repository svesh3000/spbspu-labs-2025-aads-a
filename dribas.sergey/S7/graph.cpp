#include "graph.hpp"
#include <algorithm>

dribas::Graph::Graph(const Graph& source, const RobinHoodHashTable< std::string, bool >& vertices)
{
  for (const auto& entry: source.faces_) {
    const auto& edge = entry.first;
    if (vertices.find(edge.first) != vertices.end() && vertices.find(edge.second) != vertices.end()) {
      for (int weight: entry.second) {
        faces_[edge].push_back(weight);
      }
    }
  }
}

dribas::Graph::Graph(const Graph& first, const Graph& second)
{
  auto copyEdges = [this](const Graph& src)
  {
    for (const auto& entry : src.faces_)
    {
      const auto& edge = entry.first;
      for (int weight: entry.second) {
        faces_[edge].push_back(weight);
      }
    }
  };
  copyEdges(first);
  copyEdges(second);
}

bool dribas::Graph::addEdge(const std::string& from, const std::string& to, int weight)
{
  auto edge = std::make_pair(from, to);
  faces_[edge].push_back(weight);
  return true;
}

bool dribas::Graph::removeEdge(const std::string& from, const std::string& to, int weight)
{
  auto edge = std::make_pair(from, to);
  auto it = faces_.find(edge);
  if (it == faces_.end()) {
    return false;
  }
  auto& weights = it->second;
  auto weight_it = std::find(weights.begin(), weights.end(), weight);

  if (weight_it == weights.end()) {
    return false;
  }
  weights.erase(weight_it);
  if (weights.empty()) {
    faces_.erase(edge);
  }
  return true;
}

bool dribas::Graph::hasVertex(const std::string& vertex) const
{
  for (const auto& entry: faces_) {
    if (entry.first.first == vertex || entry.first.second == vertex) {
      return true;
    }
  }
  return false;
}

namespace
{
  bool compareEdges(const std::pair< std::string, std::vector< int > >& a, const std::pair< std::string, std::vector< int>  >& b)
  {
    return a.first < b.first;
  }
}

std::vector< std::pair< std::string, std::vector< int > > > dribas::Graph::getOutboundEdges(const std::string& vertex) const
{
  dribas::RobinHoodHashTable< std::string, std::vector< int > > edges_table;
  for (const auto& entry: faces_) {
    if (entry.first.first == vertex) {
      for (int weight: entry.second) {
        edges_table[entry.first.second].push_back(weight);
      }
    }
  }

  std::vector< std::pair< std::string, std::vector< int > > > result;
  for (const auto& pair: edges_table) {
    std::vector< int > sorted_weights = pair.second;
    std::sort(sorted_weights.begin(), sorted_weights.end());
    result.emplace_back(pair.first, sorted_weights);
  }

  std::sort(result.begin(), result.end(), compareEdges);
  return result;
}

std::vector< std::pair< std::string, std::vector< int > > > dribas::Graph::getInboundEdges(const std::string& vertex) const
{
  dribas::RobinHoodHashTable< std::string, std::vector< int > > edges_table;
  for (const auto& entry: faces_) {
    if (entry.first.second == vertex) {
      for (int weight: entry.second) {
        edges_table[entry.first.first].push_back(weight);
      }
    }
  }

  std::vector< std::pair< std::string, std::vector< int > > > result;
  for (const auto& pair: edges_table) {
    std::vector< int > sorted_weights = pair.second;
    std::sort(sorted_weights.begin(), sorted_weights.end());
    result.emplace_back(pair.first, sorted_weights);
  }
  std::sort(result.begin(), result.end(), compareEdges);
  return result;
}

std::vector< std::string > dribas::Graph::getVertexes() const
{
  std::set< std::string > vertices_set;
  for (const auto& pair_entry: faces_) {
    vertices_set.insert(pair_entry.first.first);
    vertices_set.insert(pair_entry.first.second);
  }
  return std::vector< std::string >(vertices_set.begin(), vertices_set.end());
}

std::istream& dribas::operator>>(std::istream& in, Graph& graph)
{
  size_t edge_count;
  in >> edge_count;
  for (size_t i = 0; i < edge_count; ++i) {
    std::string from, to;
    int weight;
    in >> from >> to >> weight;
    graph.addEdge(from, to, weight);
  }
  return in;
}
std::ostream& dribas::operator<<(std::ostream& out, const Graph& graph)
{
  for (const auto& edge_entry: graph.faces_) {
    const auto& edge = edge_entry.first;
    for (int weight : edge_entry.second) {
      out << edge.first << " " << edge.second << " " << weight << "\n";
    }
  }
  return out;
}