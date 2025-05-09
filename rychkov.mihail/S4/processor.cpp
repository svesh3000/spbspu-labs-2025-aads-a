#include "processor.hpp"

#include <iostream>
#include <fstream>

bool rychkov::S4ParseProcessor::init(ParserContext& context, int argc, char** argv)
{
  if (argc != 2)
  {
    context.err << "wrong arguments count\n";
    return false;
  }
  std::ifstream file(argv[1]);
  if (!file)
  {
    context.err << "failed to open file \"" << argv[1] << "\"\n";
    return false;
  }
  std::string name;
  while (file >> name)
  {
    // std::pair< outer_map::iterator, bool > ins_result = map.insert(name);
  }
  return true;
}
bool rychkov::S4ParseProcessor::print(ParserContext& context)
{
  std::string name;
  if (!(context.in >> name) || !context.eol())
  {
    return false;
  }
  outer_map::const_iterator data_p = map.find(name);
  if (data_p == map.end())
  {
    return false;
  }
  context.out << data_p->first;
  if (data_p->second.empty())
  {
    context.out << " <EMPTY>\n";
    return true;
  }
  for (const inner_map::value_type& i: data_p->second)
  {
    context.out << ' ' << i.first << ' ' << i.second;
  }
  context.out << '\n';
  return true;
}
bool rychkov::S4ParseProcessor::make_complement(ParserContext& context)
{
  return true;
}
bool rychkov::S4ParseProcessor::make_intersect(ParserContext& context)
{
  return true;
}
bool rychkov::S4ParseProcessor::make_union(ParserContext& context)
{
  std::string name, lhs, rhs;
  if (!(context.in >> name >> lhs >> rhs) || !context.eol())
  {
    return false;
  }
  return true;
}
