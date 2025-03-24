#include <iostream>
#include <fstream>
#include <string>
#include "queue.hpp"

double calculatePostfix(maslov::Queue< std::string > postfixQueue)
{}

maslov::Queue< std::string > infixToPostfix(maslov::Queue< std::string > infixQueue)
{}

void splitExpression(const std::string & str, maslov::Queue< std::string > infixQueue)
{
  std::string element;
  char separator = ' ';
  for (size_t i = 0; i < str.length(); ++i)
  {
    if (str[i] != separator)
    {
      element += str[i];
    }
    else
    {
      if (!element.empty())
      {
        infixQueue.push(element);
        element.clear();
      }
    }
  }
  if (!element.empty())
  {
    infixQueue.push(element);
  }
}

void inputExpression(std::istream & in, maslov::Queue< maslov::Queue< std::string > > & queue)
{
  std::string str;
  while (std::getline(in, str))
  {
    if (str.empty())
    {
      continue;
    }
    maslov::Queue< std::string > infixQueue;
    splitExpression(str, infixQueue);
    queue.push(infixQueue);
  }
}

void inputFile(const std::string & filename, maslov::Queue< maslov::Queue< std::string > > & queue)
{
  if (!filename.empty())
  {
    std::ifstream fileInput(filename);
    if (!fileInput.is_open())
    {
      throw std::runtime_error("ERROR: cannot open the file");
    }
    inputExpression(fileInput, queue);
    fileInput.close();
  }
  else
  {
    inputExpression(std::cin, queue);
  }
}

int main(int argc, char ** argv)
{
  using namespace maslov;
  std::string filename;
  if (argc > 1)
  {
    filename = argv[1];
  }
  Queue< Queue< std::string > > queue;
  try
  {
    inputFile(filename, queue);
    while (!queue.empty())
    {
      Queue< std::string > infixQueue = queue.front();
      queue.pop();
      Queue< std::string > postfixQueue = infixToPostfix(infixQueue);
      double result = calculatePostfix(postfixQueue);
      std::cout << result << "\n";
    }
  }
  catch (const std::exception & e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
}
