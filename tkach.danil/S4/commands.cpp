#include "commands.hpp"
#include <cstddef>

void tkach::print(std::istream& in, const AvlTree< std::string, AvlTree< size_t, std::string > >& avltree, std::ostream& out)
{
  std::string name;
  in >> name;
  AvlTree< size_t, std::string > root = avltree.at(name);
  out << name;
  for (auto it = root.cbegin(); it != root.cend(); ++it)
  {
    out << " " << (*it).first << " " << (*it).second;
  }
  out << "\n";
}