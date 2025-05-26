#ifndef GRAPH_COMMANDS_HPP
#define GRAPH_COMMANDS_HPP
#include <functional>
#include "graph.hpp"

namespace alymova
{
  using GraphsSet = std::unordered_map< std::string, Graph >;
  using CommandsSet = std::unordered_map< std::string, std::function< void(const GraphsSet&) > >;

  struct GraphsCommand
  {
    std::ostream& out;
    void operator()(const GraphsSet& graphs);
  };
  struct VertexesCommand
  {
    std::istream& in;
    std::ostream& out;
    void operator()(const GraphsSet& graphs);
  };
  struct OutboundCommand
  {
    std::istream& in;
    std::ostream& out;
    void operator()(const GraphsSet& graphs);
  };
  struct InboundCommand
  {
    std::istream& in;
    std::ostream& out;
    void operator()(const GraphsSet& graphs);
  };

  GraphsSet readGraphsFile(std::istream& in);
  CommandsSet complectCommands(std::istream& in, std::ostream& out);
}

#endif
