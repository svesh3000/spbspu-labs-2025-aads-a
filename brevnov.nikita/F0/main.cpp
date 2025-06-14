#include <fstream>
#include <functional>
#include <iostream>
#include <istream>
#include <string>
#include <utility>
#include <limits>
#include "commands.hpp"
namespace
{

  void input(std::istream& in, brevnov::League league)
  {
    std::string teamName;
    while (in >> teamName)
    {
      size_t budget = 0;
      in >> budget;
      if (budget > 0)
      {
        std::pair< std::string, brevnov::Team > pair(teamName, brevnov::Team(budget));
        league.teams_.insert(pair);
        if (in.get() == '\n')
        {
          break;
        }
      }
    }
    while (in >> teamName)
    {
      std::string playerName, position;
      size_t raiting, price;
      in >> playerName >> position >> raiting >> price;
      if (raiting > 0 && price > 0 && checkPosition(position))
      {
        auto clubFind = league.teams_.find(teamName);
        if (clubFind)
        {
          brevnov::Team club(*clubFind.second);
          std::pair< std::string, brevnov::Player > pair(playerName, brevnov::Player(club, position, raiting, price));
          club.players_.insert(pair);
        }
        else
        {
          std::pair< std::string, brevnov::Player > pair(playerName, brevnov::Player(position, raiting, price));
          league.fa_.insert(pair);
        }
      }
    }
  }
}

int main(int argc, char** argv)
{
  using namespace brevnov;
  League league;
  {
    std::ifstream file(argv[1]);
    if (!file)
    {
      std::cout << "FILE ERROR\n";
      return 1;
    }
    input(file, league);
    file.close();
  }
  AVLTree< std::string, std::function< void() > > commands;
  using namespace std::placeholders;
  commands.insert(std::make_pair("newdict", std::bind(doNewDict, std::ref(std::cin), std::ref(std::cout), std::ref(leaugue))));
  commands.insert(std::make_pair("deletedict", std::bind(doDeleteDict, std::ref(std::cin), std::ref(std::cout), std::ref(leaugue))));
  commands.insert(std::make_pair("addelement", std::bind(doAddElement, std::ref(std::cin), std::ref(std::cout), std::ref(leaugue))));
  commands.insert(std::make_pair("deleteelement", std::bind(doDeleteElement, std::ref(std::cin), std::ref(std::cout), std::ref(leaugue))));
  commands.insert(std::make_pair("listdict", std::bind(doListDict, std::ref(std::cout), std::cref(leaugue))));
  commands.insert(std::make_pair("printdict", std::bind(doPrintDict, std::ref(std::cin), std::ref(std::cout), std::cref(leaugue))));
  commands.insert(std::make_pair("translateword", std::bind(doTranslateWord, std::ref(std::cin), std::ref(std::cout), std::cref(leaugue))));
  commands.insert(std::make_pair("uniondict", std::bind(doUnionDict, std::ref(std::cin), std::ref(std::cout), std::ref(leaugue))));
  commands.insert(std::make_pair("savedict", std::bind(doSaveDict, std::ref(std::cin), std::ref(std::cout), std::cref(leaugue))));
  commands.insert(std::make_pair("countdict", std::bind(doCountWord, std::ref(std::cin), std::ref(std::cout), std::cref(leaugue))));
  commands.insert(std::make_pair("searchletter", std::bind(doSearchLetter, std::ref(std::cin), std::ref(std::cout), std::cref(leaugue))));
  commands.insert(std::make_pair("loaddict", std::bind(doLoadDict, std::ref(std::cin), std::ref(std::cout), std::ref(leaugue))));
  commands.insert(std::make_pair("cleardict", std::bind(doClearDict, std::ref(std::cin), std::ref(std::cout), std::ref(leaugue))));
  commands.insert(std::make_pair("intersectdict", std::bind(doIntersectDict, std::ref(std::cin), std::ref(std::cout), std::ref(leaugue))));
  commands.insert(std::make_pair("complementdict", std::bind(doComplementDict, std::ref(std::cin), std::ref(std::cout), std::ref(leaugue))));
  std::string command;
  while (std::cin >> command)
  {
    try
    {
      commands.at(command)();
    }
    catch (...)
    {
      std::cout << "<INVALID COMMAND>\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  return 1;
}
