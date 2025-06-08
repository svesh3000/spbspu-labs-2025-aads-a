#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iostream>
#include <string>
#include <AVLtree.hpp>
#include "graph.hpp"

namespace tkach
{
  void printGraphs(std::ostream& out, const AvlTree< std::string, Graph >& tree_of_graphs);
}

#endif