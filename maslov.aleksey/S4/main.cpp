#include <map>
#include <string>
#include <iostream>
#include <fstream>

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
  }
}

void printCommand(std::istream & in, const Dictionaries & dicts)
{
  std::string dictName;
  in >> dictName;
  auto it = dicts.find(dictName);
  if (it == dicts.end() || it->second.empty())
  {
    std::cout << "<EMPTY>\n";
    return;
  }
  auto dict = it->second;
  std::cout << dictName;
  for (auto it = dict.begin(); it != dict.end(); ++it)
  {
    std::cout << ' ' << it->first << ' ' << it->second;
  }
  std::cout << '\n';
}

void complementCommand(std::istream & in, const Dictionaries & dicts)
{}

void intersectCommand(std::istream & in, const Dictionaries & dicts)
{}

void unionCommand(std::istream & in, const Dictionaries & dicts)
{}

void processCommand(std::istream & in, const std::string & command, const Dictionaries & dicts)
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
  }
}

void inputCommands(std::istream & in, const Dictionaries & dicts)
{
  std::string command;
  while (!std::cin.eof())
  {
    std::cin >> command;
    processCommand(in, command, dicts);
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
    inputCommands(std::cin, dicts);
  }
  catch (const std::exception & e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
}
