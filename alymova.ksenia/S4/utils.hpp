#ifndef UTILS_HPP
#define UTILS_HPP
#include <iostream>
#include <map>

namespace alymova
{
	using dict_t = std::map< size_t, std::string, std::less< size_t > >;
  using all_dict_t = std::map< std::string, dict_t, std::less< std::string > >;

	void print(std::ostream& out, const all_dict_t& dicts, const std::string& dataset);
	dict_t complement(all_dict_t& dicts, const std::string& newdataset,
		const std::string& dataset1, const std::string& dataset2);
	dict_t intersect(all_dict_t& dicts, const std::string& newdataset,
		const std::string& dataset1, const std::string& dataset2);
	dict_t unionDict(all_dict_t& dicts, const std::string& newdataset,
		const std::string& dataset1, const std::string& dataset2);
	dict_t readTree(const std::string& s);
}

#endif
