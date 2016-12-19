#include "../bloom_filter/bloom_filter.hpp"

#include <iostream>

size_t my_simple_hash(int i)
{
  size_t result = 0;
  do
  {
    result += i % 10;
    i /= 10;
  } while (i > 0);
  return result;
}

int main(int /*argc*/, const char*/*argv*/[])
{
  Counting_bloom_filter< int, 113 > my_set({std::hash< int >{}, my_simple_hash});
  int i = 0;

  // reading first sequence of numbers
  while (std::cin.good())
  {
    std::cin >> i;
    my_set.insert(i);
  }

  std::cin.clear();

  // checking second sequence of numbers
  std::cout << std::boolalpha;
  while (std::cin.good())
  {
    std::cin >> i;
    std::cout << my_set.has(i) << "\n";
  }

  return 0;
}