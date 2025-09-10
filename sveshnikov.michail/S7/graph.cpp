#include "graph.hpp"
#include <string>

void sveshnikov::Graph::add(std::pair< std::string, std::string > name, unsigned int weight)
{
  graph_.at(name).push_back(weight);
}
