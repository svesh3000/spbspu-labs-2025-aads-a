#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include "hockey.hpp"
namespace brevnov
{
  bool checkPosition(std::string pos);
  void addNewPlayer(std::istream&, std::ostream&, League&);
  void addTeam(std::istream&, std::ostream&, League&);
  void deleteTeam(std::istream&, std::ostream&, League&);
  void endCareer(std::istream&, std::ostream&, League&);
  void updateRating(std::istream&, std::ostream&, League&);
  void buyPlayer(std::istream&, std::ostream&, League&);
  void buyPosition(std::istream&, std::ostream&, League&);
  void buyTeam(std::istream&, std::ostream&, League&);
  void soldPlayer(std::istream&, std::ostream&, League&);
  void soldTeam(std::istream&, std::ostream&, League&);
  void deposit(std::istream&, std::ostream&, League&);
  void viewTeam(std::istream&, std::ostream&, League&);
  void viewPosition(std::istream&, std::ostream&, League&);
  void Transfer(std::istream&, std::ostream&, League&);
  void startTeam(std::istream&, std::ostream&, League&);
  void viewPlayer(std::istream&, std::ostream&, League&);
  void viewTeamPosition(std::istream&, std::ostream&, League&);
  void viewMarket(std::ostream&, League&);
  void viewMarketPosition(std::istream&, std::ostream&, League&);
}
#endif