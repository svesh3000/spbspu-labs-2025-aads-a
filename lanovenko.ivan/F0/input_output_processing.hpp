#ifndef INPUT_OUTPUT_PROCESSING_HPP
#define INPUT_OUTPUT_PROCESSING_HPP

#include <tree.hpp>
#include "pantsir.hpp"
#include "target.hpp"

namespace lanovenko
{
  void input_pantsir_status(std::istream& in, Tree< std::string, Pantsir, std::less< std::string > >& pantsir_status_sets);
  void input_targets(std::istream& in, Tree< std::string, Target, std::less< std::string > >& rhs);
}

#endif