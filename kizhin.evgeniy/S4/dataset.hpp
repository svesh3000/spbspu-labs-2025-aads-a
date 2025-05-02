#ifndef SPBSPU_LABS_2025_AADS_A_KIZHIN_EVGENIY_S4_DATASET_HPP
#define SPBSPU_LABS_2025_AADS_A_KIZHIN_EVGENIY_S4_DATASET_HPP

#include <map>
#include <string>

namespace kizhin {
  using Dataset = std::map< int, std::string >;
  using DSContainer = std::map< std::string, Dataset >;
}

#endif

