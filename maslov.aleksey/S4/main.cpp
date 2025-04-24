#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <limits>

using Dictionaries = std::map< std::string, std::map< int, std::string > >;

void inputFile(const std::string & filename, Dictionaries & dicts)
{
  std::ifstream file(filename);
  if (!file.is_open())
  {
    throw std::runtime_error("ERROR: can't open file");
  }
  std::string dataset;
  while (file >> dataset)
  {
    std::map< int, std::string > dict;
    int key;
    std::string value;
    while ((file >> key) && (file >> value))
    {
      dict[key] = value;
    }
    dicts[dataset] = dict;
    file.clear();
  }
}

void printCommand(std::istream & in, const Dictionaries & dicts)
{
  std::string dictName;
  in >> dictName;
  auto it = dicts.find(dictName);
  if (it == dicts.cend())
  {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }
  auto dict = it->second;
  if (dict.empty())
  {
    std::cout << "<EMPTY>\n";
    return;
  }
  std::cout << dictName;
  for (auto it = dict.cbegin(); it != dict.cend(); ++it)
  {
    std::cout << ' ' << it->first << ' ' << it->second;
  }
  std::cout << '\n';
}

void complementCommand(std::istream & in, Dictionaries & dicts)
{
  std::string resultName, dictName1, dictName2;
  in >> resultName >> dictName1 >> dictName2;
  auto it1 = dicts.find(dictName1);
  auto it2 = dicts.find(dictName2);
  if (it1 == dicts.cend() || it2 == dicts.cend())
  {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }
  auto dict1 = it1->second;
  auto dict2 = it2->second;
  std::map< int, std::string > result;
  for (auto it = dict1.cbegin(); it != dict1.cend(); ++it)
  {
    if (dict2.find(it->first) == dict2.cend())
    {
      result[it->first] = it->second;
    }
  }
  dicts[resultName] = result;
}

void intersectCommand(std::istream & in, Dictionaries & dicts)
{
  std::string resultName, dictName1, dictName2;
  in >> resultName >> dictName1 >> dictName2;
  auto it1 = dicts.find(dictName1);
  auto it2 = dicts.find(dictName2);
  if (it1 == dicts.cend() || it2 == dicts.cend())
  {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }
  auto dict1 = it1->second;
  auto dict2 = it2->second;
  std::map< int, std::string > result;
  for (auto it = dict1.cbegin(); it != dict1.cend(); ++it)
  {
    if (dict2.find(it->first) != dict2.cend())
    {
      result[it->first] = it->second;
    }
  }
  dicts[resultName] = result;
}

void unionCommand(std::istream & in, Dictionaries & dicts)
{
  std::string resultName, dictName1, dictName2;
  in >> resultName >> dictName1 >> dictName2;
  auto it1 = dicts.find(dictName1);
  auto it2 = dicts.find(dictName2);
  if (it1 == dicts.cend() || it2 == dicts.cend())
  {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }
  auto dict1 = it1->second;
  auto dict2 = it2->second;
  std::map< int, std::string > result = dict1;
  for (auto it = dict2.cbegin(); it != dict2.cend(); ++it)
  {
    if (result.find(it->first) == result.cend())
    {
      result[it->first] = it->second;
    }
  }
  dicts[resultName] = result;
}

void processCommand(std::istream & in, const std::string & command, Dictionaries & dicts)
{
  if (command == "print")
  {
    printCommand(in, dicts);
  }
  else if (command == "complement")
  {
    complementCommand(in, dicts);
  }
  else if (command == "intersect")
  {
    intersectCommand(in, dicts);
  }
  else if (command == "union")
  {
    unionCommand(in, dicts);
  }
  else
  {
    std::cout << "<INVALID COMMAND>\n";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }
}

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    std::cerr << "ERROR: wrong arguments\n";
    return 1;
  }
  try
  {
    Dictionaries dicts;
    inputFile(argv[1], dicts);
    std::string command;
    while (!std::cin.eof())
    {
      std::cin >> command;
      if (std::cin.eof())
      {
        break;
      }
      processCommand(std::cin, command, dicts);
    }
  }
  catch (const std::exception & e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
}
