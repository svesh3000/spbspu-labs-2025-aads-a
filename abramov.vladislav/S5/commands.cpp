#include "commands.hpp"

template< class F >
void abramov::getCommands(CommandTree &commands, DataTree &tree, F f)
{
  commands["ascending"] = std::bind(ascending< F >, std::ref(tree), f);
  commands["descending"] = std::bind(descending< F >, std::ref(tree), f);
  commands["breadth"] = std::bind(breadth< F >, std::ref(tree), f);
}

template< class F >
void abramov::ascending(DataTree &tree, F f)
{
  f = tree.traverse_lnr(f);
}

template< class F >
void abramov::descending(DataTree &tree, F f)
{
  f = tree.traverse_rnl(f);
}

template< class F >
void abramov::breadth(DataTree &tree, F f)
{
  f = tree.traverse_breadth(f);
}



