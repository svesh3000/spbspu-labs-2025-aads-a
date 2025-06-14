#ifndef HOCKEY_HPP
#define HOCKEY_HPP
#include <string>
#include "tree.hpp"
namespace brevnov
{
  enum class Position
  {
    LF;
    RF;
    CF;
    RB;
    LB;
    G;
  }
  struct Player
  {
    Player(Team * team, std::string pos, size_t raiting, size_t price):
      team_(team),
      position_(Position::CF),
      raiting_(raiting),
      price_(price)
    {
      switch (pos)
      [
        case "CF": position_ = Position::CF;
        case "RF": position_ = Position::RF;
        case "LF": position_ = Position::LF;
        case "RB": position_ = Position::RB;
        case "LB": position_ = Position::LB;
        case "G": position_ = Position::G;
      ]
    }

    Player(std::string pos, size_t raiting, size_t price):
      team_(nullptr),
      position_(Position::CF),
      raiting_(raiting),
      price_(price)
    {
      switch (pos)
      [
        case "CF": position_ = Position::CF;
        case "RF": position_ = Position::RF;
        case "LF": position_ = Position::LF;
        case "RB": position_ = Position::RB;
        case "LB": position_ = Position::LB;
        case "G": position_ = Position::G;
      ]
    }
    Team * team_;
    Position position_;
    size_t raiting_;
    size_t price_;
  };
  struct Team
  {
    Team(size_t budget):
      players_(AVLTree< size_t, Player >())
      budget_(budget)
    {}
    AVLTree< std::string, Player > players_;
    size_t budget_;
  };
  struct League
  {
    AVLTree< std::string, Player > fa_;
    AVLTRee< std::string, Team > teams_;
  };
}
#endif
