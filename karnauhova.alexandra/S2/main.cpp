#include <iostream>
#include <fstream>
#include <sstream>
#include "stack.hpp"
#include "queue.hpp"

karnauhova::Queue< std::string > split_str(std::string str)
{
  karnauhova::Queue< std::string > inf;
  std::istringstream stream(str);
  std::string element;
  while (std::getline(stream, element, ' '))
  {
    inf.push(element);
  }
  return inf;
}

karnauhova::Queue< std::string > to_post(karnauhova::Queue< std::string > inf)
{
  karnauhova::Stack< std::string > symbols;
  karnauhova::Queue< std::string > post;
  while (!inf.empty())
  {
    std::string element = inf.front();
    if (element == "+" or element == "/" or element == "-" or element == "*")
    {
      std::string last = symbols.top();
      if (last == "+" or last == "/" or last == "-" or last == "*")
      {
        post.push(last);
        symbols.pop();
      }
      symbols.push(element);
      continue;
    }
    if (element == "(")
    {
      symbols.push(element);
      continue;
    }
    try
    {
      std::stoll(element);
    }
    catch(const std::exception& e)
    {
      throw std::logic_error("No number");
    }
    post.push(element);
    inf.pop();
  }
  if (!symbols.empty())
  {
    throw std::logic_error("Error in input");
  }
  return post;
}

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
    return first / second;
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
    element = post.front();
    if (!(element == "+" or element == "/" or element == "-" or element == "*"))
    {
      second = std::stoll(element);
      post.pop();
      element = post.front();
      if (second == 0 && element == "/")
      {
        throw std::logic_error("Dividing by zero!");
      }
      sum += calculator(first, second, element);
    }
    else
    {
      if (first == 0 && element == "/")
      {
        throw std::logic_error("Dividing by zero!");
      }
      sum += calculator(sum, first, element);
    }
    post.pop();
  }
  return sum;
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
    karnauhova::Queue< std::string > inf = split_str(str);
    karnauhova::Queue< std::string > post = to_post(inf);
    long long int sum = proc_post(post);
    calc.push(sum);
  }
  in.clear();
  return calc;
}

void output_sums(std::ostream& out, karnauhova::Stack< long long int > calc)
{
  long long int sum = calc.top();
  out << " " << sum;
  calc.pop();
  while (!calc.empty())
  {
    long long int sum = calc.top();
    out << " " << sum;
    calc.pop();
  }
  out << "\n";
}

int main(int argc, char** argv)
{
  karnauhova::Stack< long long int > calc;
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
  output_sums(std::cout, calc);
  return 0;
}



