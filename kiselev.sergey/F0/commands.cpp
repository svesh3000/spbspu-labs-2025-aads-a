#include "commands.hpp"
#include <stdexcept>
#include <string>
#include <iostream>

void kiselev::doNewDict(std::istream& in, Dicts& dicts)
{
  std::string newDict;
  in >> newDict;
  if (dicts.find(newDict) != dicts.end())
  {
    std::cout << "<DICTIONARY ALREADY EXISTS>\n";
    return;
  }
  dicts[newDict];
}

void kiselev::doDeleteDict(std::istream& in, Dicts& dicts)
{
  std::string dict;
  in >> dict;
  if (dicts.find(dict) == dicts.end())
  {
    std::cout << "<DICTIONARY NOT FOUND>\n";
    return;
  }
  dicts.erase(dict);
}
