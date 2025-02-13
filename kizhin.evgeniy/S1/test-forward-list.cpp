#include <cstddef>
#include <initializer_list>
#include <iterator>
#include <boost/test/unit_test.hpp>

#if 0
#  include "list.hpp"
using ListT = kizhin::List< double >;
#else
#  include <list>
using ListT = std::list< double >;
#endif

void testInvariants(const ListT& list)
{
  BOOST_TEST(list.empty() == (list.size() == 0));
  BOOST_TEST(list.empty() == (list.begin() == list.end()));
  if (list.empty()) {
    return;
  }
  ListT::const_iterator beg = list.begin();
  ListT::const_iterator end = list.end();
  BOOST_TEST(std::addressof(list.front()) == std::addressof(*beg));
  BOOST_TEST(std::addressof(list.back()) == std::addressof(*(--end)));
  size_t count = 1;
  for (; beg != end; ++beg) {
    ++count;
  }
  BOOST_TEST(count == list.size());
}

BOOST_AUTO_TEST_CASE(default_constructor)
{
  const ListT list;
  BOOST_TEST(list.empty());
  testInvariants(list);
}

BOOST_AUTO_TEST_CASE(copy_constructor_from_empty)
{
  const ListT list;
  const ListT copied(list);
  BOOST_TEST(copied.empty());
  testInvariants(copied);
}

BOOST_AUTO_TEST_CASE(copy_constructor)
{
  const ListT list{ 1, 2, 3, 4, 5, 6 };
  const ListT copied(list);
  BOOST_TEST(list.size() == list.size());
  testInvariants(copied);
  BOOST_TEST((list == copied), boost::test_tools::per_element());
}

BOOST_AUTO_TEST_CASE(move_constructor)
{
  const ListT list{ 1, 2, 3, 4, 5, 6 };
  const ListT moved(std::move(list));
  BOOST_TEST(list.size() == list.size());
  testInvariants(moved);
  BOOST_TEST((list == moved), boost::test_tools::per_element());
}

BOOST_AUTO_TEST_CASE(initializer_list_constructor)
{
  const std::initializer_list< ListT::value_type > init{ 1, 2, 3, 4, 5, 6 };
  const ListT list(init);
  BOOST_TEST(list.size() == init.size());
  testInvariants(list);
  BOOST_TEST(std::equal(list.begin(), list.end(), init.begin()));
}

BOOST_AUTO_TEST_CASE(range_constructor)
{
  const std::initializer_list< ListT::value_type > init{ 1, 2, 3, 4, 5, 6 };
  const ListT list(init.begin(), init.end());
  BOOST_TEST(list.size() == init.size());
  testInvariants(list);
  BOOST_TEST(std::equal(list.begin(), list.end(), init.begin()));
}

BOOST_AUTO_TEST_CASE(fill_constructor_empty)
{
  ListT list(0, 10);
  BOOST_TEST(list.empty());
  testInvariants(list);
}

BOOST_AUTO_TEST_CASE(fill_constructor)
{
  constexpr ListT::size_type size = 100;
  constexpr ListT::value_type value = 10;
  const ListT list(size, value);
  BOOST_TEST(list.size() == size);
  testInvariants(list);
  BOOST_TEST(std::all_of(list.begin(), list.end(),
      [](ListT::const_reference v) -> bool { return value == v; }));
}

BOOST_AUTO_TEST_CASE(copy_assignment_operator)
{
  const ListT list{ 1, 2, 3, 4, 5, 6 };
  ListT copied;
  copied = list;
  BOOST_TEST(list.size() == list.size());
  testInvariants(copied);
  BOOST_TEST((list == copied), boost::test_tools::per_element());
}

BOOST_AUTO_TEST_CASE(move_assignment_operator)
{
  const ListT list{ 1, 2, 3, 4, 5, 6 };
  const ListT copied(list);
  ListT moved;
  moved = std::move(list);
  BOOST_TEST(list.size() == copied.size());
  testInvariants(moved);
  BOOST_TEST((moved == copied), boost::test_tools::per_element());
}

BOOST_AUTO_TEST_CASE(initializer_list_assignment_operator)
{
  const std::initializer_list< ListT::value_type > init{ 1, 2, 3, 4, 5, 6 };
  const ListT initied(init);
  ListT list;
  list = init;
  BOOST_TEST(list.size() == initied.size());
  testInvariants(list);
  BOOST_TEST((list == initied), boost::test_tools::per_element());
}
// TODO: stoped here (refactoring)

#if 0
// TODO: IMPORTANT: code duplicating in push_[back|front] tests
BOOST_AUTO_TEST_CASE(push_back_lvalue)
{
  const ListT::value_type value = 7;
  const ListT::size_type initSize = 77;
  ListT list(initSize);
  list.push_back(value);
  BOOST_TEST(list.size() == initSize + 1);
  testInvariants(list);
  BOOST_TEST(list.back() == value);
}

BOOST_AUTO_TEST_CASE(push_back_rvalue)
{
  const ListT::value_type value = 7;
  const ListT::size_type initSize = 77;
  ListT list(initSize);
  list.push_back(std::move(value));
  BOOST_TEST(list.size() == initSize + 1);
  testInvariants(list);
  BOOST_TEST(list.back() == value);
}

BOOST_AUTO_TEST_CASE(push_front_lvalue)
{
  const ListT::value_type value = 7;
  const ListT::size_type initSize = 77;
  ListT list(initSize);
  list.push_front(value);
  BOOST_TEST(list.size() == initSize + 1);
  testInvariants(list);
  BOOST_TEST(list.front() == value);
}

BOOST_AUTO_TEST_CASE(push_front_rvalue)
{
  const ListT::value_type value = 7;
  const ListT::size_type initSize = 77;
  ListT list(initSize);
  list.push_front(std::move(value));
  BOOST_TEST(list.size() == initSize + 1);
  testInvariants(list);
  BOOST_TEST(list.front() == value);
}
#endif

BOOST_AUTO_TEST_CASE(emplace_back_empty)
{
  constexpr ListT::value_type value = 7;
  ListT list;
  list.emplace_back(value);
  BOOST_TEST(list.size() == 1);
  BOOST_TEST(list.front() == value);
  BOOST_TEST(list.back() == value);
  testInvariants(list);
}

BOOST_AUTO_TEST_CASE(emplace_front_empty)
{
  constexpr ListT::value_type value = 7;
  ListT list;
  list.emplace_front(value);
  BOOST_TEST(list.size() == 1);
  BOOST_TEST(list.front() == value);
  BOOST_TEST(list.back() == value);
  testInvariants(list);
}

BOOST_AUTO_TEST_CASE(pop_back)
{
  // TODO: should here be more checks?
  const ListT::size_type initSize = 77;
  ListT list(initSize);
  list.pop_back();
  BOOST_TEST(list.size() == initSize - 1);
  testInvariants(list);
}

BOOST_AUTO_TEST_CASE(pop_front)
{
  const ListT::size_type initSize = 77;
  ListT list(initSize);
  list.pop_front();
  BOOST_TEST(list.size() == initSize - 1);
  testInvariants(list);
}

BOOST_AUTO_TEST_CASE(emplace_back)
{
  const ListT::value_type value = 7;
  const ListT::size_type initSize = 77;
  ListT list(initSize);
  list.emplace_back(value);
  BOOST_TEST(list.size() == initSize + 1);
  testInvariants(list);
  BOOST_TEST(list.back() == value);
}

BOOST_AUTO_TEST_CASE(emplace_front)
{
  const ListT::value_type value = 7;
  const ListT::size_type initSize = 77;
  ListT list(initSize);
  list.emplace_front(value);
  BOOST_TEST(list.size() == initSize + 1);
  testInvariants(list);
  BOOST_TEST(list.front() == value);
}

BOOST_AUTO_TEST_CASE(emplace)
{
  const ListT::value_type value = 7;
  const ListT::size_type initSize = 77;
  ListT list(initSize);
  ListT::const_iterator pos = static_cast< const ListT& >(list).begin();
  std::advance(pos, initSize / 2);
  ListT::iterator it = list.emplace(pos, value);
  BOOST_TEST(list.size() == initSize + 1);
  testInvariants(list);
  BOOST_TEST(*it == value);
}

BOOST_AUTO_TEST_CASE(assign_fill)
{
  constexpr ListT::size_type size = 100;
  const ListT::value_type value = 7;
  ListT list;
  list.assign(size, value);
  BOOST_TEST(list.size() == size);
  testInvariants(list);
  BOOST_TEST(std::all_of(list.begin(), list.end(),
      [&value](ListT::const_reference v) -> bool { return value == v; }));
}

BOOST_AUTO_TEST_CASE(assign_range)
{
  const std::initializer_list< ListT::value_type > init{ 1, 2, 3, 4, 5, 6 };
  ListT list;
  list.assign(init.begin(), init.end());
  BOOST_TEST(list.size() == init.size());
  testInvariants(list);
  BOOST_TEST(std::equal(list.begin(), list.end(), init.begin()));
}

BOOST_AUTO_TEST_CASE(assign_initializer_list)
{
  const std::initializer_list< ListT::value_type > init{ 1, 2, 3, 4, 5, 6 };
  ListT list;
  list.assign(init);
  testInvariants(list);
  BOOST_TEST(list.size() == init.size());
  BOOST_TEST(std::equal(list.begin(), list.end(), init.begin()));
}

// TODO: Remove code duplicating: lvalue/rvalue
BOOST_AUTO_TEST_CASE(insert_lvalue)
{
  const ListT::value_type value = 7;
  const ListT::size_type initSize = 77;
  ListT list(initSize);
  ListT::const_iterator pos = static_cast< const ListT& >(list).begin();
  std::advance(pos, initSize / 2);
  ListT::iterator it = list.insert(pos, value);
  BOOST_TEST(list.size() == initSize + 1);
  testInvariants(list);
  BOOST_TEST(*it == value);
}

BOOST_AUTO_TEST_CASE(insert_rvalue)
{
  const ListT::value_type value = 7;
  const ListT::size_type initSize = 77;
  ListT list(initSize);
  ListT::const_iterator pos = static_cast< const ListT& >(list).begin();
  std::advance(pos, initSize / 2);
  ListT::iterator it = list.insert(pos, std::move(value));
  BOOST_TEST(list.size() == initSize + 1);
  testInvariants(list);
  BOOST_TEST(*it == value);
}

BOOST_AUTO_TEST_CASE(insert_size)
{
  const ListT::value_type value = 7;
  const ListT::size_type initSize = 77;
  const ListT::size_type insertSize = 10;
  ListT list(initSize);
  ListT::const_iterator pos = static_cast< const ListT& >(list).begin();
  std::advance(pos, initSize / 2);
  ListT::iterator it = list.insert(pos, insertSize, value);
  BOOST_TEST(list.size() == initSize + insertSize);
  testInvariants(list);
  BOOST_TEST(*it == value); // TODO: improve test
}

BOOST_AUTO_TEST_CASE(insert_range)
{
  ListT list = { 1, 2, 5 };
  ListT::const_iterator pos = std::next(list.begin(), 2);
  std::initializer_list< ListT::value_type > ins = { 3, 4 };
  list.insert(pos, ins.begin(), ins.end());
  BOOST_TEST((list == ListT{ 1, 2, 3, 4, 5 }), boost::test_tools::per_element());
  BOOST_TEST(list.size() == 5);
  testInvariants(list);
}

BOOST_AUTO_TEST_CASE(insert_initializer_list)
{
  ListT list = { 1, 2, 5 };
  ListT::const_iterator pos = std::next(list.begin(), 2);
  std::initializer_list< ListT::value_type > ins = { 3, 4 };
  list.insert(pos, ins);
  BOOST_TEST((list == ListT{ 1, 2, 3, 4, 5 }), boost::test_tools::per_element());
  BOOST_TEST(list.size() == 5);
  testInvariants(list);
}

// TODO: Code duplicating in iterator and const_iterator erase test versions
BOOST_AUTO_TEST_CASE(erase_iterator)
{
  const ListT::size_type initSize = 77;
  ListT list(initSize);
  ListT::iterator pos = list.begin();
  std::advance(pos, initSize / 2);
  /*ListT::iterator it =*/list.erase(pos);
  BOOST_TEST(list.size() == initSize - 1);
  testInvariants(list); // TODO: improve test
}

BOOST_AUTO_TEST_CASE(erase_const_iterator)
{
  const ListT::size_type initSize = 77;
  ListT list(initSize);
  ListT::const_iterator pos = static_cast< const ListT& >(list).begin();
  std::advance(pos, initSize / 2);
  /*ListT::iterator it =*/list.erase(pos);
  BOOST_TEST(list.size() == initSize - 1);
  testInvariants(list); // TODO: improve test
}

BOOST_AUTO_TEST_CASE(erase_range)
{
  const ListT::size_type initSize = 77;
  ListT list(initSize);
  ListT::const_iterator pos = static_cast< const ListT& >(list).begin();
  std::advance(pos, initSize / 2);
  /*ListT::iterator it =*/list.erase(pos);
  BOOST_TEST(list.size() == initSize - 1);
  testInvariants(list); // TODO: improve test
}

BOOST_AUTO_TEST_CASE(erase_const_range)
{
  const ListT::size_type initSize = 77;
  ListT list(initSize);
  ListT::const_iterator pos = static_cast< const ListT& >(list).begin();
  std::advance(pos, initSize / 2);
  /*ListT::iterator it =*/list.erase(pos);
  BOOST_TEST(list.size() == initSize - 1);
  testInvariants(list); // TODO: improve test
}

BOOST_AUTO_TEST_CASE(remove_value)
{
  const ListT::value_type initValue = 5;
  const ListT::size_type initSize = 77;
  ListT list(initSize, initValue);
  list.remove(initValue);
  BOOST_TEST(list.empty());
  testInvariants(list);
}

BOOST_AUTO_TEST_CASE(remove_predicate)
{
  // TODO: Implement remove tests
}

BOOST_AUTO_TEST_CASE(reverse)
{
  ListT list = { 1, 2, 3, 4, 5 };
  list.reverse();
  BOOST_TEST((list == ListT{ 5, 4, 3, 2, 1 }), boost::test_tools::per_element());
}

BOOST_AUTO_TEST_CASE(unique)
{
  ListT list = { 1, 2, 2, 3, 3, 3, 4 };
  list.unique();
  BOOST_TEST((list == ListT{ 1, 2, 3, 4 }), boost::test_tools::per_element());
}

BOOST_AUTO_TEST_CASE(unique_predicate)
{
  // TODO: Implement unique tests
}

BOOST_AUTO_TEST_CASE(sort)
{
  // TODO: Implement sort tests
}

BOOST_AUTO_TEST_CASE(sort_comparator)
{
  // TODO: Implement sort tests
}

BOOST_AUTO_TEST_CASE(clear)
{
  ListT list(88, 99);
  list.clear();
  BOOST_TEST(list.empty());
  testInvariants(list);
}

BOOST_AUTO_TEST_CASE(swap)
{
  const ListT::value_type value = 7;
  const ListT::size_type initSize = 77;
  ListT empty;
  ListT list(initSize, value);
  empty.swap(list);
  BOOST_TEST(list.empty());
  BOOST_TEST(empty.size() == initSize);
  testInvariants(empty);
  testInvariants(list);
}

// TODO: Add tests: merge, splice, comparison operators

