#include "key_summ.hpp"
#include <calc_utils.hpp>

demehin::KeySumm::KeySumm() noexcept:
  val_res(0),
  str_res("")
{}

void demehin::KeySumm::operator()(const std::pair< const int, std::string >& data) noexcept
{
  val_res += data.first;
  if (str_res.size() == 0)
  {
    str_res = data.second;
  }
  else
  {
    str_res = str_res + " " + data.second;
  }
}
