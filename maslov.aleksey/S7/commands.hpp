#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "graph.hpp"

namespace maslov
{
  using hashTable = maslov::HashTable< std::string, maslov::Graph >;
  void getGraphs(std::ostream & out, const hashTable & graphs);
  void getVertexes(std::istream & in, std::ostream & out, const hashTable & graphs);
  void getOutbound(std::istream & in, std::ostream & out, const hashTable & graphs);
  void getInbound(std::istream & in, std::ostream & out, const hashTable & graphs);
  void createEdge(std::istream & in, hashTable & graphs);
  void deleteEdge(std::istream & in, hashTable & graphs);
  void createGraph(std::istream & in, hashTable & graphs);
  void mergeGraph(std::istream & in, hashTable & graphs);
  void extractGraph(std::istream & in, hashTable & graphs);
}

#endif
