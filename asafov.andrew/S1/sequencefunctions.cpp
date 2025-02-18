#include "sequencefunctions.h"
#include <algorithm>

static bool allItersEnds(data_list_t::iterator* begins, data_list_t::iterator* ends, size_t size)
{
	data_list_t::iterator* tempbegins = begins;
	data_list_t::iterator* tempends = ends;
	
	bool allItersEnds = true;
	for (size_t i = 0; i < size; i++)
	{
		if(tempbegins[i]!=tempends[i])
		{
			allItersEnds = false;
		}
	}
	return allItersEnds;
}

sequence_list_t asafov::getSequences(std::istream& in)
{
	sequence_list_t data;
	do
	{
		std::string name;
		data_list_t list;
		data_t temp = 0;
		in >> name;
		while (!in.fail())
		{
			in >> temp;
			if (in.fail())
			{
				break;
			}
			list.push_back(temp);
		}
		if (!in.eof())
		{
			in.clear();
		}
		sequence_t pair = make_pair(name, list);
		data.push_back(pair);
	} while (!in.eof());
	return data;
}

void asafov::outputSequences(sequence_list_t sequences, std::ostream& out)
{
	data_list_t::iterator* begins = new data_list_t::iterator[sequences.size()];
	data_list_t::iterator* ends = new data_list_t::iterator[sequences.size()];
	sequence_list_t::iterator seqiter = sequences.begin();

	size_t size = 0;
	for (sequence_list_t::iterator iter = sequences.begin(); iter != sequences.end(); ++iter, ++size)
	{
		std::cout << iter->first << ' ';
		begins[size] = iter->second.begin();
		ends[size] = iter->second.end();
	}
	std::cout << '\n';
	seqiter = sequences.begin();
	
	//data_t* sums = new data_t[size*size];
	data_list_t sums;
	data_list_t::iterator sumsit = sums.begin();
	while (!allItersEnds(begins, ends, sequences.size()))
	{
		data_t sum = 0;
		for (size_t i = 0; i < sequences.size(); i++)
		{
			if (begins[i] != ends[i])
			{
				sum += *begins[i];
				std::cout << *begins[i] << ' ';
				++begins[i];
			}
		}
		sums.push_back(sum);
		std::cout << '\n';
	}
	for (size_t n : sums) std::cout << n << ' ';
	std::cout << '\n';

	delete[] begins;
	delete[] ends;
}
