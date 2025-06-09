#include "commands.hpp"
#include <istream>
#include <ostream>
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
