#include <boost/test/unit_test.hpp>
#include "list.hpp"

using FwdList = maslov::FwdList< int >;

BOOST_AUTO_TEST_SUITE(constructors)

BOOST_AUTO_TEST_CASE(defaultConstructor)
{
  FwdList list;
  BOOST_TEST(list.empty());
}

BOOST_AUTO_TEST_CASE(fillConstructor)
{
  FwdList list(4, 4);
  BOOST_TEST(list.max_size() == 4);
  for (auto it = list.cbegin(); it != list.cend(); ++it)
  {
    BOOST_TEST(*it == 4);
  }
}

BOOST_AUTO_TEST_CASE(copyConstructor)
{}

BOOST_AUTO_TEST_CASE(moveConstructor)
{}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(operators)

BOOST_AUTO_TEST_CASE(copyOperator)
{}

BOOST_AUTO_TEST_CASE(moveOperator)
{}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(modifiers)

BOOST_AUTO_TEST_CASE(pushFront)
{}

BOOST_AUTO_TEST_CASE(popFront)
{}

BOOST_AUTO_TEST_CASE(swap)
{}

BOOST_AUTO_TEST_CASE(clear)
{}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(operations)

BOOST_AUTO_TEST_CASE(reverse)
{}

BOOST_AUTO_TEST_CASE(remove)
{}

BOOST_AUTO_TEST_CASE(removeIf)
{}

BOOST_AUTO_TEST_SUITE_END()
