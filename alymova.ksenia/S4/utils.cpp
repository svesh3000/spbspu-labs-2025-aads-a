#include <string>
#include <iostream>
#include <exception>
#include "utils.hpp"

void alymova::PrintCommand::operator()(const CompositeDataset_t& dicts)
{
  std::string name;
  in >> name;

  Dataset_t dataset = dicts.at(name);
  out << name;
  for (auto it = dataset.begin(); it != dataset.end(); it++)
  {
    out << ' ' << (*it).first << ' ' << (*it).second;
  }
}

void alymova::ComplementCommand::operator()(CompositeDataset_t& dicts)
{
  std::string newname, name1, name2;
  in >> newname >> name1 >> name2;

  Dataset_t dataset1 = dicts.at(name1);
  Dataset_t dataset2 = dicts.at(name2);

  for (auto it = dataset1.begin(); it != dataset1.end(); it++)
  {
    if (dataset2.find((*it).first) == dataset2.end())
    {
      dataset2[(*it).first] = (*it).second;
    }
    else
    {
      dataset2.erase((*it).first);
    }
  }
  dicts[newname] = dataset2;
}

void alymova::IntersectCommand::operator()(CompositeDataset_t& dicts)
{
  std::string newname, name1, name2;
  in >> newname >> name1 >> name2;

  Dataset_t dataset1 = dicts.at(name1);
  Dataset_t dataset2 = dicts.at(name2);
  for (auto it = dataset1.begin(); it != dataset1.end(); it++)
  {
    if (dataset2.find((*it).first) == dataset2.end())
    {
      dataset1.erase((*it).first);
    }
  }
  dicts[newname] = dataset1;
}

void alymova::UnionCommand::operator()(CompositeDataset_t& dicts)
{
  std::string newname, name1, name2;
  in >> newname >> name1 >> name2;

  Dataset_t dataset1 = dicts.at(name1);
  Dataset_t dataset2 = dicts.at(name2);
  for (auto it = dataset2.begin(); it != dataset2.end(); it++)
  {
    if (dataset1.find((*it).first) == dataset1.end())
    {
      dataset1[(*it).first] = (*it).second;
    }
  }
  dicts[newname] = dataset1;
}

alymova::Dataset_t alymova::readTree(const std::string& s)
{
  std::string s_local = s;
  Dataset_t tree;
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

alymova::CommandDataset_t alymova::complectCommands()
{
  return
  {
    {"print", PrintCommand{std::cin, std::cout}},
    {"complement", ComplementCommand{std::cin}},
    {"intersect", IntersectCommand{std::cin}},
    {"union", UnionCommand{std::cin}}
  };
}


/*void alymova::print(std::ostream& out, const CompositeDataset_t& dicts, const std::string& dataset)
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

alymova::Dataset_t alymova::complement(CompositeDataset_t& dicts, const std::string& newdataset,
  const std::string& dataset1, const std::string& dataset2)
{
  auto it_dict1 = dicts.find(dataset1);
  auto it_dict2 = dicts.find(dataset2);
  if (it_dict1 == dicts.end() || it_dict2 == dicts.end())
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
  Dataset_t new_dict;
  Dataset_t dict1 = (*it_dict1).second;
  Dataset_t dict2 = (*it_dict2).second;
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

alymova::Dataset_t alymova::intersect(CompositeDataset_t& dicts, const std::string& newdataset,
  const std::string& dataset1, const std::string& dataset2)
{
  auto it_dict1 = dicts.find(dataset1);
  auto it_dict2 = dicts.find(dataset2);
  if (it_dict1 == dicts.end() || it_dict2 == dicts.end())
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
  Dataset_t new_dict;
  Dataset_t dict1 = (*it_dict1).second;
  Dataset_t dict2 = (*it_dict2).second;
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

alymova::Dataset_t alymova::unionDict(CompositeDataset_t& dicts, const std::string& newdataset,
  const std::string& dataset1, const std::string& dataset2)
{
  auto it_dict1 = dicts.find(dataset1);
  auto it_dict2 = dicts.find(dataset2);
  if (it_dict1 == dicts.end() || it_dict2 == dicts.end())
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
  Dataset_t new_dict;
  Dataset_t dict1 = (*it_dict1).second;
  Dataset_t dict2 = (*it_dict2).second;
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
}*/
