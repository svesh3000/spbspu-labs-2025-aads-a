#include <iostream>
#include <fstream>
#include <sstream>
#include "stack.hpp"
#include "queue.hpp"
#include "input.hpp"



long long int calculator(long long int first, long long int second, std::string operat)
{
  if (operat == "+")
  {
    return first + second;
  }
  if (operat == "*")
  {
    return first * second;
  }
  if (operat == "/")
  {
    if (second == 0)
    {
      throw std::logic_error("Dividing by zero!");
    }
    return first / second;
  }
  if (operat == "%")
  {
    if (second == 0)
    {
      throw std::logic_error("Dividing by zero!");
    }
    return first % second;
  }
  return first - second;
}

long long int proc_post(karnauhova::Queue< std::string > post)
{
  long long int sum = 0;
  long long int first = 0;
  long long int second = 0;
  while (!post.empty())
  {
    std::string element = post.front();
    first = std::stoll(element);
    post.pop();
    if (post.empty() && sum == 0)
    {
      return first;
    }
    else if (post.empty())
    {
      throw std::logic_error("Incorrect");
    }
    element = post.front();
    if (!(element == "+" || element == "/" || element == "-" || element == "*" || element == "%"))
    {
      second = std::stoll(element);
      post.pop();
      element = post.front();
      sum += calculator(first, second, element);
    }
    else
    {
      sum += calculator(sum, first, element);
    }
    post.pop();
  }
  return sum;
}



void output_sums(std::ostream& out, karnauhova::Stack< long long int > calc)
{
  long long int sum = calc.top();
  out << sum;
  calc.pop();
  while (!calc.empty())
  {
    long long int sum = calc.top();
    out << " " << sum;
    calc.pop();
  }
  out << "\n";
}


karnauhova::Stack< long long int > input_str(std::istream& in)
{
  karnauhova::Stack< long long int > calc;
  std::string str;
  while (std::getline(in, str))
  {
    if (str.empty())
    {
      continue;
    }
    karnauhova::Queue< std::string > inf = karnauhova::split_str(str);
    karnauhova::Queue< std::string > post = to_post(inf);
    long long int sum = proc_post(post);
    calc.push(sum);
  }
  in.clear();
  return calc;
}

int main(int argc, char** argv)
{
  karnauhova::Stack< long long int > calc;
  try
  {
    if (argc > 1)
    {
      std::ifstream file(argv[1]);
      if (file.is_open())
      {
        calc = input_str(file);
        file.close();
      }
      else
      {
        std::cerr << "Incorrect name file\n";
        return 1;
      }
    }
    else
    {
      calc = input_str(std::cin);
    }
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
  output_sums(std::cout, calc);
  return 0;
}



