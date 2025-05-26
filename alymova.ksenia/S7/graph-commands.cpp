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

void alymova::OutboundCommand::operator()(const GraphsSet& graphs)
{
  std::string graph_name, vertex;
  in >> graph_name >> vertex;
  auto it_name = graphs.find(graph_name);
  if (it_name == graphs.end() || !in)
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
  TwoThreeTree< std::string, size_t, std::less< std::string > > sorted;
  for (auto it = it_name->second.edges.begin(); it != it_name->second.edges.end(); ++it)
  {
    if (it->first.first == vertex)
    {
      sorted.insert(std::make_pair(it->first.second, it->second));
    }
  }
  if (sorted.empty())
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
  auto it = sorted.begin();
  out << it->first << ' ' << it->second;
  ++it;
  for (; it != sorted.end(); ++it)
  {
    out << '\n' << it->first << ' ' << it->second;
  }
}

void alymova::InboundCommand::operator()(const GraphsSet& graphs)
{
  std::string graph_name, vertex;
  in >> graph_name >> vertex;
  auto it_name = graphs.find(graph_name);
  if (it_name == graphs.end() || !in)
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
  TwoThreeTree< std::string, size_t, std::less< std::string > > sorted;
  for (auto it = it_name->second.edges.begin(); it != it_name->second.edges.end(); ++it)
  {
    if (it->first.second == vertex)
    {
      sorted.insert(std::make_pair(it->first.first, it->second));
    }
  }
  if (sorted.empty())
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
  auto it = sorted.begin();
  out << it->first << ' ' << it->second;
  ++it;
  for (; it != sorted.end(); ++it)
  {
    out << '\n' << it->first << ' ' << it->second;
  }
}

void alymova::BindCommand::operator()(GraphsSet& graphs)
{
  std::string graph_name, vertex1, vertex2;
  size_t weight;
  in >> graph_name >> vertex1 >> vertex2 >> weight;
  auto it_name = graphs.find(graph_name);
  if (it_name == graphs.end() || !in)
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
  it_name->second.edges.insert(std::make_pair(std::make_pair(vertex1, vertex2), weight));
}

void alymova::CutCommand::operator()(GraphsSet& graphs)
{
  std::string graph_name, vertex1, vertex2;
  size_t weight;
  in >> graph_name >> vertex1 >> vertex2 >> weight;
  auto it_name = graphs.find(graph_name);
  if (it_name == graphs.end())
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
  auto bound = it_name->second.edges.equal_range(std::make_pair(vertex1, vertex2));
  if (bound.first == bound.second)
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
  for (auto it = bound.first; it != bound.second; ++it)
  {
    if (it->second == weight)
    {
      it_name->second.edges.erase(it);
      return;
    }
  }
  throw std::logic_error("<INVALID COMMAND>");
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
    {"graphs", GraphsCommand{out}},
    {"vertexes", VertexesCommand{in, out}},
    {"outbound", OutboundCommand{in, out}},
    {"inbound", InboundCommand{in, out}},
    {"bind", BindCommand{in}},
    {"cut", CutCommand{in}}
  };
}
