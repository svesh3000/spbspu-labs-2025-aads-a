#include "graph.hpp"

void sveshnikov::Graph::bind(std::pair< std::string, std::string > name, unsigned int weight)
{
  graph_.at(name).push_back(weight);
}
