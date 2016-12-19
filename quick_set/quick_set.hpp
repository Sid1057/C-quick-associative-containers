#ifndef HPP_QUICK_SET
#define HPP_QUICK_SET

#include "../bloom_filter/bloom_filter.hpp" // bloom_filter

#include <set>

template< class Key,
          size_t bucket_count,
          typename counting_type = unsigned int >
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

  Quick_set(const std::initializer_list< std::function< size_t(Key)> > functions = {std::hash< Key >{}})
  :bloom(functions)
  {}
  ~Quick_set() = default;
  // insert
  std::pair<iterator,bool> insert (const  Key & val)
  {
    bloom.insert(val);
    return base_set::insert(val);
  }

  std::pair<iterator,bool> insert ( Key && val)
  {
    bloom.insert(val);
    return base_set::insert(val);
  }

  iterator insert (const_iterator position, const  Key & val)
  {
    bloom.insert(val);
    return base_set::insert(position, val);
  }

  iterator insert (const_iterator position,  Key && val)
  {
    bloom.insert(val);
    return base_set::insert(position, val);
  }

  template <class InputIterator>
    void insert (InputIterator first, InputIterator last)
  {
    for (auto i = first; i != last; ++i)
    {
      bloom.insert(*i);
      return base_set::insert(*i);
    }
  }

  void insert (std::initializer_list< Key > il)
  {
    for (auto&& i : il)
    {
      bloom.insert(i);
      base_set::insert(i);    
    }
  }

  iterator erase (const_iterator position)
  {
    bloom.erase(*position);
    return base_set::erase(position);
  }

  size_type erase (const Key& val)
  {
    bloom.erase(val);
    return base_set::erase(val);
  }

  iterator erase (const_iterator first, const_iterator last)
  {
    for (auto i = first; i != last; ++i)
    {
      bloom.erase(*i);
      base_set::erase(i);
    }
  }

  const_iterator find (const Key&& val) const
  {
    if (!bloom.has(val))
    {
      return base_set::cend();
    }
    else
    {
      return base_set::find(val);
    }
  }

  iterator find (const Key&& val)
  {
    if (!bloom.has(val))
    {
      return base_set::end();
    }
    else
    {
      return base_set::find(val);
    }
  }
private:
  Counting_bloom_filter< Key, bucket_count, counting_type > bloom;
};

#endif
