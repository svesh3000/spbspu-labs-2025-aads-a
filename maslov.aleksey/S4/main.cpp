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
    while (file >> key && file >> value)
    {
      dict[key] = value;
    }
    dicts[dataset] = dict;
  }
}

void inputCommands(std::istream & in, Dictionaries & dicts)
{
}

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    std::cerr << "ERROR: file\n";
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
