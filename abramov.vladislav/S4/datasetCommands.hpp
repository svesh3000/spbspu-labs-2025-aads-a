#ifndef DATASETCOMMANDS_HPP
#define DATASETCOMMANDS_HPP
#include <map>
#include <string>
#include <fstream>

namespace abramov
{
  std::map< std::string, std::map< int, std::string > > getDataSets(std::ifstream &in);
  void printDataSet(const std::string &s, const std::map< std::string, std::map< int, std::string > > &dicts);
  std::map< int, std::string > complementDataSets(const std::string &s1, const std::string &s2, const std::map< std::string, std::map< int, std::string > > &dicts);
  std::map< int, std::string > intersectDataSets(const std::string &s1, const std::string &s2, const std::map< std::string, std::map< int, std::string > > &dicts);
  std::map< int, std::string > unionDataSets(const std::string &s1, const std::string &s2, const std::map< std::string, std::map< int, std::string > > &dicts);
  void doCommand(const std::string &s, std::istream &in, std::map< std::string, std::map< int, std::string > > &dicts);
}
#endif
