#include <iostream>
#include <fstream>
#include <string>
#include <exception>
#include <map>
#include "utils.hpp"
#include "tree.hpp"

int main(int argc, char** argv)
{
  using namespace alymova;
  using dict_t = std::map< size_t, std::string, std::less< size_t > >;
  using all_dict_t = std::map< std::string, dict_t, std::less< std::string > >;

  std::istream* input = &std::cin;
  std::ostream* out = &std::cout;
  if (argc != 2)
  {
    std::cerr << "<INCORRECT ARGUMENTS>\n";
    return 1;
  }
  std::ifstream file;
  file.open(argv[1]);
  if (!file.is_open())
  {
    std::cerr << "<INCORRECT FILE>\n";
    return 1;
  }
  input = &file;

  try
  {
    all_dict_t dicts;
    std::string dataset;
    while ((*input >> dataset))
    {
      std::string params;
      std::getline(*input, params, '\n');
      dict_t new_tree = readTree(params);
      dicts[dataset] = new_tree;
    }
    if ((*input).fail() && !(*input).eof())
    {
      std::cerr << "<INVALID COMMAND>\n";
      return 1;
    }
    (*input).clear();

    std::string command;
    while ((std::cin >> command))
    {
      if (command == "print")
      {
        std::string dataset;
        std::cin >> dataset;
        print(*out, dicts, dataset);
        *out << '\n';
      }
      else if (command == "complement")
      {
        std::string newdataset;
        std::string dataset1;
        std::string dataset2;
        std::cin >> newdataset >> dataset1 >> dataset2;
        complement(dicts, newdataset, dataset1, dataset2);
      }
      else if (command == "intersect")
      {
        std::string newdataset;
        std::string dataset1;
        std::string dataset2;
        std::cin >> newdataset >> dataset1 >> dataset2;
        intersect(dicts, newdataset, dataset1, dataset2);
      }
      else if (command == "union")
      {
        std::string newdataset;
        std::string dataset1;
        std::string dataset2;
        std::cin >> newdataset >> dataset1 >> dataset2;
        unionDict(dicts, newdataset, dataset1, dataset2);
      }
      else
      {
        throw std::logic_error("<INVALID COMMAND>");
      }
    }
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
}
