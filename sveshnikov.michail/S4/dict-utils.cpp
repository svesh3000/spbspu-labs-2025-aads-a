#include "dict-utils.hpp"
#include <fstream>

sveshnikov::DataTree_t sveshnikov::loadDicts(char *filename)
{
  std::ifstream in(filename);
  if (!in.is_open())
  {
    throw std::runtime_error("ERROR: Cannot open file!");
  }

  DataTree_t data;
  std::string name_dict;
  while (in >> name_dict)
  {
    Dict_t dict;
    while (in.peek() != '\n')
    {
      int key = 0;
      if (in >> key && in.peek() != '\n')
      {
        std::string value;
        in >> value;
        dict[key] = value;
      }
      else
      {
        throw std::invalid_argument("ERROR: Incorrect data format!");
      }
    }
    data[name_dict] = dict;
  }
  return data;
}

sveshnikov::CommandHolder_t sveshnikov::getCommands()
{
  CommandHolder_t command_holder;

  command_holder["print"] = print_dict;
  command_holder["complement"] = complement_dict;
  command_holder["intersect"] = intersect_dict;
  command_holder["union"] = union_dict;

  return command_holder;
}

void sveshnikov::print_dict(std::istream &in, const DataTree_t &data)
{
  std::string dataset;
  in >> dataset;
  auto dict = data.find(dataset);
  if (dict->second.empty())
  {
    throw std::logic_error("<EMPTY>");
  }
  std::cout << dataset;
  for (auto it = dict->second.cbegin(); it != dict->second.cend(); it++)
  {
    std::cout << " " << it->first << " " << it->second;
  }
}

void sveshnikov::complement_dict(std::istream &in, DataTree_t &data)
{
  std::string newdataset, dataset_1, dataset_2;
  in >> newdataset >> dataset_1 >> dataset_2;
  Dict_t new_dict;
  auto dict1 = data.find(dataset_1);
  auto dict2 = data.find(dataset_2);
  for (auto it = dict1->second.cbegin(); it != dict1->second.cend(); it++)
  {
    for (auto it = dict1->second.cbegin(); it != dict1->second.cend(); it++)
    {
    }
  }
}
