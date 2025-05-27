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
  if (it_name == graphs.end() || !in)
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
  auto it = it_name->second.vertexes.begin();
  if (it != it_name->second.vertexes.end())
  {
    out << it->first;
    ++it;
  }
  for (; it != it_name->second.vertexes.end(); ++it)
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
  if (sorted.empty() && it_name->second.vertexes.find(vertex) == it_name->second.vertexes.end())
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
  auto it = sorted.begin();
  if (it != sorted.end())
  {
    out << it->first << ' ' << it->second;
    ++it;
  }
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
  TwoThreeTree< std::string, std::unordered_multimap< size_t, size_t >, std::less< std::string > > sorted;
  for (auto it = it_name->second.edges.begin(); it != it_name->second.edges.end(); ++it)
  {
    if (it->first.second == vertex)
    {
      sorted[it->first.first].insert(std::make_pair(it->second, it->second));
      //sorted.insert(std::make_pair(it->first.first, it->second));
    }
  }
  if (sorted.empty() && it_name->second.vertexes.find(vertex) == it_name->second.vertexes.end())
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
  auto it = sorted.begin();
  if (it != sorted.end())
  {
    out << it->first;
    for (auto it_weight = it->second.begin(); it_weight != it->second.end(); ++it_weight)
    {
      out << ' ' << it_weight->first;
    }
    ++it;
  }
  for (; it != sorted.end(); ++it)
  {
    out << '\n' << it->first;
    for (auto it_weight = it->second.begin(); it_weight != it->second.end(); ++it_weight)
    {
      out << ' ' << it_weight->second;
    }
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
  it_name->second.addEdge(vertex1, vertex2, weight);
}

void alymova::CutCommand::operator()(GraphsSet& graphs)
{
  std::string graph_name, vertex1, vertex2;
  size_t weight;
  in >> graph_name >> vertex1 >> vertex2 >> weight;
  auto it_name = graphs.find(graph_name);
  if (it_name == graphs.end() || !in)
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
  it_name->second.cutEdge(vertex1, vertex2, weight);
}

void alymova::CreateCommand::operator()(GraphsSet& graphs)
{
  std::string graph_name;
  in >> graph_name;
  if (graphs.find(graph_name) != graphs.end() || !in)
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
  size_t vertexes_cnt;
  in >> vertexes_cnt;

  Graph graph_new;
  std::string vertex;
  for (size_t i = 0; i < vertexes_cnt; ++i)
  {
    if (!(in >> vertex))
    {
      throw std::logic_error("<INVALID COMMAND>");
    }
    graph_new.addVertex(vertex);
  }
  graphs.insert(std::make_pair(graph_name, graph_new));
}

void alymova::MergeCommand::operator()(GraphsSet& graphs)
{
  std::string name_new, name1, name2;
  in >> name_new >> name1 >> name2;
  auto it_name1 = graphs.find(name1);
  auto it_name2 = graphs.find(name2);
  if (graphs.find(name_new) != graphs.end() || it_name1 == graphs.end() || it_name2 == graphs.end() || !in)
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
  Graph graph_new = it_name1->second;
  graph_new.merge(it_name2->second);
  graphs.insert(std::make_pair(name_new, graph_new));
}

void alymova::ExtractCommand::operator()(GraphsSet& graphs)
{
  std::string name_new, name;
  in >> name_new >> name;
  auto it_name = graphs.find(name);
  if (it_name == graphs.end() || graphs.find(name_new) != graphs.end() || !in)
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
  size_t vertexes_cnt;
  in >> vertexes_cnt;

  Graph graph_new;
  std::string vertex;
  for (size_t i = 0; i < vertexes_cnt; ++i)
  {
    if (!(in >> vertex) || !it_name->second.hasVertex(vertex))
    {
      throw std::logic_error("<INVALID COMMAND>");
    }
    graph_new.addVertex(vertex);
  }
  for (auto it = it_name->second.edges.begin(); it != it_name->second.edges.end(); ++it)
  {
    if (graph_new.hasVertex(it->first.first) && graph_new.hasVertex(it->first.second))
    {
      graph_new.addEdge(it->first.first, it->first.second, it->second);
    }
  }
  graphs.insert(std::make_pair(name_new, graph_new));
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
    {"cut", CutCommand{in}},
    {"create", CreateCommand{in}},
    {"merge", MergeCommand{in}},
    {"extract", ExtractCommand{in}}
  };
}
