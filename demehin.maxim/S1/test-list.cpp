#include <boost/test/unit_test.hpp>
#include <list/list.hpp>
#include <sstream>

namespace
{
  template< typename T >
  std::ostream& printList(std::ostream& out, demehin::List< T > lst)
  {
    for (auto it = lst.begin(); it != lst.end(); it++)
    {
      out << *it;
    }
    return out;
  }
}

BOOST_AUTO_TEST_CASE(list_construct_test)
{
  demehin::List< int > list;
  demehin::List< int > fill_list(5, 5);
  demehin::List< int > mov_list(std::move(list));
  demehin::List< int > cop_list(mov_list);
  std::initializer_list< int > ilist;
  demehin::List< int > init_list(ilist);
  demehin::List< int > range_list(fill_list.begin(), fill_list.end());
}

BOOST_AUTO_TEST_CASE(list_iter_test)
{
  demehin::List< int > list;
  list.push_back(5);
  list.push_back(4);
  list.push_back(5);
  BOOST_TEST(*(++list.cbegin()) == 4);
  std::ostringstream out;
  printList(out, list);
  BOOST_TEST(out.str() == "545");
}

BOOST_AUTO_TEST_CASE(list_el_access_test)
{
  demehin::List< int > list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  BOOST_TEST(list.front() == 1);
  BOOST_TEST(list.back() == 3);
}

BOOST_AUTO_TEST_CASE(list_capac_test)
{
  demehin::List< int > list;
  BOOST_TEST(list.empty());
  list.assign(5, 5);
  BOOST_TEST(list.size() == 5);
}

BOOST_AUTO_TEST_CASE(list_mods_test)
{
  demehin::List< int > list(3, 5);
  demehin::List< int > list2(3, 4);
  list.push_front(4);
  list.push_back(4);
  std::ostringstream out;
  list.swap(list2);
  printList(out, list2);
  BOOST_TEST(out.str() == "45554");
  list2.pop_back();
  list2.pop_front();
  std::ostringstream out1;
  printList(out1, list2);
  BOOST_TEST(out1.str() == "555");

  list2.clear();
  BOOST_TEST(list2.empty());

  list2.assign(3, 5);
  std::ostringstream out2;
  printList(out2, list2);
  BOOST_TEST(out2.str() == "555");

  std::ostringstream out3;
  list2.erase(list2.cbegin());
  printList(out3, list2);
  BOOST_TEST(out3.str() == "55");
  list2.erase(list2.cbegin(), list2.cend());
  BOOST_TEST(list2.empty());

  list2.push_back(1);
  list2.assign(list.begin(), list.end());
  std::ostringstream out4;
  printList(out4, list2);
  BOOST_TEST(out4.str() == "444");

  std::initializer_list< int > ilist;
  list2.assign(ilist);
  BOOST_TEST(list2.empty());

  list2.insert(list2.cbegin(), 5);
  BOOST_TEST(list2.front() == 5);

  size_t t = 3;
  list2.insert(list2.cbegin(), t, 5);
  std::ostringstream out5;
  printList(out5, list2);
  BOOST_TEST(out5.str() == "5555");

  list2.insert(list2.cbegin(), list.begin(), list.end());
  std::ostringstream out6;
  printList(out6, list2);
  BOOST_TEST(out6.str() == "4445555");

  //list2.insert(list2.cbegin(), ilist);
  //std::ostringstream out7;
  //printList(out7, list2);
  //BOOST_TEST(out7.str() == "4445555");
}

BOOST_AUTO_TEST_CASE(list_operators_test)
{
}

BOOST_AUTO_TEST_CASE(list_test)
{
  demehin::List< int > list1(5, 5);
  BOOST_TEST(*(++list1.begin()) == 5);
  list1.push_front(6);
  BOOST_TEST(list1.front() == 6);
  demehin::List< int > mlist(std::move(list1));

  demehin::List< int > list;
  list.push_back(4);
  list.push_back(5);
  list.push_front(5);
  std::ostringstream out;
  printList(out, list);
  BOOST_TEST(out.str() == "545");
  list.pop_back();
  list.pop_front();
  list.pop_back();
  BOOST_TEST(list.empty());
  BOOST_TEST(list.size() == 0);

  mlist.clear();
  BOOST_TEST(mlist.empty());
}
