#include "io_containers.hpp"
#include <cstring>

void get_list_pair(std::istream & in, list_pair & forward_list)
{
  std::string sequence_name;
  list_llint sequence_num = {};
  list_pair::iterator fillable_iterator = forward_list.begin();
  while (in >> sequence_name)
  {
    zakirov::get_list_llint(in, sequence_num);
    forward_list.insert_after(fillable_iterator, {sequence_name, sequence_num});
    ++fillable_iterator;
  }
}

void zakirov::get_list_llint(std::istream & in, list_llint & forward_list)
{
  long long int sequence_element = 0;
  list_llint::iterator fillable_iterator = forward_list.begin();
  while (in >> sequence_element)
  {
    fillable_iterator = forward_list.insert_after(fillable_iterator++, sequence_element);
  }
}

void zakirov::output_result(std::ostream & out, list_pair & forward_list)
{
  size_t size = 0;
  list_iter iterators_llint;
  list_pair list_temp = forward_list;
  list_pair::iterator big_iterator = list_temp.begin();
  list_iter::iterator position = iterators_llint.before_begin();
  out << (* big_iterator).first;
  while (big_iterator != list_temp.end())
  {
    out << ' ' << (* big_iterator).first;
    iterators_llint.insert_after(position++, (* big_iterator).second.begin());
    ++size;
  }

  out << '\n';
  while (iterators_llint.begin() != iterators_llint.end())
  {
    position = iterators_llint.begin();
    for (size_t i = 0; i < size; ++i)
    {
      out << *(* position);
      ++(* position);
      ++position;
    }
  }
}
