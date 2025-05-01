#include "key_summ.hpp"
#include <calc_utils.hpp>
#include <limits>

namespace
{
  bool isOverflow(int a, int b)
  {
    if ((b > 0 && a > std::numeric_limits< int >::max() - b) || (b < 0 && a < std::numeric_limits< int >::min() - b))
    {
      return true;
    }
    return false;
  }
}

demehin::KeySumm::KeySumm() noexcept:
  val_res(0),
  str_res("")
{}

void demehin::KeySumm::operator()(const std::pair< const int, std::string >& data)
{
  if (isOverflow(val_res, data.first))
  {
    throw std::overflow_error("overflow");
  }
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
