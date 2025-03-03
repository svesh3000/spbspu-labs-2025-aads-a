#include "io_containers.hpp"
#include <cstring>
#include <iostream>

void zakirov::get_list_pair(std::istream & in, list_pair & forward_list)
{
  std::string sequence_name;
  list_pair::iterator fillable_iterator = forward_list.before_begin();
  while (in >> sequence_name && !in.eof())
  {
    list_ull sequence_num;
    zakirov::get_list_ull(in, sequence_num);
    forward_list.insert_after(fillable_iterator, {sequence_name, sequence_num});
    ++fillable_iterator;
    in.clear();
  }
}

void zakirov::get_list_ull(std::istream & in, list_ull & forward_list)
{
  unsigned long long int sequence_element = 0;
  list_ull::iterator fillable_iterator = forward_list.before_begin();
  while (in >> sequence_element)
  {
    forward_list.insert_after(fillable_iterator, sequence_element);
    ++fillable_iterator;
  }
}

void zakirov::output_result(std::ostream & out, list_pair & forward_list)
{
  list_iter list_iterators;
  list_pair::iterator pair_iter = forward_list.begin();
  list_iter::iterator iter_list = list_iterators.before_begin();
  size_t list_size = 0;
  size_t deleted = 0;
  while (pair_iter != forward_list.end())
  {
    list_iterators.insert_after(iter_list, (* pair_iter).second.begin());
    ++iter_list;
    ++pair_iter;
    ++list_size;
  }

  list_pair::iterator output_iter = forward_list.begin();
  out << (* output_iter).first;
  ++output_iter;
  for (; output_iter != forward_list.end(); ++output_iter)
  {
    out << ' ' << (* output_iter).first;
  }

  out << '\n';
  while (deleted != list_size)
  {
    deleted = 0;
    iter_list = list_iterators.begin();
    pair_iter = forward_list.begin();
    if ((* iter_list) != (* pair_iter).second.end())
    {
      out << ** iter_list;
      ++(* iter_list);
    }
    else
    {
      ++deleted;
    }

    ++iter_list;
    ++pair_iter;

    for (; iter_list != list_iterators.end(); ++iter_list)
    {
      if ((* iter_list) != (* pair_iter).second.end())
      {
        out << ' ' << ** iter_list;
        ++(* iter_list);
      }
      else
      {
        ++deleted;
      }

      ++pair_iter;
    }

    out << '\n';
  }
}
