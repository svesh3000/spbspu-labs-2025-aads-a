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
  dict_t new_dict;
  auto it1 = dicts.find(dataset1);
  auto it2 = dicts.find(dataset2);
  if (it1 == dicts.end() || it2 == dicts.end())
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
  dict_t dict1 = (*it1).second;
  dict_t dict2 = (*it2).second;
  for (auto it_dict1 = dict1.begin(); it_dict1 != dict1.end(); it_dict1++)
  {
    if (dict2.find((*it_dict1).first) == dict2.end())
    {
      new_dict[(*it_dict1).first] = (*it_dict1).second;
    }
  }
  for (auto it_dict2 = dict2.begin(); it_dict2 != dict2.end(); it_dict2++)
  {
    if (dict1.find((*it_dict2).first) == dict1.end())
    {
      new_dict[(*it_dict2).first] = (*it_dict2).second;
    }
  }
  dicts[newdataset] = new_dict;
  return new_dict;
}

alymova::dict_t alymova::intersect(all_dict_t& dicts, const std::string& newdataset,
  const std::string& dataset1, const std::string& dataset2)
{
  dict_t new_dict;
  auto it1 = dicts.find(dataset1);
  auto it2 = dicts.find(dataset2);
  if (it1 == dicts.end() || it2 == dicts.end())
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
  dict_t dict1 = (*it1).second;
  dict_t dict2 = (*it2).second;
  for (auto it_dict1 = dict1.begin(); it_dict1 != dict1.end(); it_dict1++)
  {
    if (dict2.find((*it_dict1).first) != dict2.end())
    {
      new_dict[(*it_dict1).first] = (*it_dict1).second;
    }
  }
  dicts[newdataset] = new_dict;
  return new_dict;
}

alymova::dict_t alymova::unionDict(all_dict_t& dicts, const std::string& newdataset,
  const std::string& dataset1, const std::string& dataset2)
{
  auto it1 = dicts.find(dataset1);
  auto it2 = dicts.find(dataset2);
  if (it1 == dicts.end() || it2 == dicts.end())
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
  dict_t dict_intersect_result = intersect(dicts, newdataset, dataset1, dataset2);
  dict_t dict_complement = complement(dicts, newdataset, dataset1, dataset2);
  for (auto it = dict_complement.begin(); it != dict_complement.end(); it++)
  {
    dict_intersect_result[(*it).first] = (*it).second;
  }
  dicts[newdataset] = dict_intersect_result;
  return dict_intersect_result;
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
