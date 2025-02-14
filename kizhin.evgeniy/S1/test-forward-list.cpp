#include "test-utils.hpp"

using kizhin::ListT;

BOOST_AUTO_TEST_SUITE(constructors);

BOOST_AUTO_TEST_CASE(default_constructor)
{
  const ListT list;
  testInvariants(list);
  BOOST_TEST(list.empty());
}

BOOST_AUTO_TEST_CASE(copy_constructor_from_empty)
{
  const ListT list;
  const ListT copied(list);
  testInvariants(copied);
  BOOST_TEST(copied.empty());
}

BOOST_AUTO_TEST_CASE(copy_constructor)
{
  const ListT list{ 1, 2, 3, 4, 5 };
  const ListT copied(list);
  testInvariants(copied);
  BOOST_TEST(copied == list);
}

BOOST_AUTO_TEST_CASE(move_constructor)
{
  const ListT list{ 1, 2, 3, 4, 5 };
  const ListT copied(list);
  const ListT moved(std::move(list));
  testInvariants(moved);
  BOOST_TEST(moved == copied);
}

BOOST_AUTO_TEST_CASE(empty_fill_constructor)
{
  const ListT list(0, 10);
  testInvariants(list);
  BOOST_TEST(list.empty());
}

BOOST_AUTO_TEST_CASE(fill_constructor)
{
  constexpr ListT::size_type size = 100;
  constexpr ListT::value_type value = 10;
  const ListT list(size, value);
  testInvariants(list);
  BOOST_TEST(list.size() == size);
  BOOST_TEST(std::all_of(list.begin(), list.end(), [](ListT::const_reference v) -> bool {
    return value == v;
  }));
}

BOOST_AUTO_TEST_CASE(empty_range_constructor)
{
  const std::initializer_list< ListT::value_type > init{};
  const ListT list(init.begin(), init.end());
  testInvariants(list);
  BOOST_TEST(list.empty());
}

BOOST_AUTO_TEST_CASE(range_constructor)
{
  const std::initializer_list< ListT::value_type > init{ 1, 2, 3, 4, 5 };
  const ListT list(init.begin(), init.end());
  testInvariants(list);
  BOOST_TEST(list.size() == init.size());
  BOOST_TEST(std::equal(list.begin(), list.end(), init.begin()));
}

BOOST_AUTO_TEST_CASE(initializer_list_constructor)
{
  const std::initializer_list< ListT::value_type > init{ 1, 2, 3, 4, 5 };
  const ListT list(init);
  testInvariants(list);
  BOOST_TEST(list.size() == init.size());
  BOOST_TEST(std::equal(list.begin(), list.end(), init.begin()));
}

BOOST_AUTO_TEST_SUITE_END();
BOOST_AUTO_TEST_SUITE(assignment_operators);

BOOST_AUTO_TEST_CASE(copy_assignment_operator)
{
  const ListT list{ 1, 2, 3, 4, 5 };
  ListT copied;
  copied = list;
  testInvariants(copied);
  BOOST_TEST(list == copied);
}

BOOST_AUTO_TEST_CASE(move_assignment_operator)
{
  const ListT list{ 1, 2, 3, 4, 5 };
  const ListT copied(list);
  ListT moved;
  moved = std::move(list);
  testInvariants(moved);
  BOOST_TEST(moved == copied);
}

BOOST_AUTO_TEST_CASE(initializer_list_assignment_operator)
{
  const std::initializer_list< ListT::value_type > init{ 1, 2, 3, 4, 5 };
  const ListT initied(init);
  ListT list;
  list = init;
  testInvariants(list);
  BOOST_TEST(list == initied);
}

BOOST_AUTO_TEST_SUITE_END();
BOOST_AUTO_TEST_SUITE(modifiers);

BOOST_AUTO_TEST_CASE(push_back)
{
  constexpr ListT::value_type value = 7;
  constexpr ListT::size_type initSize = 77;
  ListT list(initSize);
  list.pushBack(value);
  testInvariants(list);
  BOOST_TEST(list.size() == initSize + 1);
  BOOST_TEST(list.back() == value);
}

BOOST_AUTO_TEST_CASE(push_front)
{
  constexpr ListT::value_type value = 7;
  constexpr ListT::size_type initSize = 77;
  ListT list(initSize);
  list.pushFront(value);
  testInvariants(list);
  BOOST_TEST(list.size() == initSize + 1);
  BOOST_TEST(list.front() == value);
}

BOOST_AUTO_TEST_CASE(emplace_back_empty)
{
  constexpr ListT::value_type value = 7;
  ListT list;
  list.emplaceBack(value);
  testInvariants(list);
  BOOST_TEST(list.size() == 1);
  BOOST_TEST(list.front() == value);
  BOOST_TEST(list.back() == value);
}

BOOST_AUTO_TEST_CASE(emplace_front_empty)
{
  constexpr ListT::value_type value = 7;
  ListT list;
  list.emplaceFront(value);
  testInvariants(list);
  BOOST_TEST(list.size() == 1);
  BOOST_TEST(list.front() == value);
  BOOST_TEST(list.back() == value);
}

BOOST_AUTO_TEST_CASE(emplace_back)
{
  constexpr ListT::value_type value = 7;
  constexpr ListT::size_type initSize = 77;
  ListT list(initSize);
  list.emplaceBack(value);
  testInvariants(list);
  BOOST_TEST(list.size() == initSize + 1);
  BOOST_TEST(list.back() == value);
}

BOOST_AUTO_TEST_CASE(emplace_front)
{
  constexpr ListT::value_type value = 7;
  constexpr ListT::size_type initSize = 77;
  ListT list(initSize);
  list.emplaceFront(value);
  testInvariants(list);
  BOOST_TEST(list.size() == initSize + 1);
  BOOST_TEST(list.front() == value);
}

BOOST_AUTO_TEST_CASE(emplace_after_empty)
{
  constexpr ListT::value_type value = 7;
  ListT list;
  list.emplaceAfter(list.begin(), value);
  testInvariants(list);
  BOOST_TEST(list.size() == 1);
  BOOST_TEST(list.front() == value);
}

BOOST_AUTO_TEST_CASE(emplace_after_end)
{
  constexpr ListT::value_type value = 7;
  constexpr ListT::size_type initSize = 77;
  ListT list(initSize);
  ListT::iterator result = list.emplaceAfter(list.end(), value);
  testInvariants(list);
  BOOST_TEST(list.size() == initSize + 1);
  BOOST_TEST(list.back() == value);
  BOOST_TEST(*result == value);
}

BOOST_AUTO_TEST_CASE(emplace_after)
{
  constexpr ListT::value_type value = 7;
  constexpr ListT::size_type initSize = 77;
  ListT list(initSize);
  ListT::iterator result = list.emplaceAfter(list.begin(), value);
  testInvariants(list);
  BOOST_TEST(list.size() == initSize + 1);
  BOOST_TEST(*result == value);
  BOOST_TEST((result == ++list.begin()));
}

BOOST_AUTO_TEST_CASE(pop_back_single_element)
{
  ListT list{ 1 };
  list.popBack();
  testInvariants(list);
  BOOST_TEST(list.empty());
}

BOOST_AUTO_TEST_CASE(pop_front_single_element)
{
  ListT list{ 1 };
  list.popFront();
  testInvariants(list);
  BOOST_TEST(list.empty());
}

BOOST_AUTO_TEST_CASE(pop_back)
{
  const ListT expected{ 1, 2, 3, 4 };
  ListT list{ 1, 2, 3, 4, 5 };
  list.popBack();
  testInvariants(list);
  BOOST_TEST(list == expected);
}

BOOST_AUTO_TEST_CASE(pop_front)
{
  const ListT expected{ 2, 3, 4, 5 };
  ListT list{ 1, 2, 3, 4, 5 };
  list.popFront();
  testInvariants(list);
  BOOST_TEST(list == expected);
}

BOOST_AUTO_TEST_CASE(erase_after_single_element)
{
  const ListT expected{ 1, 3, 4, 5 };
  ListT list{ 1, 2, 3, 4, 5 };
  ListT::iterator result = list.eraseAfter(list.begin());
  testInvariants(list);
  BOOST_TEST(list == expected);
  BOOST_TEST((result == list.begin()));
}

BOOST_AUTO_TEST_CASE(erase_after_empty_range)
{
  ListT list{ 1, 2, 3, 4, 5 };
  const ListT copied(list);
  ListT::iterator result = list.eraseAfter(list.begin(), ++list.begin());
  testInvariants(list);
  BOOST_TEST(list == copied);
  BOOST_TEST((result == list.begin()));
}

BOOST_AUTO_TEST_CASE(erase_after_range)
{
  const ListT expected{ 1, 4, 5 };
  ListT list{ 1, 2, 3, 4, 5 };
  ListT::iterator result = list.eraseAfter(list.begin(), std::next(list.begin(), 3));
  testInvariants(list);
  BOOST_TEST(list == expected);
  BOOST_TEST((result == list.begin()));
}

BOOST_AUTO_TEST_CASE(empty_fill_assign)
{
  ListT list;
  list.assign(0, 0);
  testInvariants(list);
  BOOST_TEST(list.empty());
}

BOOST_AUTO_TEST_CASE(fill_assign)
{
  constexpr ListT::size_type size = 100;
  constexpr ListT::value_type value = 10;
  ListT list;
  list.assign(size, value);
  testInvariants(list);
  BOOST_TEST(list.size() == size);
  BOOST_TEST(std::all_of(list.begin(), list.end(), [](ListT::const_reference v) -> bool {
    return value == v;
  }));
}

BOOST_AUTO_TEST_CASE(empty_range_assign)
{
  const std::initializer_list< ListT::value_type > init{};
  ListT list;
  list.assign(init.begin(), init.end());
  testInvariants(list);
  BOOST_TEST(list.empty());
}

BOOST_AUTO_TEST_CASE(range_assign)
{
  const std::initializer_list< ListT::value_type > init{ 1, 2, 3, 4, 5 };
  ListT list;
  list.assign(init.begin(), init.end());
  testInvariants(list);
  BOOST_TEST(list.size() == init.size());
  BOOST_TEST(std::equal(list.begin(), list.end(), init.begin()));
}

BOOST_AUTO_TEST_CASE(initializer_list_assign)
{
  const std::initializer_list< ListT::value_type > init{ 1, 2, 3, 4, 5 };
  ListT list;
  list.assign(init);
  testInvariants(list);
  BOOST_TEST(list.size() == init.size());
  BOOST_TEST(std::equal(list.begin(), list.end(), init.begin()));
}

BOOST_AUTO_TEST_CASE(insert_after)
{
  constexpr ListT::value_type value = 7;
  constexpr ListT::size_type initSize = 77;
  ListT list(initSize);
  ListT::iterator result = list.insertAfter(list.begin(), value);
  testInvariants(list);
  BOOST_TEST(list.size() == initSize + 1);
  BOOST_TEST(*result == value);
  BOOST_TEST((result == ++list.begin()));
}

BOOST_AUTO_TEST_CASE(insert_after_fill_empty)
{
  ListT list{ 1, 2, 3 };
  const ListT copied(list);
  ListT::iterator result = list.insertAfter(list.begin(), 0, 5);
  testInvariants(list);
  BOOST_TEST(list == copied);
  BOOST_TEST((result == list.begin()));
}

BOOST_AUTO_TEST_CASE(insert_after_fill)
{
  const ListT expected{ 1, 5, 5, 5, 2, 3 };
  ListT list{ 1, 2, 3 };
  ListT::iterator result = list.insertAfter(list.begin(), 3, 5);
  testInvariants(list);
  BOOST_TEST(list == expected);
  BOOST_TEST((result == ++list.begin()));
}

BOOST_AUTO_TEST_CASE(insert_after_range_empty)
{
  const std::initializer_list< ListT::value_type > init{};
  ListT list{ 1, 2, 3 };
  const ListT copied(list);
  ListT::iterator result = list.insertAfter(list.begin(), init.begin(), init.end());
  testInvariants(list);
  BOOST_TEST(list == copied);
  BOOST_TEST((result == list.begin()));
}

BOOST_AUTO_TEST_CASE(insert_after_range)
{
  const std::initializer_list< ListT::value_type > init{ 5, 5, 5 };
  const ListT expected{ 1, 5, 5, 5, 2, 3 };
  ListT list{ 1, 2, 3 };
  ListT::iterator result = list.insertAfter(list.begin(), init.begin(), init.end());
  testInvariants(list);
  BOOST_TEST(list == expected);
  BOOST_TEST((result == ++list.begin()));
}

BOOST_AUTO_TEST_CASE(insert_after_initializer_list)
{
  const std::initializer_list< ListT::value_type > init{ 5, 5, 5 };
  const ListT expected{ 1, 5, 5, 5, 2, 3 };
  ListT list{ 1, 2, 3 };
  ListT::iterator result = list.insertAfter(list.begin(), init);
  testInvariants(list);
  BOOST_TEST(list == expected);
  BOOST_TEST((result == ++list.begin()));
}

BOOST_AUTO_TEST_CASE(clear)
{
  ListT list{ 1, 2, 3, 4, 5 };
  list.clear();
  testInvariants(list);
  BOOST_TEST(list.empty());
}

BOOST_AUTO_TEST_CASE(swap)
{
  ListT first{ 1, 2, 3, 4, 5 };
  ListT second{ 2, 4, 6, 2 };
  const ListT firstCopy(first);
  const ListT secondCopy(second);
  first.swap(second);
  testInvariants(first);
  testInvariants(second);
  BOOST_TEST(first == secondCopy);
  BOOST_TEST(second == firstCopy);
}

BOOST_AUTO_TEST_SUITE_END();
BOOST_AUTO_TEST_SUITE(operations);

BOOST_AUTO_TEST_CASE(remove_value)
{
  // TODO: Implement remove tests
}

BOOST_AUTO_TEST_CASE(remove_predicate)
{
  // TODO: Implement remove tests
}

BOOST_AUTO_TEST_CASE(reverse)
{
  // TODO: Implement reverse tests
}

BOOST_AUTO_TEST_CASE(unique)
{
  // TODO: Implement unique tests
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

// TODO: Add tests: merge, splice

BOOST_AUTO_TEST_SUITE_END();

// TODO: Test free comparison operators

