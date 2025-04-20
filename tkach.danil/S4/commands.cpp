#include "commands.hpp"
#include <cstddef>
namespace
{
  void printTree(std::ostream& out, const tkach::AvlTree< size_t, std::string >& root)
  {
    printTree(out, root., val_min);

  }
}

void tkach::print(std::istream& in, const AvlTree< std::string, AvlTree< size_t, std::string > >& avltree, std::ostream& out)
{
  std::string name;
  in >> name;
  AvlTree< size_t, std::string > root = avltree.at(name);
  out << name;

}