#ifndef COMMANDS_HPP
#define COMMANDS_HPP
namespace abramov
{
  using CommandTree = BinarySearchTree< std::string, std::function< void(KeySummer &) > >;
  using DataTree = BinarySearchTree< long long int, std::string >;

  template< class F >
  void getCommands(CommandTree &commands, DataTree &tree, F f);
  template< class F >
  void ascending(DataTree &tree, F f);
  template< class F >
  void descending(DataTree &tree, F f);
  template< class F >
  void breadth(DataTree &tree, F f);
}

#endif
