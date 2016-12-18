#ifndef HPP_QUICK_SET
#define HPP_QUICK_SET

#include "../bloom_filter/bloom_filter.hpp" // bloom_filter

#include <set>

template< class Key,
          size_t bucket_count >
class Quick_set : private std::set< Key >
{
private:
  typedef std::set< Key > base_set;
public:
  typedef typename base_set::size_type       size_type;
  typedef typename base_set::iterator        iterator;
  typedef typename base_set::const_iterator  const_iterator;

  using base_set::begin;
  using base_set::cbegin;
  using base_set::clear;
  using base_set::end;
  using base_set::cend;
  using base_set::size;
  using base_set::insert;
  using base_set::erase;
  using base_set::find;

  Quick_set()
  :bloom({})
  {}
  ~Quick_set() = default;
  // insert
  std::pair<iterator,bool> insert (Key& val)
  {
    bloom.insert(val);
    return base_set::insert(val);
  }
  // iterator erase (const_iterator position)
  // {

  // }

  // size_type erase (const value_type& val)
  // {

  // }

  // iterator erase (const_iterator first, const_iterator last)
  // {

  // }

  const_iterator find (const Key& val) const
  {
    if (!bloom.has(val))
    {
      return this->cend();
    }
    else
    {
      return this->find(val);
    }
  }

  iterator find (const Key& val)
  {
    if (!bloom.has(val))
    {
      return this->cend();
    }
    else
    {
      return base_set::find(val);
    }
  }
private:
  Counting_bloom_filter< Key, bucket_count > bloom;
};


#endif
