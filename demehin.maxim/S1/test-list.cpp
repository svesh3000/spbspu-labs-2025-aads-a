#include <boost/test/unit_test.hpp>
#include <list/list.hpp>


namespace
{
  void printIntList(std::ostream& out, demehin::List< int > lst)
  {
    for (auto it = lst.begin(); it != lst.end(); it++)
    {
      out << *it;
    }
  }
}

BOOST_AUTO_TEST_CASE(list_test)
{
  demehin::List< int > list;
  BOOST_TEST(list.size() == 0);
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  int nums[3] = {};
  int i = 0;
  //printIntList(std::cout, list);
  for (auto it = list.begin(); it != list.end(); it++)
  {
    nums[i++] = *it;
  }
  BOOST_TEST(nums[0] == 1);
  BOOST_TEST(nums[2] == 3);
  BOOST_TEST(list.size() == 3);
  BOOST_TEST(list.front() == 1);
  list.pop_front();
  BOOST_TEST(list.size() == 2);
  BOOST_TEST(list.front() == 2);
  demehin::List< int > list2(list);
  BOOST_TEST(list2.size() == 2);
  BOOST_TEST(list2.front() == 2);
  list.swap(list2);
  demehin::List< int > list3;
  for (size_t i = 0; i < 5; i++)
  {
    list3.push_back(0);
  }
  list3.fill(list3.begin(), list3.end(), 1);
  BOOST_TEST(list3.front() == 1);
  BOOST_TEST(list3.back() == 1);
  demehin::List< int > list4(std::move(list3));
  BOOST_TEST(list4.size() == 5);
  BOOST_TEST(list4.front() == 1);
  printIntList(std::cout, list4);
  std::cout << "\n";
  list4.push_back(4);
  list4.push_front(4);
  printIntList(std::cout, list4);
  std::cout << "\n";
  //list4.erase(list4.cend());
  list4.erase(list4.cbegin());
  printIntList(std::cout, list4);
  std::cout << "\n";
  printIntList(std::cout, list);
  std::cout << "\n";
  list4.removeIf([](int value){return value < 2;});
  printIntList(std::cout, list4);
  std::cout << "\n";
  int d = 5;
  list4.insert(list4.cbegin(), d);
  printIntList(std::cout, list4);
  std::cout << "\n";
}
