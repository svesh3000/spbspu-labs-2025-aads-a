#include <iostream>
#include <list>
#include <string>

int main()
{
  using pair_t = std::pair< std::string, std::list< unsigned long > >;
  using pair_list_t = std::list< pair_t >;

  pair_list_t list = {};
  std::string input = "";
  pair_t pair = {"", {}};
  bool isFirst = true, isEmpty = true;

  while (!std::cin.eof())
  {
    std::cin >> input;
    if (!std::isdigit(input[0]) || std::cin.eof())
    {
        if (!isFirst)
        {
            list.push_back(pair);
        }

        pair = {input, {}};
        isFirst = false;
        continue;
    }
    else
    {
        pair.second.push_front(std::stoi(input));
        isEmpty = false;
    }
  }

  if (isEmpty)
  {
    std::cout << (*list.begin()).first;
    for (auto i = ++list.cbegin(); i != list.cend(); ++i)
    {
        std::cout << " " << (*i).first;
    }
  }
  std::cout << "\n";
  
}
