#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iostream>
#include <AVLtree.hpp>
#include <list.hpp>

namespace tkach
{
  using tree_of_words = AvlTree< std::string, List< std::string > >;
  using tree_of_dict = AvlTree< std::string, tree_of_words >;
  void import(std::istream& in, AvlTree< std::string, AvlTree< std::string, List< std::string > > >& avltree);
  void addWord(std::istream& in, AvlTree< std::string, AvlTree< std::string, List< std::string > > >& avltree);
  void removeWord(std::istream& in, AvlTree< std::string, AvlTree< std::string, List< std::string > > >& avltree);
  void printAll(std::ostream& out, const AvlTree< std::string, AvlTree< std::string, List< std::string > > >& avltree);
}

#endif
