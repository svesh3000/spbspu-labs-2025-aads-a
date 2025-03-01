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
  unsigned long long int sequence_element = 0;
  list_llint::iterator fillable_iterator = forward_list.before_begin();
  while (in >> sequence_element)
  {
    forward_list.insert_after(fillable_iterator, sequence_element);
    ++fillable_iterator;
  }
}

void zakirov::output_result(std::ostream & out, list_pair & forward_list)
{
  // size_t size = 0;

  list_pair::iterator big_iter = forward_list.begin();
  list_iter list_iterators;
  list_iter::iterator r_iter_list = list_iterators.before_begin();
  list_iter::iterator pre_iter_list;

  while (big_iter != forward_list.end())
  {
    list_iterators.insert_after(r_iter_list, (* big_iter).second.begin());
    ++r_iter_list;
    ++big_iter;
  }

  while (!list_iterators.empty())
  {
    r_iter_list = list_iterators.begin();
    pre_iter_list = list_iterators.before_begin();
    big_iter = forward_list.begin();

    while (r_iter_list != list_iterators.end())
    {
      if ((* r_iter_list) == (* big_iter).second.end())
      {
        ++r_iter_list;
        list_iterators.erase_after(pre_iter_list);
        continue;
      }

      out << ** r_iter_list << ' ';
      ++(* r_iter_list);
      ++r_iter_list;
      ++pre_iter_list;
      ++big_iter;
    }

    out << '\n';
  }
}
