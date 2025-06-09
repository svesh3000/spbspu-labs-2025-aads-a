#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <istream>
#include <string>
#include "tree.hpp"
#include "list.hpp"
namespace kiselev
{
  using Dict = RBTree< std::string, List< std::string > >;
  using Dicts = RBTree< std::string, Dict >;
  void doNewDict(std::istream&, Dicts&);
  void doDeleteDict(std::istream&, Dicts&);
  void doAddElement(std::istream&, Dicts&);
  void doDeleteElement(std::istream&, Dicts&);
  void doListDict(std::ostream&, const Dicts&);
}
#endif
