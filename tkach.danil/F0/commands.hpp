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
  void doExportOverwrite(std::istream& in, const AvlTree< std::string, AvlTree< std::string, List< std::string > > >& avltree);
  void doExportInEnd(std::istream& in, const AvlTree< std::string, AvlTree< std::string, List< std::string > > >& avltree);
  void addWord(std::istream& in, AvlTree< std::string, AvlTree< std::string, List< std::string > > >& avltree);
  void printcommontranslations(std::istream& in, std::ostream& out, const AvlTree< std::string, AvlTree< std::string, List< std::string > > >& avltree);
  void removeWord(std::istream& in, AvlTree< std::string, AvlTree< std::string, List< std::string > > >& avltree);
  void clear(std::istream& in, AvlTree< std::string, AvlTree< std::string, List< std::string > > >& avltree);
  void addtranslation(std::istream& in, AvlTree< std::string, AvlTree< std::string, List< std::string > > >& avltree);
  void removetranslation(std::istream& in, AvlTree< std::string, AvlTree< std::string, List< std::string > > >& avltree);
  void printAll(std::ostream& out, const AvlTree< std::string, AvlTree< std::string, List< std::string > > >& avltree);
}

#endif
