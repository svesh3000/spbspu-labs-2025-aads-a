#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <iostream>
#include <tree/tree.hpp>
#include <list/list.hpp>

namespace demehin
{
  using list_t = demehin::List< std::string >;
  using tree_t = demehin::Tree< std::string, list_t >;
  using dict_t = demehin::Tree< std::string, tree_t >;

  void printHelp(std::ostream&);
  void createDict(std::istream&, dict_t&);
  void deleteDict(std::istream&, dict_t&);
  void printDict(std::istream&, std::ostream&, const dict_t&);
}

#endif


