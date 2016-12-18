#include <functional> // hash function
#include <vector> // vector
#include <initializer_list> // vector

template< class Key,
          size_t bucket_count,
          typename counting_type = unsigned int>
class Counting_bloom_filter
{
public:
  Counting_bloom_filter() = delete;
  Counting_bloom_filter(std::initializer_list< std::function< size_t(Key)> > functions = {std::hash< Key >{}})
    :
     hash_functions(functions),
     table(bucket_count)
  {
    if (hash_functions.empty())
    {
      hash_functions.push_back(std::hash< Key >{});
    }
  }
  ~Counting_bloom_filter() = default;

  bool has(Key& item) const
  {
    for (auto& hash_fn : hash_functions)
    {
      if (table[hash_fn(item) % bucket_count] == 0)
      {
        return false;
      }
    }
    return true;
  }

  void insert(Key item)
  {
    for (auto& hash_fn : hash_functions)
    {
      ++table[hash_fn(item) % bucket_count];
    }
  }

  void erase(Key item)
  {
    for (auto& hash_fn : hash_functions)
    {
      if (table[hash_fn(item) % bucket_count] != 0)
      {
        --table[hash_fn(item) % bucket_count];
      }
    }
  }

private:
  std::vector< std::function< size_t(Key) > > hash_functions;
  std::vector< counting_type > table;
};
