#include "dataset.h"
#include <iostream>
#include <fstream>

namespace savintsev
{
  DatasetCollection load_dataset_from(const std::string & filename)
  {
    std::ifstream file(filename);

    DatasetCollection datasets;

    if (!file)
    {
      return datasets;
    }

    while (file)
    {
      std::string label;
      file >> label;
      Dataset values;
      int key;
      std::string value;
      while (file.peek() != '\n' && file)
      {
        file >> key >> value;
        values[key] = value;
      }
      datasets[label] = std::move(values);
    }
    return datasets;
  }

  void print_dataset(const DatasetCollection & datasets)
  {
    std::string label;
    std::cin >> label;
    Dataset values;
    values = datasets.at(label);
    if (values.empty())
    {
      std::cout << "<EMPTY>\n";
      return;
    }
    std::cout << label;
    for (auto it = values.begin(); it != values.end(); ++it)
    {
      std::cout << ' ' << it->first << ' ' << it->second;
    }
    std::cout << '\n';
  }

  void complement_datasets(DatasetCollection & datasets)
  {
    std::string newset, set1, set2;
    std::cin >> newset >> set1 >> set2;
    Dataset values = datasets.at(set1);
    for (auto it = datasets.at(set2).begin(); it != datasets.at(set2).end(); ++it)
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
    datasets[newset] = std::move(values);
  }

  void intersect_datasets(DatasetCollection & datasets)
  {
    std::string newset, set1, set2;
    std::cin >> newset >> set1 >> set2;

    Dataset values = datasets.at(set1);
    for (auto it = values.begin(); it != values.end();)
    {
      if (!datasets.at(set2).count(it->first))
      {
        it = values.erase(it);
      }
      else
      {
        ++it;
      }
    }

    datasets[newset] = std::move(values);
  }

  void union_datasets(DatasetCollection & datasets)
  {
    std::string newset, set1, set2;
    std::cin >> newset >> set1 >> set2;
    Dataset values = datasets.at(set1);
    for (auto it = datasets.at(set2).begin(); it != datasets.at(set2).end(); ++it)
    {
      if (!values.count(it->first))
      {
        values[it->first] = it->second;
      }
    }
    datasets[newset] = std::move(values);
  }

  DatasetCommands register_commands()
  {
    DatasetCommands commands;
    commands.insert({"print", print_dataset});
    commands.insert({"complement", complement_datasets});
    commands.insert({"intersect", intersect_datasets});
    commands.insert({"union", union_datasets});
    return commands;
  }
}
