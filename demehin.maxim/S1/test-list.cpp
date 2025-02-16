#include <boost/test/unit_test.hpp>
#include <list/list.hpp>

BOOST_AUTO_TEST_CASE(list_test)
{
  demehin::List< int > list;
  BOOST_TEST(list.size() == 0);
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  int nums[3] = {};
  int i = 0;
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
  //demehin::List< int > list3(std::move(list2));
  //BOOST_TEST(list3.front() == 2);
}
