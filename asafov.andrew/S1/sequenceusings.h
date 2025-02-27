#ifndef LISTUSINGS_H
#define LISTUSINGS_H
#include <list>
#include <utility>
#include <string>
using data_t = int;
using data_list_t = std::list<data_t>;
using sequence_t = std::pair<std::string, data_list_t>;
using sequence_list_t = std::list<sequence_t>;
#endif
