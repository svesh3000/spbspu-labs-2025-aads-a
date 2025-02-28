#include "io_containers.hpp"

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

void zakirov::output_result (std::ostream & out, list_pair & forward_list)
{
  
}
