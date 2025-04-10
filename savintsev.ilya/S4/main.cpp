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

  storage_t datasets;

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
    datasets[label] = values;
  }

  string command;
  while (std::cin)
  {
    std::cin >> command;
    if (!std::cin)
    {
      break;
    }
    if (command == "print")
    {
      string label;
      std::cin >> label;
      tree_t values;
      values = datasets.at(label);
      if (values.empty())
      {
        std::cout << "EMPTY\n";
        continue;
      }
      std::cout << label;
      for (auto it = values.begin(); it != values.end(); ++it)
      {
        std::cout << ' ' << it->first << ' ' << it->second;
      }
      std::cout << '\n';
      command.clear();
    }
    else if (command == "complement")
    {
      string newset;
      string set1;
      string set2;
      std::cin >> newset >> set1 >> set2;
      tree_t values = datasets.at(set1);
      for (auto it = datasets[set2].begin(); it != datasets[set2].end(); ++it)
      {
        if (values.count(it->first))
        {
          values.erase(it->first);
        }
        else
        {
          values[it->first] = it->second;
        }
      }
      datasets[newset] = values;
      command.clear();
    }
    else if (command == "intersect")
    {
      string newset;
      string set1;
      string set2;
      std::cin >> newset >> set1 >> set2;
      tree_t values = datasets[set1];
      for (auto it = values.begin(), safe = values.begin(); it != values.end(); ++it)
      {
        if (!datasets[set2].count(it->first))
        {
          values.erase(it->first);
          it = safe;
        }
        safe = it;
      }
      datasets[newset] = values;
      command.clear();
    }
    else if (command == "union")
    {
      string newset;
      string set1;
      string set2;
      std::cin >> newset >> set1 >> set2;
      tree_t values = datasets[set1];
      for (auto it = datasets[set2].begin(); it != datasets[set2].end(); ++it)
      {
        if (!values.count(it->first))
        {
          values[it->first] = it->second;
        }
      }
      datasets[newset] = values;
      command.clear();
    }
    else
    {
      std::cout << "INVALID COMMAND\n";
    }
  }
}
