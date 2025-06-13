#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iostream>
#include <AVLtree.hpp>
#include <list.hpp>

namespace tkach
{
  void imprort(std::istream& in, const AvlTree< std::string, AvlTree< std::string, List< std::string > > >& avltree);
}

#endif