#include <random>
#include <iostream> // cerr cout

int main(int argc, char const *argv[])
{
  int count = 0;

  if (argc == 2 && (count = std::atoi(argv[1])) > 0)
  {
    std::random_device rd;
    int median = (rd.max() - rd.min()) / 2;
    for (int i = 0; i < count; ++i)
    {
      std::cout << (int)rd() - median<< "\n";
    }
  }
  else
  {
    std::cerr << "Invalid second parametr.\nUse integer_generator_name <count>\nWhere count is length of random integer sequence.";
    return 1;
  }
  return 0;
}