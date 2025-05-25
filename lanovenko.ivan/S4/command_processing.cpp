#include "command_processing.hpp"

void lanovenko::merge(map_t& dictionaries)
{
  std::string new_dataset, dataset_1, dataset_2;
  std::cin >> new_dataset >> dataset_1 >> dataset_2;
  const Tree< int, std::string, std::less< int > > lhs = dictionaries.at(dataset_1);
  const Tree< int, std::string, std::less< int > > rhs = dictionaries.at(dataset_2);
  Tree< int, std::string, std::less < int > > dataset_union{};
  for (const auto& pair : lhs)
  {
    dataset_union.insert(pair);
  }
  for (const auto& pair : rhs)
  {
    dataset_union.insert(pair);
  }
  dictionaries.insert({ new_dataset, dataset_union });
}

void lanovenko::complement(map_t& dictionaries)
{
  std::string new_dataset, dataset_1, dataset_2;
  std::cin >> new_dataset >> dataset_1 >> dataset_2;
  const Tree< int, std::string, std::less< int > > lhs = dictionaries.at(dataset_1);
  const Tree< int, std::string, std::less < int > > rhs = dictionaries.at(dataset_2);
  Tree< int, std::string, std::less<int > > dataset_complement{};
  for (const auto& pair : lhs)
  {
    if (rhs.find(pair.first) == rhs.end())
    {
      dataset_complement.insert(pair);
    }
  }
  dictionaries.insert({ new_dataset, dataset_complement });
}

void lanovenko::intersect(map_t& dictionaries)
{
  std::string new_dataset, dataset_1, dataset_2;
  std::cin >> new_dataset >> dataset_1 >> dataset_2;
  const Tree< int, std::string, std::less < int > > lhs = dictionaries.at(dataset_1);
  const Tree< int, std::string, std::less < int > > rhs = dictionaries.at(dataset_2);
  Tree < int, std::string, std::less < int > > dataset_intersect{};
  for (const auto& pair : lhs)
  {
    if (rhs.find(pair.first) != rhs.end())
    {
      dataset_intersect.insert(pair);
    }
  }
  dictionaries.insert({ new_dataset, dataset_intersect });
}

lanovenko::CommandType lanovenko::parseCommand(const std::string& cmd)
{
  if (cmd == "print")
  {
    return CommandType::PRINT;
  }
  if (cmd == "complement")
  {
    return CommandType::COMPLEMENT;
  }
  if (cmd == "intersect")
  {
    return CommandType::INTERSECT;
  }
  if (cmd == "union")
  {
    return CommandType::UNION;
  }
  return CommandType::INVALID;
}
