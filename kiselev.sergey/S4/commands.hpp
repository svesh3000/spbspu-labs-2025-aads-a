#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include "tree.hpp"

namespace kiselev
{
  using data = RBTree< size_t, std::string >;
  using dataset = RBTree< std::string, data >;
}
#endif
