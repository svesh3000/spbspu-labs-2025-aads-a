#include "graph.hpp"

void demehin::Graph::addEdge(const std::string& from, const std::string& to, unsigned int weight)
{
  auto key = std::make_pair(from, to);
  edges[key].push(weight);
}

demehin::Tree< std::string, std::string > demehin::Graph::getVrts() const
{
  Tree< std::string, std::string > vrts;
  for (const auto& edge : edges)
  {
    vrts[edge.first.first];
    vrts[edge.first.second];
  }
  return vrts;
}
