#include <boost/test/unit_test.hpp>
#include "list.hpp"

using namespace duhanina;
using list_t = List<int>;
namespace duhanina {

template <typename T>
friend std::ostream& operator<<(std::ostream& os, const Iterator<T>& it) {
  if (it.ptr_ != nullptr) {
    os << "Iterator(" << *it << ")"; // Используем оператор * для вывода значения
  } else {
    os << "Iterator(nullptr)";
  }
  return os;
}
}
BOOST_AUTO_TEST_CASE(test_default_constructor)
{
  list_t list;
  BOOST_TEST(list.empty());
  BOOST_TEST(list.size() == 0);
}

BOOST_AUTO_TEST_CASE(test_constructor_with_parameters)
{
  list_t list(3, 5);
  BOOST_TEST(list.size() == 3);
  BOOST_TEST(list.front() == 5);
  BOOST_TEST(list.back() == 5);
}

BOOST_AUTO_TEST_CASE(test_copy_constructor)
{
  list_t list1;
  list1.push_back(1);
  list1.push_back(2);
  list_t list2(list1);
  BOOST_TEST(list2.size() == 2);
  BOOST_TEST(list2.front() == 1);
  BOOST_TEST(list2.back() == 2);
}

BOOST_AUTO_TEST_CASE(test_move_constructor)
{
  list_t list1;
  list1.push_back(1);
  list1.push_back(2);
  list_t list2(std::move(list1));
  BOOST_TEST(list2.size() == 2);
  BOOST_TEST(list2.front() == 1);
  BOOST_TEST(list2.back() == 2);
  BOOST_TEST(list1.empty());
}

BOOST_AUTO_TEST_CASE(test_push_front)
{
  list_t list;
  list.push_front(1);
  BOOST_TEST(list.size() == 1);
  BOOST_TEST(list.front() == 1);
  list.push_front(2);
  BOOST_TEST(list.size() == 2);
  BOOST_TEST(list.front() == 2);
}

BOOST_AUTO_TEST_CASE(test_push_back)
{
  list_t list;
  list.push_back(1);
  BOOST_TEST(list.size() == 1);
  BOOST_TEST(list.back() == 1);
  list.push_back(2);
  BOOST_TEST(list.size() == 2);
  BOOST_TEST(list.back() == 2);
}

BOOST_AUTO_TEST_CASE(test_pop_front)
{
  list_t list;
  list.push_back(1);
  list.push_back(2);
  list.pop_front();
  BOOST_TEST(list.size() == 1);
  BOOST_TEST(list.front() == 2);
  list.pop_front();
  BOOST_TEST(list.empty());
}

BOOST_AUTO_TEST_CASE(test_pop_back)
{
  list_t list;
  list.push_back(1);
  list.push_back(2);
  list.pop_back();
  BOOST_TEST(list.size() == 1);
  BOOST_TEST(list.back() == 1);
  list.pop_back();
  BOOST_TEST(list.empty());
}

BOOST_AUTO_TEST_CASE(test_clear)
{
  list_t list;
  list.push_back(1);
  list.push_back(2);
  list.clear();
  BOOST_TEST(list.empty());
  BOOST_TEST(list.size() == 0);
}

BOOST_AUTO_TEST_CASE(test_remove)
{
  list_t list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  list.push_back(2);
  list.remove(2);
  BOOST_TEST(list.size() == 2);
  BOOST_TEST(list.front() == 1);
  BOOST_TEST(list.back() == 3);
}

BOOST_AUTO_TEST_CASE(test_remove_if)
{
  list_t list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  list.push_back(4);
  list.remove_if([](int value) { return value % 2 == 0; });
  BOOST_TEST(list.size() == 2);
  BOOST_TEST(list.front() == 1);
  BOOST_TEST(list.back() == 3);
}

BOOST_AUTO_TEST_CASE(test_assign)
{
  list_t list;
  list.push_back(1);
  list.push_back(2);
  list.assign(3, 5);
  BOOST_TEST(list.size() == 3);
  BOOST_TEST(list.front() == 5);
  BOOST_TEST(list.back() == 5);
}

BOOST_AUTO_TEST_CASE(test_iterators)
{
  list_t list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  auto it = list.begin();
  BOOST_TEST(*it == 1);
  ++it;
  BOOST_TEST(*it == 2);
  ++it;
  BOOST_TEST(*it == 3);
  ++it;
  BOOST_TEST(it == list.end());
}

BOOST_AUTO_TEST_CASE(test_swap)
{
  list_t list1;
  list1.push_back(1);
  list1.push_back(2);
  list_t list2;
  list2.push_back(3);
  list2.push_back(4);
  list1.swap(list2);
  BOOST_TEST(list1.size() == 2);
  BOOST_TEST(list1.front() == 3);
  BOOST_TEST(list1.back() == 4);
  BOOST_TEST(list2.size() == 2);
  BOOST_TEST(list2.front() == 1);
  BOOST_TEST(list2.back() == 2);
}
