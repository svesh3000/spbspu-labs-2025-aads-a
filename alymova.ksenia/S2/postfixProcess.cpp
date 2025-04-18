#include "postfixProcess.hpp"
#include <cstddef>
#include <string>
#include <limits>
#include <stdexcept>

bool alymova::is_overflow_addition(long long int lhs, long long int rhs)
{
  const long long int max_sum = std::numeric_limits< long long int >::max();
  const long long int min_sum = std::numeric_limits< long long int >::min();
  if (lhs > 0 && rhs > 0)
  {
    return ((max_sum - rhs) < lhs);
  }
  if (lhs < 0 && rhs < 0)
  {
    return ((min_sum - rhs) > lhs);
  }
  return false;
}
bool alymova::is_overflow_substraction(long long int lhs, long long int rhs)
{
  const long long int max_substr = std::numeric_limits< long long int >::max();
  const long long int min_substr = std::numeric_limits< long long int >::min();
  if (lhs > 0 && rhs < 0)
  {
    return ((max_substr + rhs) < lhs);
  }
  if (lhs < 0 && rhs > 0)
  {
    return ((min_substr + rhs) > lhs);
  }
  return false;
}
bool alymova::is_overflow_multi(long long int lhs, long long int rhs)
{
  const long long int max_multi = std::numeric_limits< long long int >::max();
  const long long int min_multi = std::numeric_limits< long long int >::min();
  if ((lhs > 0 && rhs > 0) || (lhs < 0 && rhs < 0))
  {
    return (std::abs(max_multi / lhs) < std::abs(rhs));
  }
  else
  {
    return (std::abs(min_multi / lhs) < std::abs(rhs));
  }
  return false;
}
long long int alymova::my_mod(long long int item1, long long int item2)
{
  long long int quot = item1 / item2;
  if (item1 < 0 && item2 < 0)
  {
    quot++;
  }
  if (item1 < 0 && item2 > 0)
  {
    quot--;
  }
  return item1 - quot * item2;
}
bool alymova::is_first_priority(const std::string& token)
{
  return (token == "*" || token == "/" || token == "%");
}
bool alymova::is_second_priority(const std::string& token)
{
  return (token == "+" || token == "-");
}
bool alymova::is_notless_priority(const std::string& token, const std::string& top)
{
  if (token == "*" || token == "/" || token == "%")
  {
    return (top == "*" || top == "/" || top == "%");
  }
  return is_operation(top);
  /*if (is_second_priority(item))
  {
    return (is_first_priority(token) || is_second_priority(token));
  }
  else
  {
    return is_first_priority(token);
  }*/
}
bool alymova::is_operation(const std::string& token)
{
  const std::string operations[5] = {"+", "-", "*", "/", "%"};
  for (std::string s: operations)
  {
    if (token == s)
    {
      return true;
    }
  }
  return false;
}
