#include <iostream>
#include "graph.hpp"

void demehin::Graph::addEdge(const std::string& from, const std::string& to, unsigned int weight)
{
  auto key = std::make_pair(from, to);
  edges[key].push(weight);
}

void demehin::Graph::print() const
{
  for (const auto& edge : edges)
  {
    const auto& vrt = edge.first;
    const auto& weights = edge.second;

    std::cout << vrt.first << " " << vrt.second << ": ";
    for (size_t i = 0; i < weights.size(); i++)
    {
      std::cout << weights[i] << " ";
    }
  }
}
