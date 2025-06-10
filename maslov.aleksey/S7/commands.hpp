#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "graph.hpp"

namespace maslov
{
  void getGraphs(std::ostream & out, const std::unordered_map< std::string, Graph > & graphs);
  void getVertexes(std::istream & in, std::ostream & out, const std::unordered_map< std::string, Graph > & graphs);
  void getOutbound(std::istream & in, std::ostream & out, const std::unordered_map< std::string, Graph > & graphs);
  void getInbound(std::istream & in, std::ostream & out, const std::unordered_map< std::string, Graph > & graphs);
  void createEdge(std::istream & in, std::unordered_map< std::string, Graph > & graphs);
  void deleteEdge(std::istream & in, std::unordered_map< std::string, Graph > & graphs);
  void createGraph(std::istream & in, std::unordered_map< std::string, Graph > & graphs);
  void mergeGraph(std::istream & in, std::unordered_map< std::string, Graph > & graphs);
  void extractGraph(std::istream & in, std::unordered_map< std::string, Graph > & graphs);
}

#endif
