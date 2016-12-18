#include "../quick_set/quick_set.hpp" // quick_set

#include <set> // set
#include <unordered_set> // unordered_set
#include <fstrean> // fstream
#include <iterator> // istream_iterator inserter
#include <algorithm> // copy

int main(int /*argc*/, const char */*argv*/[])
{
  std::fstream input("input_integers.txt", std::ios_base::in);
  std::fstream output("results.txt", std::ios_base::out);

  std::istream_iterator< int > input_begin(input);
  std::istream_iterator< int > output_begin;

  std::copy();

  std::vector< int > integers;

  std::set usual_set;
  std::unordered_set unordered_set;
  std::quick_set my_set;

  input.close();
  output.close();

  return 0;
}