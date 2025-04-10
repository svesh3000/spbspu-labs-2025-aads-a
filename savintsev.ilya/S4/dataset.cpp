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
      datasets[label] = values;
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
  }

  void intersect_datasets(DatasetCollection & datasets)
  {
    std::string newset, set1, set2;
    std::cin >> newset >> set1 >> set2;
    Dataset values = datasets[set1];
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
  }

  void union_datasets(DatasetCollection & datasets)
  {
    std::string newset, set1, set2;
    std::cin >> newset >> set1 >> set2;
    Dataset values = datasets[set1];
    for (auto it = datasets[set2].begin(); it != datasets[set2].end(); ++it)
    {
      if (!values.count(it->first))
      {
        values[it->first] = it->second;
      }
    }
    datasets[newset] = values;
  }

  DatasetCommands register_commands()
  {
    return
    {
      {"print", print_dataset},
      {"complement", complement_datasets},
      {"intersect", intersect_datasets},
      {"union", union_datasets}
    };
  }
}
