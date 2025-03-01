#include <boost/test/unit_test.hpp>
#include "list.hpp"

BOOST_AUTO_TEST_SUITE(ListTest)

BOOST_AUTO_TEST_CASE(DefaultConstructor)
{
    averenkov::List<int> list;
    BOOST_TEST(list.empty());
}

BOOST_AUTO_TEST_CASE(CopyConstructor)
{
    averenkov::List<int> list;
    list.push_back(1);
    list.push_back(2);

    averenkov::List<int> copyList(list);
    BOOST_TEST(copyList.size() == 2);
    BOOST_TEST(copyList.front() == 1);
    BOOST_TEST(copyList.back() == 2);
}

BOOST_AUTO_TEST_CASE(MoveConstructor)
{
    averenkov::List<int> list;
    list.push_back(1);
    list.push_back(2);

    averenkov::List<int> movedList(std::move(list));
    BOOST_TEST(movedList.size() == 2);
    BOOST_TEST(movedList.front() == 1);
    BOOST_TEST(movedList.back() == 2);
    BOOST_TEST(list.empty());
}

BOOST_AUTO_TEST_CASE(FillConstructor)
{
    averenkov::List<int> list(3, 5);
    BOOST_TEST(list.size() == 3);
    BOOST_TEST(list.front() == 5);
    BOOST_TEST(list.back() == 5);
}

BOOST_AUTO_TEST_CASE(BeginEnd)
{
    averenkov::List<int> list;
    list.push_back(1);
    list.push_back(2);

    auto it = list.begin();
    BOOST_TEST(*it == 1);
    ++it;
    BOOST_TEST(*it == 2);
    ++it;
    BOOST_TEST(it == list.end());
}

BOOST_AUTO_TEST_CASE(CBeginCEnd)
{
    averenkov::List<int> list;
    list.push_back(1);
    list.push_back(2);

    auto it = list.cbegin();
    BOOST_TEST(*it == 1);
    ++it;
    BOOST_TEST(*it == 2);
    ++it;
    BOOST_TEST(it == list.cend());
}

BOOST_AUTO_TEST_CASE(FrontBack)
{
    averenkov::List<int> list;
    list.push_back(1);
    list.push_back(2);

    BOOST_TEST(list.front() == 1);
    BOOST_TEST(list.back() == 2);
}

BOOST_AUTO_TEST_CASE(PushFront)
{
    averenkov::List<int> list;
    list.push_front(1);
    list.push_front(2);

    BOOST_TEST(list.front() == 2);
    BOOST_TEST(list.back() == 1);
}

BOOST_AUTO_TEST_CASE(PushBack)
{
    averenkov::List<int> list;
    list.push_back(1);
    list.push_back(2);

    BOOST_TEST(list.front() == 1);
    BOOST_TEST(list.back() == 2);
}

BOOST_AUTO_TEST_CASE(PopFront)
{
    averenkov::List<int> list;
    list.push_back(1);
    list.push_back(2);

    list.pop_front();
    BOOST_TEST(list.front() == 2);
    BOOST_TEST(list.size() == 1);
}

BOOST_AUTO_TEST_CASE(PopBack)
{
    averenkov::List<int> list;
    list.push_back(1);
    list.push_back(2);

    list.pop_back();
    BOOST_TEST(list.back() == 1);
    BOOST_TEST(list.size() == 1);
}

BOOST_AUTO_TEST_CASE(Clear)
{
    averenkov::List<int> list;
    list.push_back(1);
    list.push_back(2);

    list.clear();
    BOOST_TEST(list.empty());
    BOOST_TEST(list.size() == 0);
}

BOOST_AUTO_TEST_CASE(Swap)
{
    averenkov::List<int> list1;
    list1.push_back(1);
    list1.push_back(2);

    averenkov::List<int> list2;
    list2.push_back(3);
    list2.push_back(4);

    list1.swap(list2);
    BOOST_TEST(list1.front() == 3);
    BOOST_TEST(list2.front() == 1);
}

BOOST_AUTO_TEST_CASE(Remove)
{
    averenkov::List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    list.remove(2);
    BOOST_TEST(list.size() == 2);
    BOOST_TEST(list.front() == 1);
    BOOST_TEST(list.back() == 3);
}

BOOST_AUTO_TEST_CASE(RemoveIf)
{
    averenkov::List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    list.remove_if([](int value) { return value % 2 == 0; });
    BOOST_TEST(list.size() == 2);
    BOOST_TEST(list.front() == 1);
    BOOST_TEST(list.back() == 3);
}

/*BOOST_AUTO_TEST_CASE(Splice)
{
    averenkov::List<int> list1;
    list1.push_back(1);
    list1.push_back(2);

    averenkov::List<int> list2;
    list2.push_back(3);
    list2.push_back(4);

    auto it = list1.begin();
    ++it;
    list1.splice(it, list2);

    BOOST_TEST(list1.size() == 4);
    BOOST_TEST(list2.size() == 0);
    BOOST_TEST(list1.front() == 1);
    BOOST_TEST(list1.back() == 2);
}*/

BOOST_AUTO_TEST_CASE(Assign)
{
    averenkov::List<int> list;
    list.assign(3, 5);

    BOOST_TEST(list.size() == 3);
    BOOST_TEST(list.front() == 5);
    BOOST_TEST(list.back() == 5);
}

BOOST_AUTO_TEST_SUITE_END()
