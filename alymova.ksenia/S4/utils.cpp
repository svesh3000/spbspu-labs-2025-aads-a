#include <string>
#include <iostream>
#include <exception>
#include "utils.hpp"

void alymova::print(std::ostream& out, const all_dict_t& dicts, const std::string& dataset)
{
  auto it1 = dicts.find(dataset);
  if (it1 == dicts.end())
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
  if ((*it1).second.empty())
  {
    out << "<EMPTY>";
    return;
  }
  out << (*it1).first;
  for (auto it2 = (*it1).second.begin(); it2 != (*it1).second.end(); it2++)
  {
    out << ' ' << (*it2).first << ' ' << (*it2).second;
  }
}

alymova::dict_t alymova::complement(all_dict_t& dicts, const std::string& newdataset,
  const std::string& dataset1, const std::string& dataset2)
{
  auto it_dict1 = dicts.find(dataset1);
  auto it_dict2 = dicts.find(dataset2);
  if (it_dict1 == dicts.end() || it_dict2 == dicts.end())
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
  dict_t new_dict;
  dict_t dict1 = (*it_dict1).second;
  dict_t dict2 = (*it_dict2).second;
  for (auto it1 = dict1.begin(); it1 != dict1.end(); it1++)
  {
    if (dict2.find((*it1).first) == dict2.end())
    {
      new_dict[(*it1).first] = (*it1).second;
    }
  }
  for (auto it2 = dict2.begin(); it2 != dict2.end(); it2++)
  {
    if (dict1.find((*it2).first) == dict1.end())
    {
      new_dict[(*it2).first] = (*it2).second;
    }
  }
  dicts[newdataset] = new_dict;
  return new_dict;
}

alymova::dict_t alymova::intersect(all_dict_t& dicts, const std::string& newdataset,
  const std::string& dataset1, const std::string& dataset2)
{
  auto it_dict1 = dicts.find(dataset1);
  auto it_dict2 = dicts.find(dataset2);
  if (it_dict1 == dicts.end() || it_dict2 == dicts.end())
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
  dict_t new_dict;
  dict_t dict1 = (*it_dict1).second;
  dict_t dict2 = (*it_dict2).second;
  for (auto it1 = dict1.begin(); it1 != dict1.end(); it1++)
  {
    if (dict2.find((*it1).first) != dict2.end())
    {
      new_dict[(*it1).first] = (*it1).second;
    }
  }
  dicts[newdataset] = new_dict;
  return new_dict;
}

alymova::dict_t alymova::unionDict(all_dict_t& dicts, const std::string& newdataset,
  const std::string& dataset1, const std::string& dataset2)
{
  auto it_dict1 = dicts.find(dataset1);
  auto it_dict2 = dicts.find(dataset2);
  if (it_dict1 == dicts.end() || it_dict2 == dicts.end())
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
  dict_t new_dict;
  dict_t dict1 = (*it_dict1).second;
  dict_t dict2 = (*it_dict2).second;
  for (auto it1 = dict1.begin(); it1 != dict1.end(); it1++)
  {
    if (new_dict.find((*it1).first) == new_dict.end())
    {
      new_dict[(*it1).first] = (*it1).second;
    }
  }
  for (auto it2 = dict2.begin(); it2 != dict2.end(); it2++)
  {
    if (new_dict.find((*it2).first) == new_dict.end())
    {
      new_dict[(*it2).first] = (*it2).second;
    }
  }
  dicts[newdataset] = new_dict;
  return new_dict;
}

alymova::dict_t alymova::readTree(const std::string& s)
{
  std::string s_local = s;
  dict_t tree;
  if (s.empty())
  {
    return tree;
  }
  s_local = s_local.substr(1);

  while (!s_local.empty())
  {
    size_t tree_key;
    std::string tree_value;
    size_t space = s_local.find(" ");
    if (space != std::string::npos)
    {
      tree_key = std::stoll(s_local.substr(0, space));
    }
    s_local = s_local.substr(space + 1);

    space = s_local.find(" ");
    tree_value = s_local.substr(0, space);
    if (space == std::string::npos)
    {
      space = s_local.size() - 1;
    }
    s_local = s_local.substr(space + 1);
    tree[tree_key] = tree_value;
  }
  return tree;
}
