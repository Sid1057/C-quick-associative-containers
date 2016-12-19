#include "../quick_set/quick_set.hpp" // quick_set

#include <set> // set
#include <unordered_set> // unordered_set
#include <iterator> // istream_iterator ostream_iterator inserter
#include <algorithm> // copy
#include <iostream> // cerr cin cout
#include <ctime> // clock_t time CLOCK_PER_SEC

size_t my_simple_hash(long int i)
{
  size_t result = 0;
  do
  {
    result += i % 10;
    i /= 10;
  } while (i > 0);
  return result;
}

size_t my_another_simple_hash(long int i)
{
  return std::hash<long int>{}(~i * 13);
}

int main(int /*argc*/, const char *[])
{
  std::vector< int > integers;

  std::copy(std::istream_iterator< long int >(std::cin),
            std::istream_iterator< long int >{},
            std::inserter(integers, integers.begin()));

  if (!std::cin.eof())
  {
    std::cerr << "Error in reading input.\n";
    return 2;
  }

  std::set< long int > usual_set;

  std::unordered_set< long int > usual_unordered_set;

  Quick_set< long int, 105019, unsigned int>
  my_set({std::hash< long int >{}/*, my_simple_hash*//*, my_another_simple_hash*/});

  Counting_bloom_filter< long int, 105019, unsigned int >
  my_bloom({std::hash< long int >{}, my_simple_hash, my_another_simple_hash});

  unsigned int founded = 0;

  std::cout << "\n\n\nCount of integers is: " << integers.size() << "\n\n";

  std::cout << "Inserting:\n";
  std::cout << "|Container|Inserting clocks|seconds     |Spec size|\n";
  std::cout << "|_________|________________|____________|_________|\n";
  clock_t t = clock();
  for (auto& i : integers)
  {
    usual_set.insert(i);
  }
  t = clock() - t;
  std::cout << "|Set      |";
  std::cout.width(16);
  std::cout << t << "|";
  std::cout.width(12);
  std::cout << ((float)t)/CLOCKS_PER_SEC << "|";
  std::cout.width(9);
  std::cout << usual_set.size() * sizeof(long int) << "|\n";
  std::cout << "|_________|________________|____________|_________|\n";

  t = clock();
  for (auto& i : integers)
  {
    usual_unordered_set.insert(i);
  }
  t = clock() - t;
  std::cout << "|Unord Set|";
  std::cout.width(16);
  std::cout << t << "|";
  std::cout.width(12);
  std::cout << ((float)t)/CLOCKS_PER_SEC << "|";
  std::cout.width(9);
  std::cout << usual_unordered_set.bucket_count() * sizeof(long int) << "|\n";
  std::cout << "|_________|________________|____________|_________|\n";

  t = clock();
  for (auto& i : integers)
  {
    my_set.insert(i);
  }
  t = clock() - t;
  std::cout << "|Quick Set|";
  std::cout.width(16);
  std::cout << t << "|";
  std::cout.width(12);
  std::cout << ((float)t)/CLOCKS_PER_SEC << "|";
  std::cout.width(9);
  std::cout << my_set.size() * sizeof(long int) + 4999 * sizeof(unsigned int) << "|\n";
  std::cout << "|_________|________________|____________|_________|\n";

  t = clock();
  for (auto& i : integers)
  {
    my_bloom.insert(i);
  }
  t = clock() - t;
  std::cout << "|Bloom    |";
  std::cout.width(16);
  std::cout << t << "|";
  std::cout.width(12);
  std::cout << ((float)t)/CLOCKS_PER_SEC << "|";
  std::cout.width(9);
  std::cout << 4999 * sizeof(unsigned int) << "|\n";
  std::cout << "|_________|________________|____________|_________|\n";
  
  std::cout << "\nFinding:\n";
  std::cout << "|Container|Finding   clocks|Seconds     |Founded|\n";
  std::cout << "|_________|________________|____________|_______|\n";
  
  founded = 0;
  t = clock();
  for (long long int i = 3000000; i < 4000000; ++i)
  {
    if (usual_set.find(i) != usual_set.end())
    {
      founded++;
    }
  }
  t = clock() - t;
  std::cout << "|Set      |";
  std::cout.width(16);
  std::cout << t << "|";
  std::cout.width(12);
  std::cout << ((float)t)/CLOCKS_PER_SEC << "|";
  std::cout.width(7);
  std::cout << founded << "|\n";
  std::cout << "|_________|________________|____________|_______|\n";

  founded = 0;
  t = clock();
  for (long long int i = 3000000; i < 4000000; ++i)
  {
    if (usual_unordered_set.find(i) != usual_unordered_set.end())
    {
      founded++;
    }
  }
  t = clock() - t;
  std::cout << "|Unord set|";
  std::cout.width(16);
  std::cout << t << "|";
  std::cout.width(12);
  std::cout << ((float)t)/CLOCKS_PER_SEC << "|";
  std::cout.width(7);
  std::cout << founded << "|\n";
  std::cout << "|_________|________________|____________|_______|\n";

  founded = 0;
  t = clock();
  for (long long int i = 3000000; i < 4000000; ++i)
  {
    if (my_set.find(i) != my_set.end())
    {
      founded++;
    }
  }
  t = clock() - t;
  std::cout << "|Quick set|";
  std::cout.width(16);
  std::cout << t << "|";
  std::cout.width(12);
  std::cout << ((float)t)/CLOCKS_PER_SEC << "|";
  std::cout.width(7);
  std::cout << founded << "|\n";
  std::cout << "|_________|________________|____________|_______|\n";
  
  founded = 0;
  t = clock();
  for (long long int i = 3000000; i < 4000000; ++i)
  {
    if (my_bloom.has(i))
    {
      founded++;
    }
  }
  t = clock() - t;
  std::cout << "|Bloom    |";
  std::cout.width(16);
  std::cout << t << "|";
  std::cout.width(12);
  std::cout << ((float)t)/CLOCKS_PER_SEC << "|";
  std::cout.width(7);
  std::cout << founded << "|\n";
  std::cout << "|_________|________________|____________|_______|\n\n\n";

  return 0;
}