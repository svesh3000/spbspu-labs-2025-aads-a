#include "commands.hpp"
#include <string>
#include <dynamic_array.hpp>
#include <fstream>
#include <hash_dyn_array.hpp>
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

  tkach::List< std::string > getCommonElements(const tkach::List< std::string >& list1, const tkach::List< std::string >& list2)
  {
    tkach::List< std::string > common_list;
    for (auto it = list1.cbegin(); it != list1.cend(); ++it)
    {
      if (findTranslation(list2, *it) && !findTranslation(common_list, *it))
      {
        common_list.pushBack(*it);
      }
    }
    return common_list;
  }

  void writeDictToFile(std::ostream& out, const std::string& dict_name, const tree_of_words& dict)
  {
    out << dict_name << "\n";
    for (auto it = dict.cbegin(); it != dict.cend(); ++it)
    {
      out << it->first;
      for (auto it2 = it->second.cbegin(); it2 != it->second.cend(); ++it2)
      {
        out << " " << *it2;
      }
      out << "\n";
    }
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

  void exportDictionaries(std::istream& in, const tree_of_dict& avltree, std::ios_base::openmode mode)
  {
    std::string filename;
    size_t count_of_dicts = 0;
    if (!(in >> filename) || filename.empty())
    {
      throw std::logic_error("<INVALID COMMAND>");
    }
    if (!(in >> count_of_dicts))
    {
      throw std::logic_error("<INVALID COMMAND>");
    }
    std::ofstream outFile(filename, mode);
    if (!outFile.is_open())
    {
      throw std::logic_error("<EXPORT FAILED>");
    }
    if (count_of_dicts == 0)
    {
      if (avltree.empty())
      {
        return;
      }
      for (auto it = avltree.cbegin(); it != avltree.cend(); ++it)
      {
        writeDictToFile(outFile, it->first, it->second);
      }
    }
    else
    {
      std::string current_dict_name;
      for (size_t i = 0; i < count_of_dicts; ++i)
      {
        if (!(in >> current_dict_name) || current_dict_name.empty())
        {
          throw std::logic_error("<INVALID COMMAND>");
        }
        auto it = avltree.find(current_dict_name);
        if (it == avltree.cend())
        {
          throw std::logic_error("<INVALID DICTIONARY>");
        }
        writeDictToFile(outFile, it->first, it->second);
      }
    }
  }
}

namespace tkach
{
  void import(std::istream& in, AvlTree< std::string, AvlTree< std::string, List< std::string > > >& avltree)
  {
    using tree_of_dict = AvlTree< std::string, AvlTree< std::string, List< std::string > > >;
    tree_of_dict temp(avltree);
    std::string file_name = "";
    int count_of_dict = 0;
    HashDynAry< std::string > main_name_dict = (count_of_dict);
    in >> file_name >> count_of_dict;
    if (count_of_dict < 0)
    {
      throw std::logic_error("<INVALID IMPORT>");
    }
    for (size_t i = 0; i < static_cast< size_t >(count_of_dict); ++i)
    {
      main_name_dict[i];
    }
    std::fstream in2(file_name);
    if (!in2.is_open())
    {
      throw std::logic_error("<INVALID IMPORT>");
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
    if (count_of_dict != 0)
    {
      for (size_t i = 0; i < static_cast< size_t >(count_of_dict); ++i)
      {
        auto it = temp.find(main_name_dict[i]);
        if (it == temp.end())
        {
          throw std::logic_error("<INVALID IMPORT>");
        }
        avltree[main_name_dict[i]] = temp[main_name_dict[i]];
      }
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

  void printcommontranslations(std::istream& in, std::ostream& out, const AvlTree< std::string, AvlTree< std::string, List< std::string > > >& avltree)
  {
    std::string dict_name;
    size_t number_of_words = 0;
    if (!(in >> dict_name) || dict_name.empty())
    {
      throw std::logic_error("<INVALID COMMAND>");
    }
    if (!(in >> number_of_words))
    {
      throw std::logic_error("<INVALID COMMAND>");
    }
    if (number_of_words <= 0)
    {
      throw std::logic_error("<INVALID NUMBER>");
    }
    auto it = avltree.find(dict_name);
    if (it == avltree.cend())
    {
      throw std::logic_error("<INVALID DICTIONARY>");
    }
    tkach::List< std::string > common_translations;
    for (size_t i = 0; i < number_of_words; ++i)
    {
      std::string word;
      if (!(in >> word) || word.empty())
      {
        throw std::logic_error("<INVALID COMMAND>");
      }
      auto word_it = it->second.find(word);
      if (word_it == it->second.cend())
      {
        throw std::logic_error("<INVALID WORD>");
      }
      if (common_translations.empty())
      {
        common_translations = word_it->second;
      }
      else
      {
        common_translations = getCommonElements(common_translations, word_it->second);
      }
    }
    if (common_translations.empty())
    {
      out << "\n";
    }
    else
    {
      out << *common_translations.cbegin();
      for (auto it3 = ++common_translations.cbegin(); it3 != common_translations.cend(); ++it3)
      {
        out << " " << *it3;
      }
      out << "\n";
    }
  }

  void doExportOverwrite(std::istream& in, const AvlTree< std::string, AvlTree< std::string, List< std::string > > >& avltree)
  {
    exportDictionaries(in, avltree, std::ios_base::out);
  }

  void doExportInEnd(std::istream& in, const AvlTree< std::string, AvlTree< std::string, List< std::string > > >& avltree)
  {
    exportDictionaries(in, avltree, std::ios_base::app);
  }
  void printAll(std::ostream& out, const AvlTree< std::string, AvlTree< std::string, List< std::string > > >& data)
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

  void removeWord(std::istream& in, AvlTree< std::string, AvlTree< std::string, List< std::string > > >& avltree)
  {
    std::string dict_name;
    std::string eng_word;
    if (!(in >> dict_name) || dict_name.empty())
    {
      throw std::logic_error("<INVALID COMMAND>");
    }
    if (!(in >> eng_word) || eng_word.empty())
    {
      throw std::logic_error("<INVALID COMMAND>");
    }
    auto it = avltree.find(dict_name);
    if (it == avltree.end())
    {
      throw std::logic_error("<INVALID DICTIONARY>");
    }
    bool removed = (it->second).erase(eng_word);
    if (!removed)
    {
      throw std::logic_error("<INVALID WORD>");
    }
  }

  void addtranslation(std::istream& in, AvlTree< std::string, AvlTree< std::string, List< std::string > > >& avltree)
  {
    std::string dict_name = "";
    std::string eng_word;
    std::string translation;
    size_t dict_name_specified = 2;
    if (!(in >> dict_name_specified) && dict_name_specified != 0 && dict_name_specified != 1)
    {
      throw std::logic_error("<INVALID COMMAND>");
    }
    if (dict_name_specified)
    {
      if (!(in >> dict_name) || dict_name.empty())
      {
        throw std::logic_error("<INVALID COMMAND>");
      }
    }
    if (!(in >> eng_word) || eng_word.empty())
    {
      throw std::logic_error("<INVALID COMMAND>");
    }
    if (!(in >> translation) || translation.empty())
    {
      throw std::logic_error("<INVALID COMMAND>");
    }
    if (dict_name_specified)
    {
      auto it = avltree.find(dict_name);
      if (it == avltree.end())
      {
        throw std::logic_error("<INVALID DICTIONARY>");
      }
      auto it2 = it->second.find(eng_word);
      if (it2 == it->second.end())
      {
        throw std::logic_error("<INVALID WORD>");
      }
      if (!findTranslation(it2->second, translation))
      {
        it2->second.pushBack(translation);
      }
    }
    else
    {
      for (auto it = avltree.begin(); it != avltree.end(); ++it)
      {
        auto it2 = it->second.find(eng_word);
        if (it2 != it->second.end())
        {
          if (!findTranslation(it2->second, translation))
          {
            it2->second.pushBack(translation);
          }
        }
      }
    }
  }

  void removetranslation(std::istream& in, AvlTree< std::string, AvlTree< std::string, List< std::string > > >& avltree)
  {
    std::string dict_name = "";
    std::string eng_word;
    std::string translation;
    size_t dict_name_specified = 2;
    if (!(in >> dict_name_specified) && dict_name_specified != 0 && dict_name_specified != 1)
    {
      throw std::logic_error("<INVALID COMMAND>");
    }
    if (dict_name_specified)
    {
      if (!(in >> dict_name) || dict_name.empty())
      {
        throw std::logic_error("<INVALID COMMAND>");
      }
    }
    if (!(in >> eng_word) || eng_word.empty())
    {
      throw std::logic_error("<INVALID COMMAND>");
    }
    if (!(in >> translation) || translation.empty())
    {
      throw std::logic_error("<INVALID COMMAND>");
    }
    if (dict_name_specified)
    {
      auto it = avltree.find(dict_name);
      if (it == avltree.end())
      {
        throw std::logic_error("<INVALID DICTIONARY>");
      }
      auto it2 = it->second.find(eng_word);
      if (it2 == it->second.end())
      {
        throw std::logic_error("<INVALID WORD OR TRANSLATION>");
      }
      if (findTranslation(it2->second, translation))
      {
        it2->second.remove(translation);
      }
      else
      {
        throw std::logic_error("<INVALID WORD OR TRANSLATION>");
      }
    }
    else
    {
      for (auto it = avltree.begin(); it != avltree.end(); ++it)
      {
        auto it2 = it->second.find(eng_word);
        if (it2 != it->second.end())
        {
          if (!findTranslation(it2->second, translation))
          {
            it2->second.remove(translation);
          }
        }
      }
    }
  }

  void clear(std::istream& in, AvlTree< std::string, AvlTree< std::string, List< std::string > > >& avltree)
  {
    std::string dict_name;
    if (!(in >> dict_name) || dict_name.empty())
    {
      throw std::logic_error("<INVALID COMMAND>");
    }
    auto it = avltree.find(dict_name);
    if (it == avltree.end())
    {
      throw std::logic_error("<INVALID DICTIONARY>");
    }
    it->second.clear();
  }

}
