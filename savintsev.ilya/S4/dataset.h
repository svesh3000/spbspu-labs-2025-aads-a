#ifndef DATASET_H
#define DATASET_H
#include <map>
#include <string>
#include <functional>
#include "AVL-tree.h"

using namespace savintsev;

using Dataset = AVLTree< int, std::string >;
using DatasetCollection = AVLTree< std::string, Dataset >;
using DatasetCommands = AVLTree< std::string, std::function< void(DatasetCollection &) > >;

namespace savintsev
{
  DatasetCollection load_dataset_from(const std::string & filename);
  void print_dataset(const DatasetCollection & datasets);

  void complement_datasets(DatasetCollection & datasets);
  void intersect_datasets(DatasetCollection & datasets);
  void union_datasets(DatasetCollection & datasets);

  DatasetCommands register_commands();
}

#endif
