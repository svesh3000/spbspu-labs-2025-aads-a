#include <boost/test/unit_test.hpp>
#include "FwdList.hpp"
#include "IteratorFwd.hpp"
#include "ConstIteratorFwd.hpp"
#include <iostream>

// BOOST_AUTO_TEST_CASE(test_element_access)
// {
//   gavrilova::FwdList< int > list;
//   list.push_front(0);
//   list.push_front(1);
//   BOOST_TEST(list.front() == 1);
// }

// BOOST_AUTO_TEST_CASE(test_reverse)
// {
//   gavrilova::FwdList< int > list;
//   list.push_front(0);
//   list.push_front(1);
//   list.push_front(2);
//   list.reverse();
//   BOOST_TEST(list.front() == 0);
// }

// BOOST_AUTO_TEST_CASE(test_assignment_operator)
// {
//   gavrilova::FwdList< int > list1;
//   list1.push_front(0);
//   list1.push_front(1);
//   list1.push_front(2);
//   gavrilova::FwdList< int > list2;
//   list2 = list1;
//   BOOST_TEST(list1.size() == list2.size());
//   BOOST_TEST(list2.front() == list1.front());
// }

BOOST_AUTO_TEST_CASE(test_compare) {
    gavrilova::FwdList< int > list1;
    list1.push_front(0);
    list1.push_front(1);
    list1.push_front(2);
    gavrilova::FwdList< int > list2;
    list2.push_front(2);
    list2.push_front(3);
    list2.push_front(4);
    BOOST_TEST(list1 != list2);
    BOOST_TEST(list1 < list2);
}
BOOST_AUTO_TEST_CASE(test_splice)
{
    gavrilova::FwdList<int> list1;
    list1.push_front(2);
    list1.push_front(1);

    gavrilova::FwdList<int> list2;
    list2.push_front(4);
    list2.push_front(3);

    list1.splice(list1.cbegin(), list2);
    BOOST_TEST(list1.size() == 4);
    BOOST_TEST(list1.front() == 1);
    BOOST_TEST(list2.size() == 0);
    list2.push_front(4);
    list2.push_front(3);
    list1.clear();
    list1.push_front(2);
    list1.push_front(1);
    auto it = list2.cbegin();
    list1.splice(list1.cbegin(), list2, it);
    auto it1 = list1.begin();
    BOOST_TEST(*it1++ == 1);
    BOOST_TEST(*it1++ == 4);
    BOOST_TEST(*it1 == 2);
    BOOST_TEST(list1.size() == 3);
    BOOST_TEST(list2.size() == 1);
}
BOOST_AUTO_TEST_CASE(test_splice2) {
    gavrilova::FwdList<int> list1;
    list1.push_front(4);
    list1.push_front(3);
    list1.push_front(2);
    list1.push_front(1);

    gavrilova::FwdList<int> list2;
    list2.push_front(8);
    list2.push_front(7);
    list2.push_front(6);
    list2.push_front(5);
    auto first = list2.cbegin();
    auto last = list2.cend();
    list1.splice(list1.cbegin(), list2, first, last);
    for (auto it = list1.begin(); it != list1.end(); ++it) {
        std::cout << *it << "\n";
    }
    BOOST_TEST(list2.size() == 1);
    BOOST_TEST(list1.size() == 7);
}