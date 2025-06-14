#include "commands.hpp"
#include <string>
#include <dynamic_array.hpp>
#include <fstream>
namespace
{
  using tree_of_words = tkach::AvlTree< std::string, tkach::List< std::string > >;
  using tree_of_dict = tkach::AvlTree< std::string, tree_of_words >;

  bool findTranslation(const tkach::List< std::string >& list, const std::string& translation)
  {

    if (list.empty())
    {
      return false;
    }
    for (auto it = list.cbegin(); it != list.cend(); ++it)
    {
      if (*it == translation)
      {
        return true;
      }
    }
    return false;
  }


  tkach::List< std::string > mergeTranslations(const tkach::List< std::string >& list1, const tkach::List< std::string >& list2)
  {
    tkach::List< std::string > translations;
    for (auto it = list1.cbegin(); it != list1.cend(); ++it)
    {
      if (!findTranslation(translations, *it))
      {
        translations.pushBack(*it);
      }
    }
    if (std::addressof(list1) != std::addressof(list2))
    {
      for (auto it = list2.cbegin(); it != list2.cend(); ++it)
      {
        if (!findTranslation(translations, *it))
        {
          translations.pushBack(*it);
        }
      }
    }
    return translations;
  }
  
  tkach::AvlTree< std::string, tkach::List< std::string > > mergeDicts(const tkach::List< const tree_of_words* >& source_dicts)
  {
    size_t size = source_dicts.size();
    if (size == 0)
    {
      throw std::logic_error("EMPTY");
    }
    tree_of_words temp_dict;
    for (auto it = source_dicts.cbegin(); it != source_dicts.cend(); ++it)
    {
      const tree_of_words& now_dict = *(*it);
      for (auto it = now_dict.cbegin(); it != now_dict.cend(); ++it)
      {
        std::string word = it->first;
        tkach::List< std::string > translations = it->second;
        auto it2 = temp_dict.find(word);
        if (it2 != temp_dict.end())
        {
          it2->second = mergeTranslations(it2->second, translations);
        }
        else
        {
          temp_dict[word] = mergeTranslations(translations, translations);
        }
      }
    }
    return temp_dict;
  }
}

namespace tkach
{
  void import(std::istream& in, AvlTree< std::string, AvlTree< std::string, List< std::string > > >& avltree)
  {
    using tree_of_dict = AvlTree< std::string, AvlTree< std::string, List< std::string > > >;
    tree_of_dict temp(avltree);
    std::string main_name_dict = "", file_name = "";
    in >> file_name;
    if (in.peek() != '\n')
    {
      in >> main_name_dict;
    }
    std::fstream in2(file_name);
    if (!in2.is_open())
    {
      throw std::logic_error("<INVALID IMPORT2>");
    }
    std::string name_of_dict = "";
    while (in2 >> name_of_dict)
    {
      if (name_of_dict.empty())
      {
        continue;
      }
      tree_of_words temp_dict;
      std::string eng_word;
      while (in2 >> eng_word)
      {
        List< std::string > translations;
        std::string translation;
        while (in2 >> translation)
        {
          translations.pushBack(translation);
          if (in2.peek() == '\n')
          {
            in2.get();
            break;
          }
        }
        auto it = temp_dict.find(eng_word);
        if (it == temp_dict.end())
        {
          temp_dict[eng_word] = mergeTranslations(translations, translations);
        }
        else
        {
          List< std::string > unique = mergeTranslations(translations, temp_dict[eng_word]);
          temp_dict[eng_word] = unique; 
        }
        if (in2.peek() == '\n')
        {
          in2.get();
          break;
        }
      }
      auto it = temp.find(name_of_dict);
      if (it == temp.end())
      {
        temp[name_of_dict] = temp_dict;
      }
      else
      {
        AvlTree< std::string, List< std::string > > merged = mergeDicts({&temp_dict, &temp[name_of_dict]});
        temp[name_of_dict] = merged;
      }
    }
    if (!in2.eof())
    {
      throw std::logic_error("<INVALID IMPORT>");
    }
    if (main_name_dict != "")
    {
      auto it = temp.find(main_name_dict);
      if (it == temp.end())
      {
        return;
      }
      avltree[main_name_dict] = temp[main_name_dict];
    }
    else
    {
      avltree = std::move(temp);
    }
  }

  void addWord(std::istream& in, AvlTree< std::string, AvlTree< std::string, List< std::string > > >& avltree)
  {
    std::string dict_name;
    std::string eng_word;
    size_t num_translations = 0;
    if (!(in >> dict_name) || dict_name.empty())
    {
      throw std::logic_error("<INVALID COMMAND>");
    }
    if (!(in >> eng_word) || eng_word.empty())
    {
      throw std::logic_error("<INVALID COMMAND>");
    }
    if (!(in >> num_translations))
    {
      throw std::logic_error("<INVALID COMMAND>");
    }
    if (num_translations <= 0)
    {
      throw std::logic_error("<INVALID NUMBER>");
    }
    List< std::string > translations;
    std::string translation;
    for (size_t i = 0; i < num_translations; ++i)
    {
      if (!(in >> translation))
      {
        throw std::logic_error("<INVALID ARGUMENTS>");
      }
      translations.pushBack(translation);
    }
    auto it = avltree.find(dict_name);
    if (it == avltree.end())
    {
      tree_of_words new_dict;
      new_dict[eng_word] = translations;
      avltree[dict_name] = new_dict;
    }
    else
    {
      tree_of_words& current_dict = it->second;
      auto it2 = current_dict.find(eng_word);
      if (it2 == current_dict.end())
      {
        current_dict[eng_word] = mergeTranslations(translations, translations);
      }
      else
      {
        it2->second = mergeTranslations(translations, it2->second);
      }
    }
  }

  void printAll(std::ostream& out, AvlTree< std::string, AvlTree< std::string, List< std::string > > >& data)
  {
    for (auto it = data.cbegin(); it != data.cend(); ++it)
    {
      out << it->first << "\n";
      for (auto it2 = it->second.cbegin(); it2 != it->second.cend(); ++it2)
      {
        out << it2->first;
        for (auto it3 = it2->second.cbegin(); it3 != it2->second.cend(); it3++)
        {
          out << " " << *it3;
        }
        out << "\n";
      }
    }
  }
}