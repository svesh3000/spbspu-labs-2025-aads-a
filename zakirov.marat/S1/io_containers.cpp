#include "io_containers.hpp"
#include <cstring>
#include <iostream>

void zakirov::get_list_pair(std::istream & in, list_pair & forward_list)
{
  std::string sequence_name;
  list_llint sequence_num;
  list_pair::iterator fillable_iterator = forward_list.before_begin();
  while (in >> sequence_name && !in.eof())
  {
    zakirov::get_list_llint(in, sequence_num);
    forward_list.insert_after(fillable_iterator, {sequence_name, sequence_num});
    ++fillable_iterator;
    in.clear();
  }
}

void zakirov::get_list_llint(std::istream & in, list_llint & forward_list)
{
  long long int sequence_element = 0;
  list_llint::iterator fillable_iterator = forward_list.before_begin();
  while (in >> sequence_element)
  {
    forward_list.insert_after(fillable_iterator, sequence_element);
    ++fillable_iterator;
  }
}

void zakirov::output_result(std::ostream & out, list_pair & forward_list)
{
  size_t size = 0;
  list_pair list_temp = forward_list;
  list_pair::iterator pre_iterator;
  list_pair::iterator big_iterator = list_temp.begin();
  out << (* big_iterator).first;
  while (big_iterator != list_temp.end())
  {
    out << ' ' << (* big_iterator).first;
    ++big_iterator;
    ++size;
  }

  out << '\n';
  while (size > 0)
  {
    pre_iterator = list_temp.before_begin();
    big_iterator = list_temp.begin();
    size_t deleted = 0;
    for (size_t i = 0; i < size; ++i)
    {
      if ((* big_iterator).second.empty())
      {
        ++big_iterator;
        ++deleted;
        list_temp.erase_after(pre_iterator);
        continue;
      }

      out << *((* big_iterator).second.begin()) << " ";
      (* big_iterator).second.pop_front();
      ++big_iterator;
    }

    out << '\n';
    size -= deleted;
  }
}
