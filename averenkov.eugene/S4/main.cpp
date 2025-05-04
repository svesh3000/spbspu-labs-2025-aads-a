#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "BiTree.hpp"

using Dictionary = Tree< int, std::string >;
using DictionaryStorage = Tree< std::string, Dictionary >;
using str = const std::string&;

void loadDictionaries(str filename, DictionaryStorage& storage)
{
  std::ifstream file(filename);
  if (!file)
  {
    std::cerr << "file error\n";
    return;
  }

  std::string line;
  while (std::getline(file, line))
  {
    if (line.empty())
    {
      continue;
    }

    std::istringstream iss(line);
    std::string dictName;
    iss >> dictName;

    Dictionary dict;
    int key;
    std::string value;
    while (iss >> key >> value)
    {
      dict.insert(std::pair< const int, std::string >(key, value));
    }

    storage.insert(std::pair< const std::string, Dictionary >(dictName, dict));
  }
}

void printDictionary(const Dictionary& dict, str name)
{
  if (dict.empty())
  {
    std::cout << "<EMPTY>\n";
    return;
  }

  std::cout << name;
  for (auto it = dict.begin(); it != dict.end(); ++it)
  {
    std::cout << " " << it->first << " " << it->second;
  }
  std::cout << "\n";
}


void complement(DictionaryStorage& storage, str newName, str name1, str name2)
{
  auto dict1 = storage.find(name1);
  auto dict2 = storage.find(name2);
  if (dict1 == storage.end() || dict2 == storage.end())
  {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }

  Dictionary result;
  auto it1 = dict1->second.begin();
  auto it2 = dict2->second.begin();
  auto end1 = dict1->second.end();
  auto end2 = dict2->second.end();
  while (it1 != end1)
  {
    if (it2 == end2 || it1->first < it2->first)
    {
      result.insert({it1->first, it1->second});
      ++it1;
    }
    else if (it1->first > it2->first)
    {
      ++it2;
    }
    else
    {
      ++it1;
      ++it2;
    }
  }
  storage.insert({ newName, result });
}

void intersect(DictionaryStorage& storage, str newName, str name1, str name2)
{
  auto dict1 = storage.find(name1);
  auto dict2 = storage.find(name2);
  if (dict1 == storage.end() || dict2 == storage.end())
  {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }
  Dictionary result;
  auto it1 = dict1->second.begin();
  auto it2 = dict2->second.begin();
  auto end1 = dict1->second.end();
  auto end2 = dict2->second.end();
  while (it1 != end1 && it2 != end2)
  {
    if (it1->first < it2->first)
    {
      ++it1;
    }
    else if (it1->first > it2->first)
    {
      ++it2;
    }
    else
    {
      result.insert({it1->first, it1->second});
      ++it1;
      ++it2;
    }
  }
  storage.insert({ newName, result });
}

void unionDicts(DictionaryStorage& storage, str newName, str name1, str name2)
{
  auto dict1 = storage.find(name1);
  auto dict2 = storage.find(name2);

  if (dict1 == storage.end() || dict2 == storage.end())
  {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }

  Dictionary result;
  auto it1 = dict1->second.begin();
  auto it2 = dict2->second.begin();
  auto end1 = dict1->second.end();
  auto end2 = dict2->second.end();

  while (it1 != end1 && it2 != end2)
  {
    if (it1->first < it2->first)
    {
      result.insert({ it1->first, it1->second });
      ++it1;
    }
    else if (it1->first > it2->first)
    {
      result.insert({ it2->first, it2->second });
      ++it2;
    }
    else
    {
      result.insert({ it1->first, it1->second });
      ++it1;
      ++it2;
    }
  }
  while (it1 != end1)
  {
    result.insert({ it1->first, it1->second });
    ++it1;
  }
  while (it2 != end2)
  {
    result.insert({ it2->first, it2->second });
    ++it2;
  }
  storage.insert({ newName, result });
}

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    std::cerr << "Usage: " << argv[0] << " filename\n";
    return 1;
  }

  DictionaryStorage dictionaries;
  loadDictionaries(argv[1], dictionaries);

  std::string line;
  while (std::getline(std::cin, line))
  {
    std::istringstream iss(line);
    std::string command;
    iss >> command;

    if (command == "print")
    {
      std::string dictName;
      if (iss >> dictName)
      {
        auto dict = dictionaries.find(dictName);
        if (dict != dictionaries.end())
        {
          printDictionary(dict->second, dictName);
        }
        else
        {
          std::cout << "<EMPTY>\n";
        }
      }
      else
      {
        std::cout << "<INVALID COMMAND>\n";
      }
    }
    else if (command == "complement")
    {
      std::string newName, name1, name2;
      if (iss >> newName >> name1 >> name2)
      {
        complement(dictionaries, newName, name1, name2);
      }
      else
      {
        std::cout << "<INVALID COMMAND>\n";
      }
    }
    else if (command == "intersect")
    {
      std::string newName, name1, name2;
      if (iss >> newName >> name1 >> name2)
      {
        intersect(dictionaries, newName, name1, name2);
      }
      else
      {
        std::cout << "<INVALID COMMAND>\n";
      }
    }
    else if (command == "union")
    {
      std::string newName, name1, name2;
      if (iss >> newName >> name1 >> name2)
      {
        unionDicts(dictionaries, newName, name1, name2);
      }
      else
      {
        std::cout << "<INVALID COMMAND>\n";
      }
    }
    else
    {
      std::cout << "<INVALID COMMAND>\n";
    }
  }

  return 0;
}
