#include "postfix.hpp"
#include "queue.hpp"
#include "stack.hpp"
#include "infix_to_postfix.hpp"

zakirov::Postfix::Postfix(const std::string & infix)
{
  Queue< std::string > infix_queue;
  size_t old_pos = 0;
  size_t new_pos = 0;
  while (new_pos != std::string::npos)
  {
    new_pos = infix.find(" ", old_pos);
    infix_queue.push(infix.substr(old_pos, new_pos - old_pos));
    old_pos = new_pos + 1;
  }

  postfix = transform_to_postfix(infix_queue);
}

zakirov::Postfix & zakirov::Postfix::operator+(const Postfix & other)
{
  unite_postfixes(other);
  postfix.push("+");
  return *this;
}

zakirov::Postfix & zakirov::Postfix::operator-(const Postfix & other)
{
  unite_postfixes(other);
  postfix.push("-");
  return *this;
}

zakirov::Postfix & zakirov::Postfix::operator*(const Postfix & other)
{
  unite_postfixes(other);
  postfix.push("*");
  return *this;
}

zakirov::Postfix & zakirov::Postfix::operator/(const Postfix & other)
{
  unite_postfixes(other);
  postfix.push("/");
  return *this;
}

zakirov::Postfix & zakirov::Postfix::operator%(const Postfix & other)
{
  unite_postfixes(other);
  postfix.push("%");
  return *this;
}

long long zakirov::Postfix::operator()()
{
  long long result = calculate_postfix_expression(postfix);
  return result;
}

zakirov::Postfix & zakirov::Postfix::unite_postfixes(const Postfix & other)
{
  Postfix temporary(other);
  while (!temporary.postfix.empty())
  {
    postfix.push(temporary.postfix.front());
    temporary.postfix.pop();
  }

  return *this;
}
