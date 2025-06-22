#include "dict-utils.hpp"

std::istream& alymova::operator>>(std::istream& in, List< std::string >& list)
{
  std::istream::sentry s(in);
  if (!s)
  {
    return in;
  }
  size_t cnt;
  in >> cnt;
  List< std::string > tested;
  for (size_t i = 0; i < cnt && in; i++)
  {
    std::string word;
    in >> word;
    tested.push_back(word);
  }
  if (!in)
  {
    return in;
  }
  list = tested;
  return in;
}

std::ostream& alymova::operator<<(std::ostream& out, const List< std::string >& list)
{
  std::ostream::sentry s(out);
  if (!s || list.empty())
  {
    return out;
  }
  List< std::string > copy(list);
  copy.sort();
  auto it = copy.begin();
  out << *(it++);
  for (; it != copy.end(); it++)
  {
    out << ' ' << *it;
  }
  return out;
}
