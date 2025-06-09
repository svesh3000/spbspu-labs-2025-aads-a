#include "commands.hpp"
#include <fstream>
#include <stdexcept>
#include <string>
#include <iostream>
#include "list.hpp"

namespace
{
  std::ostream& operator<<(std::ostream& out, const kiselev::List< std::string >& list)
  {
    auto it = list.cbegin();
    out << *it;
    ++it;
    for (; it != list.cend(); ++it)
    {
      out << " " << *it;
    }
    return out;
  }

  kiselev::Dict unionTwoDict(const kiselev::Dict& dict1, const kiselev::Dict& dict2)
  {
    kiselev::Dict res = dict1;
    for (auto it = dict2.cbegin(); it != dict2.cend(); ++it)
    {
      std::string eng = it->first;
      kiselev::List< std::string > translations = it->second;
      auto it2 = res.find(eng);
      if (it2 == res.end())
      {
        res[eng] = translations;
      }
      else
      {
        for (auto transIt = translations.cbegin(); transIt != translations.cend(); ++transIt)
        {
          bool isExists = false;
          for (auto transIt2 = it2->second.cbegin(); transIt2 != it2->second.cend(); ++transIt2)
          {
            if (*transIt2 == *transIt)
            {
              isExists = true;
              break;
            }
          }
          if (!isExists)
          {
            it2->second.pushBack((*transIt));
          }
        }
      }
    }
    return res;
  }
}

void kiselev::doNewDict(std::istream& in, std::ostream& out, Dicts& dicts)
{
  std::string newDict;
  in >> newDict;
  if (dicts.find(newDict) != dicts.end())
  {
    out << "<DICTIONARY ALREADY EXISTS>\n";
    return;
  }
  dicts[newDict];
}

void kiselev::doDeleteDict(std::istream& in, std::ostream& out, Dicts& dicts)
{
  std::string dict;
  in >> dict;
  if (dicts.find(dict) == dicts.end())
  {
    out << "<DICTIONARY NOT FOUND>\n";
    return;
  }
  dicts.erase(dict);
}

void kiselev::doAddElement(std::istream& in, std::ostream& out, Dicts& dicts)
{
  std::string nameDict;
  std::string eng;
  std::string rus;
  in >> nameDict >> eng >> rus;
  auto dictIt = dicts.find(nameDict);
  if (dictIt == dicts.end())
  {
    out << "<DICTIONARY NOT FOUND>\n";
    return;
  }
  Dict dict = dictIt->second;
  auto engIt = dict.find(eng);
  if (engIt == dict.end())
  {
    List< std::string > translations;
    translations.pushBack(rus);
    dict[eng] = translations;
  }
  else
  {
    engIt->second.pushBack(rus);
  }
}

void kiselev::doDeleteElement(std::istream& in, std::ostream& out, Dicts& dicts)
{
  std::string nameDict;
  std::string eng;
  in >> nameDict >> eng;
  auto dictIt = dicts.find(nameDict);
  if (dictIt == dicts.end())
  {
    out << "<DICTIONARY NOT FOUND>\n";
    return;
  }
  Dict dict = dictIt->second;
  auto engIt = dict.find(eng);
  if (engIt == dict.end())
  {
    out << "<ENGWORD NOT FOUND>\n";
    return;
  }
  dict.erase(eng);
}

void kiselev::doListDict(std::ostream& out, const Dicts& dicts)
{
  if (dicts.empty())
  {
    out << "<EMPTY>\n";
    return;
  }
  for (auto it = dicts.cbegin(); it != dicts.cend(); ++it)
  {
    out << it->first << "\n";
  }
}

void kiselev::doPrintDict(std::istream& in, std::ostream& out, const Dicts& dicts)
{
  std::string nameDict;
  in >> nameDict;
  auto dictIt = dicts.find(nameDict);
  if (dictIt == dicts.cend())
  {
    out << "<DICTINARY NOT FOUND>\n";
    return;
  }
  out << nameDict << '\n';
  const Dict dict = dictIt->second;
  for (auto it = dict.cbegin(); it != dict.cend(); ++it)
  {
    out << it->first << " " << it->second << "\n";
  }
}

void kiselev::doTranslateWord(std::istream& in, std::ostream& out, const Dicts& dicts)
{
  std::string nameDict;
  std::string word;
  in >> nameDict >> word;
  auto dictIt = dicts.find(nameDict);
  if (dictIt == dicts.cend())
  {
    out << "<DICTIONARY NOT FOUND>\n";
    return;
  }
  const Dict dict = dictIt->second;
  auto engIt = dict.find(word);
  if (engIt != dict.cend())
  {
    out << engIt->second << "\n";
    return;
  }
  List< std::string > translations;
  for (auto it = dict.cbegin(); it != dict.cend(); ++it)
  {
    for (auto transIt = it->second.cbegin(); transIt != it->second.cend(); ++transIt)
    {
      if (*transIt == word)
      {
        translations.pushBack(it->first);
        break;
      }
    }
  }
  if (!translations.empty())
  {
    out << translations << "\n";
  }
  else
  {
    out << "<WORD NOT FOUND>\n";
  }
}

void kiselev::doUnionDict(std::istream& in, std::ostream& out, Dicts& dicts)
{
  std::string nameNewDict;
  std::string firstDict;
  std::string secondDict;
  in >> nameNewDict >> firstDict >> secondDict;
  if (dicts.find(nameNewDict) != dicts.end())
  {
    out << "<DICTIONARY ALREADY EXISTS>\n";
    return;
  }
  auto first = dicts.find(firstDict);
  auto second = dicts.find(secondDict);
  if (first == dicts.end() || second == dicts.end())
  {
    out << "<DICTIONARY NOT FOUND>\n";
    return;
  }
  Dict res = unionTwoDict(first->second, second->second);
  std::string nextDict;
  while (in >> nextDict)
  {
    auto it = dicts.find(nextDict);
    if (it == dicts.end())
    {
      out << "<DICTIONARY NOT FOUND>\n";
      return;
    }
    res = unionTwoDict(res, it->second);
    if (in.get() == '\n')
    {
      break;
    }
  }
  dicts[nameNewDict] = res;
}

void kiselev::doSaveDict(std::istream& in, std::ostream& out, const Dicts& dicts)
{
  std::string fileName;
  std::string dictName;
  in >> dictName >> fileName;
  auto dictIt = dicts.find(dictName);
  if (dictIt == dicts.cend())
  {
    out << "<DICTIONARY NOT FOUND>\n";
    return;
  }
  std::ofstream file(fileName);
  if (!file)
  {
    out << "<FILE ERROR>\n";
    return;
  }
  file << dictName << "\n";
  Dict dict = dictIt->second;
  for (auto it = dict.cbegin(); it != dict.cend(); ++it)
  {
    file << it->first << " " << it->second << "\n";
  }
  file << "\n";
}

void kiselev::doCountWord(std::istream& in, std::ostream& out, const Dicts& dicts)
{
  std::string dictName;
  in >> dictName;
  auto it = dicts.find(dictName);
  if (it == dicts.cend())
  {
    out << "<DICTIONARY NOT FOUND>\n";
    return;
  }
  out << it->second.size() << "\n";
}
