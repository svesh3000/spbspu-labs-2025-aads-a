#include <iostream>
#include <map>
#include <limits>
#include <fstream>
#include <algorithm>
#include <string>

using map_t = std::map< std::string, std::map < int, std::string > >;

void getDictionaries(std::istream& in, map_t& dictionaries)
{
  std::string name, value;
  int key = 0;
  while (!in.eof())
  {
    std::map< int, std::string > dictionary{};
    in >> name;
    while (in && in.peek() != '\n')
    {
      in >> key >> value;
      dictionary.insert({ key, value });
    }
    dictionaries.insert({ name, dictionary });
  }
  std::cin.clear();
}

void printDictionary(map_t& dictionaries)
{
  std::string name = "";
  std::cin >> name;
  const std::map< int, std::string > dictionary = dictionaries.at(name);
  if (dictionary.empty())
  {
    std::cout << "<EMPTY>" << "\n";
    return;
  }
  std::cout << name;
  for (const auto& pair : dictionary)
  {
    std::cout << ' ' << pair.first << ' ' << pair.second;
  }
  std::cout << '\n';
}

void merge(map_t& dictionaries)
{
  std::string new_dataset, dataset_1, dataset_2;
  std::cin >> new_dataset >> dataset_1 >> dataset_2;
  const std::map< int, std::string > lhs = dictionaries.at(dataset_1);
  const std::map< int, std::string > rhs = dictionaries.at(dataset_2);
  std::map< int, std::string > dataset_union{};
  dataset_union.insert(lhs.begin(), lhs.end());
  dataset_union.insert(rhs.begin(), rhs.end());
  dictionaries[new_dataset] = dataset_union;
}

void complement(map_t& dictionaries)
{
  std::string new_dataset, dataset_1, dataset_2;
  std::cin >> new_dataset >> dataset_1 >> dataset_2;
  const std::map< int, std::string > lhs = dictionaries.at(dataset_1);
  const std::map< int, std::string > rhs = dictionaries.at(dataset_2);
  std::map < int, std::string > dataset_complement{};
  for (const auto& pair : lhs)
  {
    if (rhs.find(pair.first) == rhs.end())
    {
      dataset_complement.insert(pair);
    }
  }
  dictionaries[new_dataset] = dataset_complement;
}

void intersect(map_t& dictionaries)
{
  std::string new_dataset, dataset_1, dataset_2;
  std::cin >> new_dataset >> dataset_1 >> dataset_2;
  const std::map< int, std::string > lhs = dictionaries.at(dataset_1);
  const std::map< int, std::string > rhs = dictionaries.at(dataset_2);
  std::map < int, std::string > dataset_intersect{};
  for (const auto& pair : lhs)
  {
    if (rhs.find(pair.first) != rhs.end())
    {
      dataset_intersect.insert(pair);
    }
  }
  dictionaries[new_dataset] = dataset_intersect;
}

enum class CommandType { PRINT, COMPLEMENT, INTERSECT, UNION, INVALID };

CommandType parseCommand(const std::string& cmd)
{
  if (cmd == "print")
  {
    return CommandType::PRINT;
  }
  if (cmd == "complement")
  {
    return CommandType::COMPLEMENT;
  }
  if (cmd == "intersect")
  {
    return CommandType::INTERSECT;
  }
  if (cmd == "union")
  {
    return CommandType::UNION;
  }
  return CommandType::INVALID;
}

int main(int argc, char** argv)
{
  if (argc != 2)
  {
    std::cerr << "< INVALID PARAMETRS COUNT >\n";
    return 1;
  }
  std::ifstream input(argv[1]);
  std::map< std::string, std::map< int, std::string > > dictionaries{};
  getDictionaries(input, dictionaries);

  std::string command = "";

  while (!(std::cin >> command).eof())
  {
    CommandType cmdType = parseCommand(command);
    try
    {
      switch (cmdType)
      {
      case::CommandType::PRINT:
        printDictionary(dictionaries);
        break;
      case::CommandType::COMPLEMENT:
        complement(dictionaries);
        break;
      case::CommandType::INTERSECT:
        intersect(dictionaries);
        break;
      case::CommandType::UNION:
        merge(dictionaries);
        break;
      case::CommandType::INVALID:
        std::cout << "<INVALID COMMAND>\n";
        break;
      default:
        break;
      }
    }
    catch (...)
    {
      std::cout << "<INVALID COMMAND>\n";
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
}
