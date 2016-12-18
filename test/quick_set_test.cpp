#include "../quick_set/quick_set.hpp" // quick_set

#include <set> // set
#include <unordered_set> // unordered_set
#include <iterator> // istream_iterator ostream_iterator inserter
#include <algorithm> // copy
#include <iostream> // cerr cin cout
#include <ctime> // clock_t time CLOCK_PER_SEC

int main(int /*argc*/, const char *[])
{
  std::vector< int > integers;

  std::copy(std::istream_iterator< int >(std::cin),
            std::istream_iterator< int >{},
            std::inserter(integers, integers.begin()));

  if (!std::cin.eof())
  {
    std::cerr << "Error in reading input.\n";
    return 2;
  }

  std::set< int > usual_set;
  std::unordered_set< int > usual_unordered_set;
  Quick_set< int, 3193 > my_set;
  Counting_bloom_filter< int, 3193> my_bloom({std::hash< int >{}});
  unsigned int founded = 0;

  std::cout << "Sequence:\n";
  // std::copy(integers.begin(), integers.end(),
  //           std::ostream_iterator< int >(std::cout, "\n"));

  std::cout << "Count of integers is: " << integers.size() << "\n";

  clock_t t = clock();
  for (auto& i : integers)
  {
    usual_set.insert(i);
  }
  t = clock() - t;
  std::cout << "Time to insert every item in set is: "
            << t << "clicks"
            << "(" << ((float)t)/CLOCKS_PER_SEC << " seconds)" << "\n"
            << "usual set contains " <<  usual_set.size() << "items\n";

  t = clock();
  for (auto& i : integers)
  {
    usual_unordered_set.insert(i);
  }
  t = clock() - t;
  std::cout << "Time to insert every item in unordered set is: "
            << t << "clicks"
            << "(" << ((float)t)/CLOCKS_PER_SEC << " seconds)" << "\n"
            << "usual unordered set contains " <<  usual_unordered_set.size() << "items\n";

  t = clock();
  for (auto& i : integers)
  {
    my_set.insert(i);
  }
  t = clock() - t;
  std::cout << "Time to insert every item in Quick set is: "
            << t << "clicks"
            << "(" << ((float)t)/CLOCKS_PER_SEC << " seconds)" << "\n"
            << "Quick set contains " <<  my_set.size() << "items\n";

  t = clock();
  for (auto& i : integers)
  {
    my_bloom.insert(i);
  }
  t = clock() - t;
  std::cout << "Time to insert every item in Bloom filter is: "
            << t << "clicks"
            << "(" << ((float)t)/CLOCKS_PER_SEC << " seconds)" << "\n";
  
  founded = 0;
  t = clock();
  for (auto i = 0; i < 50000; ++i)
  {
    if (usual_set.find(i) != usual_set.end())
    {
      founded++;
    }
  }
  t = clock() - t;
  std::cout << "Time for finding count of items from 0 to 5000 in set is: "
            << t << "clicks"
            << "(" << ((float)t)/CLOCKS_PER_SEC << " seconds)" << "\n";
  std::cout << "Founded: " << founded << "\n";

  founded = 0;
  t = clock();
  for (auto i = 0; i < 50000; ++i)
  {
    if (usual_unordered_set.find(i) != usual_unordered_set.end())
    {
      founded++;
    }
  }
  t = clock() - t;
  std::cout << "Time for finding count of items from 0 to 5000 in unordered set is: "
            << t << "clicks"
            << "(" << ((float)t)/CLOCKS_PER_SEC << " seconds)" << "\n";
  std::cout << "Founded: " << founded << "\n";

  founded = 0;
  t = clock();
  for (auto i = 0; i < 50000; ++i)
  {
    if (my_set.find(i) != my_set.end())
    {
      founded++;
    }
  }
  t = clock() - t;
  std::cout << "Time for finding count of items from 0 to 5000 in quick set is: "
            << t << "clicks"
            << "(" << ((float)t)/CLOCKS_PER_SEC << " seconds)" << "\n";
  std::cout << "Founded: " << founded << "\n";
  
  founded = 0;
  t = clock();
  for (auto i = 0; i < 50000; ++i)
  {
    if (my_bloom.has(i))
    {
      founded++;
    }
  }
  t = clock() - t;
  std::cout << "Time for finding count of items from 0 to 5000 in Bloom filter is: "
            << t << "clicks"
            << "(" << ((float)t)/CLOCKS_PER_SEC << " seconds)" << "\n";
  std::cout << "Founded: " << founded << "\n";

  return 0;
}