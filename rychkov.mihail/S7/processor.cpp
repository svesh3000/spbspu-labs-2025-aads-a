#include <iostream>
#include <set.hpp>
#include "processor.hpp"

bool rychkov::S7ParseProcessor::graphs(ParserContext& context)
{
  if (map.empty() || !eol(context.in))
  {
    return false;
  }
  Set< std::string > graphs;
  for (const outer_map::value_type& i: map)
  {
    graphs.insert(i.first);
  }
  for (const std::string& i: graphs)
  {
    context.out << i << '\n';
  }
  return true;
}
bool rychkov::S7ParseProcessor::vertexes(ParserContext& context)
{
  std::string name;
  if (!(context.in >> name))
  {
    return false;
  }
  const inner_map& graph = map.at(name);
  if (!eol(context.in))
  {
    return false;
  }
  Set< std::string > points;
  for (const inner_map::value_type& i: graph)
  {
    points.insert(i.first.first);
    points.insert(i.first.second);
  }
  for (const std::string& i: points)
  {
    context.out << i << '\n';
  }
  return true;
}
bool rychkov::S7ParseProcessor::outbound(ParserContext& context)
{
  std::string name, point;
  if (!(context.in >> name >> point))
  {
    return false;
  }
  const inner_map& graph = map.at(name);
  if (!eol(context.in))
  {
    return false;
  }
  MultiSet< std::pair< std::string, unsigned > > edges;
  for (const inner_map::value_type& i: graph)
  {
    if (i.first.first == point)
    {
      for (unsigned weight: i.second)
      {
        edges.emplace(i.first.second, weight);
      }
    }
  }
  if (edges.empty())
  {
    return false;
  }
  for (const decltype(edges)::value_type& i: edges)
  {
    context.out << i.first << ' ' << i.second << '\n';
  }
  return true;
}
bool rychkov::S7ParseProcessor::inbound(ParserContext& context)
{
  std::string name, point;
  if (!(context.in >> name >> point))
  {
    return false;
  }
  const inner_map& graph = map.at(name);
  if (!eol(context.in))
  {
    return false;
  }
  MultiSet< std::pair< std::string, unsigned > > edges;
  for (const inner_map::value_type& i: graph)
  {
    if (i.first.second == point)
    {
      for (unsigned weight: i.second)
      {
        edges.emplace(i.first.first, weight);
      }
    }
  }
  if (edges.empty())
  {
    return false;
  }
  for (const decltype(edges)::value_type& i: edges)
  {
    context.out << i.first << ' ' << i.second << '\n';
  }
  return true;
}
bool rychkov::S7ParseProcessor::bind(ParserContext& context)
{
  std::string name, from, to;
  unsigned weight = 0;
  if (!(context.in >> name >> from >> to >> weight))
  {
    return false;
  }
  inner_map& graph = map.at(name);
  if (!eol(context.in))
  {
    return false;
  }
  graph[{from, to}].push_back(weight);
  return true;
}
bool rychkov::S7ParseProcessor::cut(ParserContext& context)
{
  std::string name, from, to;
  unsigned weight = 0;
  if (!(context.in >> name >> from >> to >> weight))
  {
    return false;
  }
  inner_map& graph = map.at(name);
  if (!eol(context.in))
  {
    return false;
  }
  inner_map::iterator to_erase = graph.find({from, to});
  if (to_erase == graph.end())
  {
    return false;
  }
  if (to_erase->second.size() == 1)
  {
    graph.erase(to_erase);
  }
  else
  {
    if (to_erase->second.remove(weight) == 0)
    {
      return false;
    }
  }
  return true;
}
bool rychkov::S7ParseProcessor::create(ParserContext& context)
{
  std::string name;
  if (!(context.in >> name) || (map.find(name) != map.end()) || !eol(context.in))
  {
    return false;
  }
  map.insert({name, {}});
  return true;
}
bool rychkov::S7ParseProcessor::merge(ParserContext& context)
{
  std::string result, lhs, rhs;
  if (!(context.in >> result >> lhs >> rhs) || (map.find(result) != map.end()) || !eol(context.in))
  {
    return false;
  }
  inner_map& left = map.at(lhs), right = map.at(rhs);
  inner_map& res = map.insert({result, left}).first->second;
  for (const inner_map::value_type& i: right)
  {
    res.insert(i);
  }
  return true;
}
bool rychkov::S7ParseProcessor::extract(ParserContext& context)
{
  return true;
}
