#ifndef PROCESSINGDICTIONARY_HPP
#define PROCESSINGDICTIONARY_HPP
#include <ostream>
#include <map>
#include <string>
#include <list>

namespace zakirov
{
  template < class K, class T >
  std::map< K, T > find_d(std::string name, const std::list< std::pair< std::string, std::map< K, T > > > & dictionary);
  template < class K, class T >
  void execute_command(std::istream & in, std::ostream & out, std::list< std::pair< std::string, std::map< K, T > > > & dictionary);
  template < class K, class T >
  void print_d(std::ostream & out, std::string name, const std::map< K, T > & dictionary);
  template < class K, class T >
  void complement_d(std::map< K, T > & result_d, const std::map< K, T > & first_d, const std::map< K, T > & second_d);
  template < class K, class T >
  void intersect_d(std::map< K, T > & result_d, const std::map< K, T > & first_d, const std::map< K, T > & second_d);
  template < class K, class T >
  void union_d(std::map< K, T > & result_d, const std::map< K, T > & first_d, const std::map< K, T > & second_d);

  template < class K, class T >
  std::map< K, T > find_d(std::string name, const std::list< std::pair< std::string, std::map< K, T > > > & dictionary)
  {
    for (auto it = dictionary.cbegin(); it != dictionary.cend(); ++it)
    {
      if (name == it->first)
      {
        return it->second;
      }
    }

    throw std::logic_error("<DICTIONARY NOT FOUND>");
  }

  template < class K, class T >
  void execute_command(std::istream & in, std::ostream & out, std::list< std::pair< std::string, std::map< K, T > > > & dictionary)
  {
    std::string command;
    in >> command;
    if (command == "print")
    {
      std::string dataset;
      in >> dataset;
      zakirov::print_d(out, dataset, find_d(dataset, dictionary));
    }
    else if (command == "complement")
    {
      std::pair< std::string, std::map< K, T > > dataset_new;
      std::string dataset_1;
      std::string dataset_2;
      in >> dataset_new.first >> dataset_1 >> dataset_2;
      complement_d(dataset_new.second, find_d(dataset_1, dictionary), find_d(dataset_2, dictionary));
      dictionary.push_back(dataset_new);
    }
    else if (command == "intersect")
    {
      std::pair< std::string, std::map< K, T > > dataset_new;
      std::string dataset_1;
      std::string dataset_2;
      in >> dataset_new.first >> dataset_1 >> dataset_2;
      intersect_d(dataset_new.second, find_d(dataset_1, dictionary), find_d(dataset_2, dictionary));
      dictionary.push_back(dataset_new);
    }
    else if (command == "union")
    {
      std::pair< std::string, std::map< K, T > > dataset_new;
      std::string dataset_1;
      std::string dataset_2;
      in >> dataset_new.first >> dataset_1 >> dataset_2;
      union_d(dataset_new.second, find_d(dataset_1, dictionary), find_d(dataset_2, dictionary));
      dictionary.push_back(dataset_new);
    }
    else
    {
      throw std::logic_error("<INVALID ARGUMENT>");
    }
  }

  template < class K, class T >
  void print_d(std::ostream & out, std::string name, const std::map< K, T > & dictionary)
  {
    if (dictionary.empty())
    {
      throw std::invalid_argument("<EMPTY>");
    }

    out << name;
    auto iter = dictionary.cbegin();
    for (; iter != dictionary.cend(); ++iter)
    {
      out << ' ' << iter->first << ' ' << iter->second;
    }

    out << '\n';
  }

  template < class K, class T >
  void complement_d(std::map< K, T > & result_d, const std::map< K, T > & first_d, const std::map< K, T > & second_d)
  {
    if (first_d.empty())
    {
      result_d = second_d;
      return;
    }
    else
    {
      result_d = first_d;
      return;
    }

    auto first_iter = first_d.cbegin();
    auto second_iter = second_d.cbegin();

    while (first_iter != first_d.cend() && second_iter != second_d.cend())
    {
      if (first_iter->first < second_iter->first)
      {
        result_d.insert({first_iter->first, first_iter->second});
        ++first_iter;
      }
      else if (first_iter->first > second_iter->first)
      {
        result_d.insert({second_iter->first, second_iter->second});
        ++second_iter;
      }
      else
      {
        ++second_iter;
        ++first_iter;
      }
    }

    while (first_iter != first_d.cend())
    {
      result_d.insert({first_iter->first, first_iter->second});
      ++first_iter;
    }

    while (second_iter != second_d.cend())
    {
      result_d.insert({second_iter->first, second_iter->second});
      ++second_iter;
    }
  }

  template < class K, class T >
  void intersect_d(std::map< K, T > & result_d, const std::map< K, T > & first_d, const std::map< K, T > & second_d)
  {
    result_d.clear();
    if (first_d.empty() || second_d.empty())
    {
      return;
    }

    auto first_iter = first_d.cbegin();
    auto second_iter = second_d.cbegin();

    while (first_iter != first_d.cend() && second_iter != second_d.cend())
    {
      if (first_iter->first < second_iter->first)
      {
        ++first_iter;
      }
      else if (first_iter->first > second_iter->first)
      {
        ++second_iter;
      }
      else
      {
        result_d.insert({first_iter->first, first_iter->second});
        ++second_iter;
        ++first_iter;
      }
    }
  }

  template < class K, class T >
  void union_d(std::map< K, T > & result_d, const std::map< K, T > & first_d, const std::map< K, T > & second_d)
  {
    if (first_d.empty())
    {
      result_d = second_d;
      return;
    }
    else
    {
      result_d = first_d;
      return;
    }

    auto first_iter = first_d.cbegin();
    auto second_iter = second_d.cbegin();

    while (first_iter != first_d.cend() && second_iter != second_d.cend())
    {
      if (first_iter->first < second_iter->first)
      {
        result_d.insert({first_iter->first, first_iter->second});
        ++first_iter;
      }
      else if (first_iter->first > second_iter->first)
      {
        if (second_iter->first != first_iter->first)
        {
          result_d.insert({second_iter->first, second_iter->second});
        }

        ++second_iter;
      }
      else if (first_iter->first == second_iter->first)
      {
        result_d.insert({first_iter->first, first_iter->second});
        ++second_iter;
        ++first_iter;
      }
    }

    while (first_iter != first_d.cend())
    {
      result_d.insert({first_iter->first, first_iter->second});
      ++first_iter;
    }

    while (second_iter != second_d.cend())
    {
      result_d.insert({second_iter->first, second_iter->second});
      ++second_iter;
    }
  }
}

#endif
