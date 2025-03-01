#include "read-sequences.hpp"
#include <iostream>

namespace
{
  std::forward_list<int> *readOneSequence(std::istream &in);

  std::forward_list<int> *readOneSequence(std::istream &in)
  {
    size_t size = 5;
    std::forward_list<int> *data_sequence = nullptr;
    size_t i = 0, num = 0;
    while (in >> num)
    {
      i++;
      try
      {
        data_sequence->push_front(num);
      }
      catch(std::bad_alloc &e)
      {
        data_sequence->clear();
        throw;
      }
    }
    if (in.fail() && !in.eof())
    {
      in.clear();
    }
    return data_sequence;
  }
}

std::forward_list<std::pair<std::string, std::forward_list<int> *>> *sveshnikov::readSequences(std::istream& in)
{
  std::forward_list<std::pair<std::string, std::forward_list<int> *>> *list = {};
  std::pair<std::string, std::forward_list<int> *> sequence = {};
  std::string name_sequence;
  std::forward_list<int> *data_sequence = nullptr;
  while (!in.eof())
  {
    std::cin >> name_sequence;
    data_sequence = readOneSequence(std::cin);
    std::pair<std::string, std::forward_list<int> *> sequence = {name_sequence, data_sequence};
    list->push_front(sequence);
  }
  return list;
}
