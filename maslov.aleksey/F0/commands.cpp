#include "commands.hpp"
#include <iostream>
#include <fstream>
#include <iomanip>

void maslov::createDictionary(std::istream & in, Dicts & dicts)
{}

void maslov::showDictionary(std::ostream & out, const Dicts & dicts)
{}

void maslov::load(std::istream & in, Dicts & dicts)
{
  std::string fileName, dictName;
  in >> fileName >> dictName;
  std::ifstream file(fileName);
  if (!file.is_open())
  {
    throw std::runtime_error("<INVALID COMMAND>");
  }
  auto it = dicts.find(dictName);
  if (it == dicts.end())
  {
    throw std::runtime_error("<INVALID COMMAND>");
  }
  loadFromFile(file, dictName, dicts);
}

void maslov::unionDictionary(std::istream & in, Dicts & dicts)
{}

void maslov::intersectDictionary(std::istream & in, Dicts & dicts)
{}

void maslov::copyDictionary(std::istream & in, Dicts & dicts)
{}

void maslov::addWord(std::istream & in, Dicts & dicts)
{}

void maslov::printSize(std::istream & in, std::ostream & out, const Dicts & dicts)
{}

void maslov::cleanWord(std::istream & in, Dicts & dicts)
{}

void maslov::cleanDictionary(std::istream & in, Dicts & dicts)
{}

void maslov::printTop(std::istream & in, std::ostream & out, const Dicts & dicts)
{}

void maslov::printRare(std::istream & in, std::ostream & out, const Dicts & dicts)
{}

void maslov::printFrequency(std::istream & in, std::ostream & out, const Dicts & dicts)
{}

void maslov::createWordRange(std::istream & in, Dicts & dicts)
{}

void maslov::printHelp(std::ostream & out)
{
  out << std::left;
  constexpr size_t cmdWidth = 50;
  constexpr size_t numWidth = 4;
  out << std::setw(numWidth) << "1." << std::setw(cmdWidth);
  out << "createdictionary <dict_name>" << "create a new dictionary\n";

  out << std::setw(numWidth) << "2." << std::setw(cmdWidth);
  out << "showdictionary" << "shows all dictionary names\n";

  out << std::setw(numWidth) << "3." << std::setw(cmdWidth);
  out << "load <dict_name> <file>" << "upload text from a file to the dictionary\n";

  out << std::setw(numWidth) << "4." << std::setw(cmdWidth);
  out << "union <result> <dict1> <dict2>" << "creates a new dictionary that combines the other two\n";

  out << std::setw(numWidth) << "5." << std::setw(cmdWidth);
  out << "intersect <result> <dict1> <dict2>" << "creates a new dictionary that intersects the other two\n";

  out << std::setw(numWidth) << "6." << std::setw(cmdWidth);
  out << "copy <result> <dict>" << "copies dictionary data\n";

  out << std::setw(numWidth) << "7." << std::setw(cmdWidth);
  out << "addword <dict_name> <word> <frequency>" << "adding a word to the dictionary\n";

  out << std::setw(numWidth) << "8." << std::setw(cmdWidth);
  out << "size <dict_name>" << "print the number of words in the dictionary\n";

  out << std::setw(numWidth) << "9." << std::setw(cmdWidth);
  out << "cleanword <dict_name> <word>" << "deleting a word from the dictionary\n";

  out << std::setw(numWidth) << "10." << std::setw(cmdWidth);
  out << "cleandictionary <dict_name>" << "deleting all words from the dictionary\n";

  out << std::setw(numWidth) << "11." << std::setw(cmdWidth);
  out << "top <dict_name> <number>" << "print of the most frequently used words\n";

  out << std::setw(numWidth) << "12." << std::setw(cmdWidth);
  out << "rare <dict_name> <number>" << "print of the least frequently used words\n";

  out << std::setw(numWidth) << "13." << std::setw(cmdWidth);
  out << "frequency <dict_name> <word>" << "print of the word frequency\n";

  out << std::setw(numWidth) << "14." << std::setw(cmdWidth);
  out << "wordrange <result> <dict_name> <freq1> <freq2>";
  out << "creates a dictionary of words whose frequencies are in the range\n";
}

void maslov::loadFromFile(std::ifstream & file, const std::string & name, Dicts & dicts)
{}
