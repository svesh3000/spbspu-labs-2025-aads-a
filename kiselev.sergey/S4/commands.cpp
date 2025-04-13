#include "commands.hpp"

void kiselev::print(std::ostream& out, std::istream& in, const dataset& dict)
{
  std::string name;
  in >> name;
  data tree = dict.at(name);
  if (tree.empty())
  {
    out << "<EMPTY>\n";
    return;
  }
  out << name;
  for (auto it = tree.cbegin(); it != tree.cend(); ++it)
  {
    out << " " << (*it).first << " " << (*it).second;
  }
  out << "\n";
}


