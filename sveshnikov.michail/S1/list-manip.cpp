#include "list-manip.hpp"

size_t sveshnikov::getSizeDataList(iter_t i)
{
  size_t len = 0;
  for (iter_list_ull_t j = i->second.cbegin(); j != i->second.cend(); j++)
  {
    len++;
  }
  return len;
}

size_t sveshnikov::getMaxSizeLists(const list_pair_t &list)
{
  size_t num_lines = 0;
  for (iter_t it = list.cbegin(); it != list.cend(); it++)
  {
    num_lines = std::max(num_lines, getSizeDataList(it));
  }
  return num_lines;
}


void sveshnikov::transposeDataList(list_pair_t &list)
{
  list_pair_t transp_list;
  list_ull_t data;
  for (iter_t it = list.cbegin(); it != list.cend(); it++)
  {
    pair_t sequence = {it->first, data};
    try
    {
      transp_list.push_front(sequence);
    }
    catch(const std::bad_alloc& e)
    {
      transp_list.clear();
      throw;
    }
  }
  iter_t it_transp = transp_list.cbegin();
  size_t max_size = getMaxSizeLists(list);
  for (size_t num_lines = 0; num_lines < max_size; num_lines++, it_transp++)
  {
    for (iter_t it = list.cbegin(); it != list.cend(); it++)
    {
      if (num_lines >= sveshnikov::getSizeDataList(it))
      {
        continue;
      }
      iter_list_ull_t it_data = it->second.cbegin();
      for (size_t i = 0; i < num_lines - 1; i++)
      {
        it_data++;
      }
    }
  }
}

