#include "graph-commands.hpp"
#include <exception>
#include <tree/tree-2-3.hpp>

void alymova::GraphsCommand::operator()(const GraphsSet& graphs)
{
  TwoThreeTree< std::string, std::string, std::less< std::string > > sorted;
  for (auto it = graphs.begin(); it != graphs.end(); ++it)
  {
    sorted.insert(std::make_pair(it->first, it->first));
  }
  auto it = sorted.begin();
  if (it != sorted.end())
  {
    out << it->first;
    ++it;
  }
  for (; it != sorted.end(); ++it)
  {
    out << '\n' << it->first;
  }
}

void alymova::VertexesCommand::operator()(const GraphsSet& graphs)
{
  std::string name;
  in >> name;
  auto it_name = graphs.find(name);
  if (it_name == graphs.end())
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
  TwoThreeTree< std::string, std::string, std::less< std::string > > sorted;
  for (auto it = it_name->second.edges.begin(); it != it_name->second.edges.end(); ++it)
  {
    sorted.insert(std::make_pair(it->first.first, it->first.first));
    sorted.insert(std::make_pair(it->first.second, it->first.second));
  }
  auto it = sorted.begin();
  if (it != sorted.end())
  {
    out << it->first;
    ++it;
  }
  for (; it != sorted.end(); ++it)
  {
    out << '\n' << it->first;
  }
}

alymova::GraphsSet alymova::readGraphsFile(std::istream& in)
{
  GraphsSet graphs;
  std::string name;
  while (in >> name)
  {
    Graph gr;
    in >> gr;
    if (in)
    {
      graphs.insert(std::make_pair(name, gr));
    }
  }
  if (!in.eof() && in.fail())
  {
    throw std::logic_error("<INCORRECT GRAPHS DESCRIPTION>");
  }
  return graphs;
}

alymova::CommandsSet alymova::complectCommands(std::istream& in, std::ostream& out)
{
  return
  {
    {"GRAPHS", alymova::GraphsCommand{out}},
    {"VERTEXES", alymova::VertexesCommand{in, out}}
  };
}
