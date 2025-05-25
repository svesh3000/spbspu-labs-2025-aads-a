#include "graph.hpp"

std::istream& alymova::operator>>(std::istream& in, Graph& graph)
{
  std::istream::sentry s(in);
  if (!s)
  {
    return in;
  }
  size_t cnt_edges;
  in >> cnt_edges;
  std::string vertex1, vertex2;
  size_t weidth;
  for (size_t i = 0; i < cnt_edges && in; i++)
  {
    in >> vertex1 >> vertex2 >> weidth;
    if (in)
    {
      graph.edges.insert(std::make_pair(std::make_pair(vertex1, vertex2), weidth));
    }
  }
  return in;
}
std::ostream& alymova::operator<<(std::ostream& out, const Graph& graph)
{
  std::ostream::sentry s(out);
  if (!s)
  {
    return out;
  }
  auto it = graph.edges.begin();
  if (it != graph.edges.end())
  {
    out << it->first.first << ' ' << it->first.second << ' ' << it->second;
    ++it;
  }
  for (; it != graph.edges.end(); ++it)
  {
    out << '\n' << it->first.first << ' ' << it->first.second << ' ' << it->second;
  }
  return out;
}
