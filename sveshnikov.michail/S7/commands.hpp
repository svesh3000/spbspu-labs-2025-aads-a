#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include "graph.hpp"

namespace sveshnikov
{
  using GraphsMap_t = std::unordered_map< std::string, sveshnikov::Graph >;

  void graph();
  void vertexes();
  void outbound();
  void inbound();
  void bind();
  void cut();
  void create();
  void merge();
  void extract();
}

#endif
