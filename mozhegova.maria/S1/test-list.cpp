#include <boost/test/unit_test.hpp>
#include <sstream>
#include "list.hpp"

namespace
{
  template< typename T >
  std::ostream & printList(std::ostream & out, mozhegova::List< T > list)
  {
    for (auto it = list.begin(); it != list.end(); it++)
    {
      out << *it;
    }
    return out;
  }
}

BOOST_AUTO_TEST_CASE(capacity)
{
  mozhegova::List< int > list;
  BOOST_TEST(list.empty());
  BOOST_TEST(list.size() == 0);
  list.push_back(1);
  BOOST_TEST(!list.empty());
  list.clear();
  BOOST_TEST(list.empty());
}

BOOST_AUTO_TEST_CASE(front_back)
{
  mozhegova::List< int > list({1, 2, 3});
  BOOST_TEST(list.front() == 1);
  BOOST_TEST(list.back() == 3);
}

BOOST_AUTO_TEST_CASE(push_pop)
{
  mozhegova::List< int > list;
  list.push_front(1);
  BOOST_TEST(list.front() == 1);
  list.push_front(2);
  BOOST_TEST(list.front() == 2);
  list.pop_front();
  BOOST_TEST(list.front() == 1);
  list.pop_back();
  BOOST_TEST(list.empty());
  list.push_back(1);
  BOOST_TEST(list.back() == 1);
  list.push_back(2);
  BOOST_TEST(list.back() == 2);
}

BOOST_AUTO_TEST_CASE(swap)
{
  mozhegova::List< int > list1({1, 2, 3});
  mozhegova::List< int > list2({10, 20, 30});
  list1.swap(list2);
  std::ostringstream out1;
  printList(out1, list1);
  BOOST_TEST(out1.str() == "102030");
  std::ostringstream out2;
  printList(out2, list2);
  BOOST_TEST(out2.str() == "123");
}

BOOST_AUTO_TEST_CASE(iterators)
{
  mozhegova::List< int > list({1, 2, 3});
  BOOST_TEST(*(list.begin()) == 1);
  BOOST_TEST(*(list.cbegin()) == 1);
}
