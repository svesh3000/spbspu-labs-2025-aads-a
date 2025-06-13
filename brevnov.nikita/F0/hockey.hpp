#ifndef HOCKEY_HPP
#define HOCKEY_HPP
#include <string>
#include "tree.hpp"
namespace brevnov
{
  enum class Position
  {
    LeftForward;
    RightForward;
    CenterForward;
    RightForward;
    LeftForward;
    Goalie;
  }
  struct Player
  {
    Player(std::string name, Team * team, Position pos, size_t raiting, size_t price):
      name_(name),
      team_(team),
      position_(pos),
      raiting_(raiting),
      price_(price)
    {}
    Player(std::string name, Position pos, size_t raiting, size_t price):
      name_(name),
      team_(nullptr)
      position_(pos),
      raiting_(raiting),
      price_(price)
    {}
    std::string name_;
    Team * team_;
    Position position_;
    size_t raiting_;
    size_t price_;
  };
  struct Team
  {
    std::string name_;
    AVLTree< size_t, Player> players_;
    size_t budget_;
  }
}
#endif
