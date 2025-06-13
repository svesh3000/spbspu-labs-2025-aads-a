#include "commands.hpp"
#include <string>
#include <hash_dyn_array.hpp>

namespace
{
  using tree_of_words = tkach::AvlTree< std::string, tkach::List< std::string > >;
  using tree_of_dict = tkach::AvlTree< std::string, tree_of_words >;

  template< typename T >
  void sortList(List< T >& list_to_sort)
  {
    if (list_to_sort.empty() || list_to_sort.size() == 1)
    {
        return;
    }
    tkach::AvlTree< std::string, bool > tree;
    auto it = list_to_sort.cbegin();
    
    List< T > temp;
  }

  bool findTranslation(const tkach::List< std::string >& list, const std::string& translation)
  {

    if (list.empty())
    {
      return;
    }
    auto it = list.cbegin();
    if (*it == translation)
    {
      return true;
    }
    for (; it != list.cend(); ++it)
    {
      if (*it == translation)
      {
        return true;
      }
    }
    return false;
  }

  void mergeDicts(const tree_of_dict& data, const std::string& newDictName, const tkach::HashDynAry< const tree_of_words* >& source_dicts)
  {
    size_t size = source_dicts.size();
    if (size <= 0)
    {
      throw std::logic_error("");
    }
    tree_of_words temp_dict;
    for (size_t i = 0; i < size; ++i)
    {
      tree_of_words now_dict = *(source_dicts[i]);
      for (auto it = now_dict.begin(); it != now_dict.end(); ++it)
      {
        std::string word = it->first;
        tkach::List< std::string > translations = it->second;
        auto it2 = temp_dict.find(word);
        if (it2 != temp_dict.end())
        {
          tkach::List< std::string >& translations2 = it2->second;
          auto it3 = translations.begin();
          if (!findTranslation(translations2, *it3))
          {
            translations2.pushBack(*it3);
          }
          for (; it3 != now_dict.end(); ++it3)
          {
            if (!findTranslation(translations2, *it3))
            {
              translations2.pushBack(*it3);
            }
          }
        }
        else
        {
          temp_dict.insert({word, translations});
        }
      }
    }
  }
}

namespace tkach
{
  using tree_of_words = AvlTree< std::string, List< std::string > >;
  using tree_of_dict = AvlTree< std::string, tree_of_words >;
  void imprort(std::istream& in, const AvlTree< std::string, AvlTree< std::string, List< std::string > > >& avltree)
  {
    using tree_of_dict = AvlTree< std::string, AvlTree< std::string, List< std::string > > >;
    tree_of_dict temp(avltree);
    std::string name_of_dict = "";
    while (std::getline(in, name_of_dict))
    {
      if (name_of_dict.empty())
      {
        continue;
      }

    }
    if (!in)
    {
      throw std::logic_error("<INVALID IMPORT>");
    }
  }
}