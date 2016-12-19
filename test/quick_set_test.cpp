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

class A
{
public:
  A():
    vec(0)
  {}
  ~A() = default;
  size_t Hash()
  {
    size_t result = 0;
    for (auto& i : vec)
    {
      result += std::hash< long int >()(i);
    }
    return result / vec.size(); 
  }
private:
  std::vector< long int > vec;
};

size_t my_another_simple_hash(long int i)
{
  return std::hash<long int>{}(~i * 13);
}

template< unsigned int hash_size>
void test(std::vector< int >& integers)
{
  std::set< long int > usual_set;

  std::unordered_set< long int > usual_unordered_set;

  Quick_set< long int, hash_size, unsigned short int>
  my_set({std::hash< long int >{}/*, my_simple_hash*//*, my_another_simple_hash*/});

  Counting_bloom_filter< long int, hash_size, unsigned short int >
  my_bloom({std::hash< long int >{}, my_simple_hash, my_another_simple_hash});

  unsigned int founded = 0;

  std::cout << "\n\n\nCount of integers is: " << integers.size() << "\n\n";

  std::cout << "Inserting:\n";
  std::cout << "|Container|Inserting clocks|seconds     |Spec size|\n";
  std::cout << "|_________|________________|____________|_________|\n";
  clock_t t = clock();
  clock_t set_time = 0;
  clock_t unordered_set_time = 0;
  clock_t my_set_time = 0;

  size_t set_size = 0;
  size_t unordered_set_size = 0;
  size_t my_set_size = 0;

  for (auto& i : integers)
  {
    usual_set.insert(i);
  }
  t = clock() - t;
  set_size = usual_set.size() * sizeof(long int);

  std::cout << "|Set      |";
  std::cout.width(16);
  std::cout << t << "|";
  std::cout.width(12);
  std::cout << ((float)t)/CLOCKS_PER_SEC << "|";
  std::cout.width(9);
  std::cout << set_size << "|\n";
  std::cout << "|_________|________________|____________|_________|\n";

  t = clock();
  for (auto& i : integers)
  {
    usual_unordered_set.insert(i);
  }
  t = clock() - t;
  unordered_set_size = usual_unordered_set.bucket_count() * sizeof(long int);

  std::cout << "|Unord Set|";
  std::cout.width(16);
  std::cout << t << "|";
  std::cout.width(12);
  std::cout << ((float)t)/CLOCKS_PER_SEC << "|";
  std::cout.width(9);
  std::cout << unordered_set_size << "|\n";
  std::cout << "|_________|________________|____________|_________|\n";

  t = clock();
  for (auto& i : integers)
  {
    my_set.insert(i);
  }
  t = clock() - t;
  my_set_size = my_set.size() * sizeof(long int) + hash_size * sizeof(unsigned short int);

  std::cout << "|Quick Set|";
  std::cout.width(16);
  std::cout << t << "|";
  std::cout.width(12);
  std::cout << ((float)t)/CLOCKS_PER_SEC << "|";
  std::cout.width(9);
  std::cout << my_set_size << "|\n";
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
  std::cout << hash_size * sizeof(unsigned short int) << "|\n";
  std::cout << "|_________|________________|____________|_________|\n";

  std::cout << "\nFinding:\n";
  std::cout << "|Container|Finding   clocks|Seconds     |Founded|\n";
  std::cout << "|_________|________________|____________|_______|\n";
  
  founded = 0;
  t = clock();
  for (long long int i = 100000; i < 2000000; ++i)
  {
    if (usual_set.find(i) != usual_set.end())
    {
      founded++;
    }
  }
  t = clock() - t;
  set_time = t;
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
  for (long long int i = 100000; i < 2000000; ++i)
  {
    if (usual_unordered_set.find(i) != usual_unordered_set.end())
    {
      founded++;
    }
  }
  t = clock() - t;
  unordered_set_time = t;
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
  for (long long int i = 100000; i < 2000000; ++i)
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
  my_set_time = t;
  
  founded = 0;
  t = clock();
  for (long long int i = 100000; i < 2000000; ++i)
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
  std::cout << "|_________|________________|____________|_______|\n";

  if (my_set_time <= set_time)
  {
    if (my_set_time <= unordered_set_time)
    {
      std::cout << "VERY ";
    }
    std::cout << "GOOD TIME ";
  }
  if (my_set_size < unordered_set_size)
  {
    std::cout << "GOOD SIZE ";
  }

  std::cout << "\n\n\n";
}

int main(int /*argc*/, const char* /*argv*/[])
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

  std::cout << "Hash size is " << 103 << "\n";
  test<103>(integers);
  std::cout << "Hash size is " << 1009 << "\n";
  test<1009>(integers);
  std::cout << "Hash size is " << 4999 << "\n";
  test<4999>(integers);
  std::cout << "Hash size is " << 105019 << "\n";
  test<105019>(integers);
  std::cout << "Hash size is " << 250007 << "\n";
  test<250007>(integers);

  return 0;
}