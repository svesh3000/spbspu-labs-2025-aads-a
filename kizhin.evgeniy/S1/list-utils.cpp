#include "list-utils.hpp"
#include <limits>
#include <stdexcept>

kizhin::ForwardList< kizhin::NumbersT > kizhin::convert(
    const ForwardList< NumbersT >& source)
{
  using ListIter = NumbersT::const_iterator;
  ForwardList< std::pair< ListIter, ListIter > > iters;
  for (const NumbersT& nums : source) {
    iters.emplaceBack(nums.begin(), nums.end());
  }
  ForwardList< NumbersT > result;
  NumbersT current;
  do {
    current.clear();
    for (std::pair< ListIter, ListIter >& p : iters) {
      if (p.first != p.second) {
        current.pushBack(*p.first);
        ++p.first;
      }
    }
    result.pushBack(current);
  } while (!current.empty());
  result.popBack();
  return result;
}

kizhin::NumbersT::value_type kizhin::safeAccumulate(const NumbersT& nums,
    NumbersT::value_type init)
{
  constexpr NumbersT::value_type limit =
      std::numeric_limits< NumbersT::value_type >::max();
  for (const NumbersT::value_type& num : nums) {
    if (init > limit - num) {
      throw std::overflow_error("Failed to compute sum because of an overflow");
    }
    init += num;
  }
  return init;
}
