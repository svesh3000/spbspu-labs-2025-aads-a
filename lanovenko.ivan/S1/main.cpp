#include <iostream>
#include <utility>
#include <list>
#include <iomanip>

void printSequencesName(const std::list<std::pair<std::string, std::list<int>>> temporary)
{
  auto it = temporary.begin();
  std::cout << (*it).first;
  for (++it; it != temporary.end(); it++)
  {
    std::cout << " " << (*it).first;
  }
  std::cout << '\n';
}

void printSequences(const std::list < std::pair < std::string, std::list<int>>> temporary, int* array, size_t maxSize)
{
  for (size_t i = 0; i < maxSize; i++)
  {
    size_t res = 0;
    bool isFirstElement = true;
    for (const auto& pair : temporary)
    {
      if (!pair.second.empty() && i < pair.second.size())
      {
        auto it = pair.second.begin();
        std::advance(it, i);
        if (!isFirstElement)
        {
          std::cout << " ";
        }
        std::cout << (*it);
        res += *(it);
        isFirstElement = false;
      }
    }
    array[i] = res;
    std::cout << '\n';
  }
}

void printSequencesSum(const int* sumArray, size_t maxSize)
{
  std::cout << sumArray[0];
  for (size_t i = 1; i < maxSize; i++)
  {
    std::cout << " " << sumArray[i];
  }
  std::cout << '\n';
}

int main()
{
  std::list < std::pair<std::string, std::list<int>>> myList;
  std::string sequenceName = "";
  while (std::cin >> sequenceName)
  {
    int element = 0;
    std::list<int> temporaryList{};
    while (std::cin >> element)
    {
      temporaryList.push_back(element);
    }
    std::pair<std::string, std::list<int>> temporaryPair{ sequenceName, temporaryList };
    myList.push_back(temporaryPair);
    if (std::cin.eof())
    {
      break;
    }
    std::cin.clear();
  }
  printSequencesName(myList);
  size_t maxSize = 0;
  int* sumArray = nullptr;
  for (const auto& i : myList)
  {
    if (maxSize < i.second.size())
    {
      maxSize = i.second.size();
    }
  }
  try
  {
    sumArray = new int[maxSize] {};
  }
  catch (const std::bad_alloc& e)
  {
    std::cerr << "Out of memmory\n";
    return 1;
  }
  printSequences(myList, sumArray, maxSize);
  printSequencesSum(sumArray, maxSize);
  delete[] sumArray;
}
