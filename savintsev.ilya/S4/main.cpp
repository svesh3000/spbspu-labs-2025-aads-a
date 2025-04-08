#include <map>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>

int main(int argc, char ** argv)
{
  if (argc != 2)
  {
    std::cerr << "ERROR: Incorrect number of arguments\n";
    return 1;
  }

  std::ifstream file(argv[1]);

  if (!file)
  {
    std::cerr << "ERROR: invalid file\n";
    return 1;
  }

  using string = std::string;
  using tree_t = std::map< int, string >;
  using storage_t = std::map< string, tree_t >;

  storage_t dataset;

  while (file)
  {
    string label;
    file >> label;
    tree_t values;
    int key;
    string value;
    while (file.peek() != '\n' && file)
    {
      file >> key >> value;
      values[key] = value;
    }
    dataset[label] = values;
  }

  string command;
  while (std::cin)
  {
    std::cin >> command;
    if (command == "print")
    {
      string label;
      std::cin >> label;
      tree_t values = dataset[label];
      if (values.empty())
      {
        std::cout << "EMPTY\n";
      }
      std::cout << label;
      for (auto it = values.begin(); it != values.end(); ++it)
      {
        std::cout << ' ' << it->first << ' ' << it->second;
      }
      std::cout << '\n';
      command.clear();
    }
  }
}
