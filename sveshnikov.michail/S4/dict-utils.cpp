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
