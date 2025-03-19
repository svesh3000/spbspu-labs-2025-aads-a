#include <boost/test/unit_test.hpp>
#include <sstream>

#include <stack>
#include "queue.hpp"

template < typename T >
std::ostream& operator<<(std::ostream& out, const zholobov::Queue< T >& queue)
{
  zholobov::Queue< T > temp(queue);
  std::stack< T > medium;
  while (!queue.empty()) {
    medium.push(temp.front());
    temp.pop();
  }

  if (!medium.empty()) {
    out << medium.top();
    medium.pop();
    while (!medium.empty()) {
      out << " " << medium.top();
      medium.pop();
    }
  }
  return out;
}

template < typename T >
std::string to_string(const zholobov::Queue< T >& queue)
{
  std::stringstream ss;
  ss << queue;
  return ss.str();
}

BOOST_AUTO_TEST_SUITE(Queue_Constructors)

BOOST_AUTO_TEST_CASE(default_ctor)
{
  zholobov::Queue< std::string > queue;
  BOOST_TEST(queue.empty());
  BOOST_TEST(to_string(queue) == "");
}

BOOST_AUTO_TEST_CASE(copy_ctor)
{
  zholobov::Queue< std::string > queue;
  queue.push("This");
  queue.push("is");
  queue.push("content");
  zholobov::Queue< std::string > new_queue(queue);
  BOOST_TEST(to_string(queue) == "This is content");
  BOOST_TEST(to_string(new_queue) == "This is content");
}

BOOST_AUTO_TEST_CASE(move_ctor)
{
  zholobov::Queue< std::string > queue;
  queue.push("This");
  queue.push("is");
  queue.push("content");
  zholobov::Queue< std::string > new_queue(std::move(queue));
  BOOST_TEST(to_string(queue) == "");
  BOOST_TEST(to_string(new_queue) == "This is content");
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Queue_Assign_Operators)

BOOST_AUTO_TEST_CASE(copy_assign_operator)
{
  zholobov::Queue< std::string > queue;
  queue.push("This");
  queue.push("is");
  queue.push("content");
  zholobov::Queue< std::string > new_queue = queue;
  BOOST_TEST(to_string(queue) == "This is content");
  BOOST_TEST(to_string(new_queue) == "This is content");
}

BOOST_AUTO_TEST_CASE(move_assign_operator)
{
  zholobov::Queue< std::string > queue;
  queue.push("This");
  queue.push("is");
  queue.push("content");
  zholobov::Queue< std::string > new_queue = std::move(queue);
  BOOST_TEST(to_string(queue) == "");
  BOOST_TEST(to_string(new_queue) == "This is content");
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Queue_Opeartions)

BOOST_AUTO_TEST_CASE(push_copy)
{
  zholobov::Queue< std::string > queue;
  std::string val = "Something";
  queue.push(val);
  BOOST_TEST(to_string(queue) == "Something");
  BOOST_TEST(val == "Something");
}

BOOST_AUTO_TEST_CASE(push_move)
{
  zholobov::Queue< std::string > queue;
  std::string val = "Something";
  queue.push(std::move(val));
  BOOST_TEST(to_string(queue) == "Something");
  BOOST_TEST(val == "");
}

BOOST_AUTO_TEST_CASE(front__back_pop)
{
  zholobov::Queue< std::string > queue;
  queue.push("This");
  BOOST_TEST(queue.front() == "This");
  BOOST_TEST(queue.back() == "This");
  queue.push("is");
  BOOST_TEST(queue.front() == "This");
  BOOST_TEST(queue.back() == "is");
  queue.push("content");
  BOOST_TEST(queue.front() == "This");
  BOOST_TEST(queue.back() == "content");
  queue.pop();
  BOOST_TEST(queue.front() == "is");
  BOOST_TEST(queue.back() == "content");
  queue.pop();
  BOOST_TEST(queue.front() == "content");
  BOOST_TEST(queue.back() == "content");
  queue.pop();
  BOOST_TEST(queue.front() == "content");
  BOOST_TEST(queue.back() == "content");
}

BOOST_AUTO_TEST_CASE(empty)
{
  zholobov::Queue< std::string > queue;
  BOOST_TEST(queue.empty());
  queue.push("Something");
  BOOST_TEST(!queue.empty());
  queue.pop();
  BOOST_TEST(queue.empty());
}

BOOST_AUTO_TEST_SUITE_END()
