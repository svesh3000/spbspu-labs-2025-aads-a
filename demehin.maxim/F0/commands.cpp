#include "commands.hpp"

void demehin::printHelp(std::ostream& out)
{
  out << "Commands system:\n";
  out << "1. createdict < dictname > - create empty dictionary\n";
  out << "2. deletedict < dictname > - delete excisting dictionary\n";
  out << "3. printdict < dictname > - print dict content\n";
}

void demehin::createDict(std::istream& in, dict_t& dicts)
{
  tree_t dict;
  std::string dict_name;
  in >> dict_name;
  if (dicts.find(dict_name) == dicts.end())
  {
    dicts.insert(std::make_pair(dict_name, dict));
  }
  else
  {
    throw std::logic_error("existent dictionary");
  }
}

void demehin::deleteDict(std::istream& in, dict_t& dicts)
{
  std::string dict_name;
  in >> dict_name;
  if (dicts.find(dict_name) == dicts.end())
  {
    throw std::logic_error("non-existent dictionary");
  }

  dicts.erase(dict_name);
}

void demehin::printDict(std::istream& in, std::ostream& out, const dict_t& dicts)
{
  std::string dict_name;
  in >> dict_name;

  tree_t dict = dicts.at(dict_name);

  for (auto&& key: dict)
  {
    out << key.first;
    for (auto&& translation: key.second)
    {
      out << " " << translation;
    }
    out << "\n";
  }
}
