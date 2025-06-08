#include "commands.hpp"
#include <AVLtree.hpp>

namespace tkach
{
  void printGraphs(std::ostream& out, const AvlTree< std::string, Graph >& tree_of_graphs)
  {
    if (tree_of_graphs.empty())
    {
      out << "\n";
      return;
    }
    for (auto it = tree_of_graphs.cbegin(); it != tree_of_graphs.cend(); ++it)
    {
      out << it->first << "\n";  
    }
  }
}