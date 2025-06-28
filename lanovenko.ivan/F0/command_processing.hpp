#ifndef COMMAND_PROCESSING_HPP
#define COMMAND_PROCESSING_HPP

#include <tree.hpp>
#include <cmath>
#include <vector>
#include <algorithm>
#include <functional>
#include "pantsir.hpp"
#include "target.hpp"

namespace lanovenko
{
  using targets = Tree< std::string, Target, std::less< std::string > >;
  using targets_sets = Tree< std::string, targets, std::less< std::string > >;
  using pantsir_s = Tree< std::string, Pantsir, std::less< std::string > >;
  using commands_t = Tree< std::string, std::function< void() >, std::less< std::string > >;
  void create_target(std::istream& in, targets& trg);
  void delete_target(std::istream& in, targets& trg, targets_sets& trgs);
  void engage_max_targets(std::istream& in, std::ostream& out, targets& trg, targets_sets& trgs, pantsir_s& ps);
  void engage_balanced(std::istream& in, std::ostream& out, targets& trg, targets_sets& trgs, pantsir_s& ps);
  void engage_top_threats(std::istream& in, std::ostream& out, targets& trg, targets_sets& trgs, pantsir_s& ps);
  void engage_manual(std::istream& in, std::ostream& out, targets& trs, targets_sets& trgs, pantsir_s& ps);
  void solve_threat(std::istream& in, std::ostream& out, targets& trs, targets_sets& trgs, pantsir_s& ps);
  void target_list(std::istream& in, std::ostream& out, const targets_sets& trgs);
  void system_status(std::istream& in, std::ostream& out, const pantsir_s& ps);
  void create_target_set(std::istream& in, targets_sets& trgs);
  void add_target_to_set(std::istream& in, targets_sets& trgs, targets& trg);
  void all_targets(std::ostream& out, const targets& trs);
  void help(std::ostream& out);
}

#endif