#include "datasetCommands.hpp"
#include <iostream>
#include <limits>

std::map< std::string, std::map< int, std::string > > abramov::getDataSets(std::ifstream &in)
{
  std::map< std::string, std::map< int, std::string > > collection;
  while (in)
  {
    std::string name;
    in >> name;
    std::map< int, std::string > dict;
    int k;
    std::string s;
    while(in && in.peek() != '\n')
    {
      in >> k >> s;
      dict[k] = s;
    }
    collection[name] = dict;
  }
  return collection;
}

void abramov::printDataSet(const std::string &name, const std::map< std::string, std::map< int, std::string > > &dicts)
{
  std::cout << name << " ";
  std::map< int, std::string > dict = dicts.find(name)->second;
  for (auto it = dict.begin(); it != --dict.end(); ++it)
  {
    std::cout << it->first << " " << it->second << " ";
  }
  std::cout << (--dict.end())->first << " " << (--dict.end())->second << "\n";
}

std::map< int, std::string > abramov::complementDataSets(const std::string &s1, const std::string &s2, const std::map< std::string, std::map< int, std::string > > &dicts)
{
  std::map< int, std::string > dict1 = dicts.find(s1)->second;
  std::map< int, std::string > dict2 = dicts.find(s2)->second;
  std::map< int, std::string > res = std::map< int, std::string >();
  for (auto it = dict1.begin(); it != dict1.end(); ++it)
  {
    if (dict2.find(it->first) == dict2.end())
    {
      res[it->first] = it->second;
    }
  }
  return res;
}

std::map< int, std::string > abramov::intersectDataSets(const std::string &s1, const std::string &s2, const std::map< std::string, std::map< int, std::string > > &dicts)
{
  std::map< int, std::string > dict1 = dicts.find(s1)->second;
  std::map< int, std::string > dict2 = dicts.find(s2)->second;
  std::map< int, std::string > res = std::map< int, std::string >();
  for (auto it = dict1.begin(); it != dict1.end(); ++it)
  {
    if (dict2.find(it->first) != dict2.end())
    {
      res[it->first] = it->second;
    }
  }
  return res;
}

std::map< int, std::string > abramov::unionDataSets(const std::string &s1, const std::string &s2, const std::map< std::string, std::map< int, std::string > > &dicts)
{
  std::map< int, std::string > dict1 = dicts.find(s1)->second;
  std::map< int, std::string > dict2 = dicts.find(s2)->second;
  std::map< int, std::string > res = std::map< int, std::string >();
  for (auto it = dict1.begin(); it != dict1.end(); ++it)
  {
    res[it->first] = it->second;
  }
  for (auto it = dict2.begin(); it != dict2.end(); ++it)
  {
    if (res.find(it->first) != res.end())
    {
      res[it->first] = it->second;
    }
  }
  return res;
}

void abramov::doCommand(const std::string &s, std::istream &in, std::map< std::string, std::map< int, std::string > > &dicts)
{
  std::string s1;
  std::string s2;
  if (s == "PRINT")
  {
    in >> s1;
    printDataSet(s1, dicts);
  }
  else if (s == "COMPLEMENT")
  {
    std::string name;
    in >> name >> s1 >> s2;
    dicts[name] = complementDataSets(s1, s2, dicts);
  }
  else if (s == "INTERSECT")
  {
    std::string name;
    in >> name >> s1 >> s2;
    dicts[name] = intersectDataSets(s1, s2, dicts);
  }
  else if (s == "UNION")
  {
    std::string name;
    in >> name >> s1 >> s2;
    dicts[name] = unionDataSets(s1, s2, dicts);
  }
  else
  {
    std::cout << "<INVALID COMMAND>\n";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }
}
