#include "input_output_dictionaries.hpp"

void lanovenko::getDictionaries(std::istream& in, map_t& dictionaries)
{
  std::string name, value;
  int key = 0;
  while (!in.eof())
  {
    Tree< int, std::string, std::less< int > > dictionary{};
    in >> name;
    while (in && in.peek() != '\n')
    {
      in >> key >> value;
      dictionary.insert({ key, value });
    }
    if (!dictionary.empty())
    {
      dictionaries.insert({ name, dictionary });
    }
  }
  std::cin.clear();
}

void lanovenko::printDictionary(map_t& dictionaries)
{
  std::string name = "";
  std::cin >> name;
  const Tree< int, std::string, std::less < int > > dictionary = dictionaries.at(name);
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
