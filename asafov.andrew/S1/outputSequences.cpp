#include "sequencefunctions.h"
#include <limits>

namespace
{
  struct IteratorPair
  {
    asafov::data_list_t::ConstIterator current;
    asafov::data_list_t::ConstIterator end;
  };

  bool allItersEnds(const asafov::ForwardList<IteratorPair>& iters)
  {
    for (const auto& pair : iters)
    {
      if (pair.current != pair.end)
      {
        return false;
      }
    }
    return true;
  }
}

void asafov::outputSequences(sequence_list_t& sequences, std::ostream& out)
{
  if (sequences.cbegin()->first == "")
  {
    out << "0\n";
    return;
  }

  if (sequences.cbegin()->second.empty())
  {
    out << sequences.cbegin()->first << "\n0\n";
    return;
  }

  ForwardList<IteratorPair> iterators;

  auto iter = sequences.cbegin();
  out << iter->first;

  IteratorPair firstPair{ iter->second.cbegin(), iter->second.cend() };
  iterators.push_back(firstPair);

  ++iter;

  for (; iter != sequences.cend(); ++iter)
  {
    out << ' ' << iter->first;
    IteratorPair pair{ iter->second.cbegin(), iter->second.cend() };
    iterators.push_back(pair);
  }

  if (!sequences.empty())
  {
    out << '\n';
  }

  data_list_t sums;
  bool isAllItersEnds = true;

  while (!allItersEnds(iterators))
  {
    data_t sum = 0;
    bool firstOutput = true;

    for (auto& pair : iterators)
    {
      if (pair.current != pair.end)
      {
        if (sum > std::numeric_limits<data_t>::max() - *pair.current)
        {
          isAllItersEnds = false;
        }
        else
        {
          sum += *pair.current;
        }

        if (firstOutput)
        {
          out << *pair.current;
          firstOutput = false;
        }
        else
        {
          out << ' ' << *pair.current;
        }

        ++pair.current;
      }
    }

    out << '\n';
    sums.push_back(sum);
  }

  if (!isAllItersEnds)
  {
    sums.clear();
    throw std::overflow_error("overflow!");
  }

  auto it = sums.cbegin();
  out << *it;
  ++it;

  for (; it != sums.cend(); ++it)
  {
    out << ' ' << *it;
  }

  out << '\n';
}
