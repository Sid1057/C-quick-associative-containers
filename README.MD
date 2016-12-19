# Quick set #

This is an implementation of associative containers which used bloom-filter

## Containers: ##
1. Counting bloom filter
2. Quick set(ordered set)

## Usage interface ##

### Bloom ###
Constructor have to get an initializer list of hash functions, which return size_t value.
Counting_bloom_filter accepted insert/find/erase operations.

``` c++
  Counting_bloom_filter< int, hash_size > bloom_set({std::hash< int >{}, my_simple_hash, my_another_simple_hash});
  bloom_set.insert(123); // void
  bloom_set.insert(43); // void
  bloom_set.erase(123); // void
  bloom_set.find(123); // bool
```

### Quick_set ###
Except constructors and template parametrs usage is the same as usge of std::set.
Constructor have to get an initializer list of hash functions, which return size_t value.
``` c++
  /***
  * template<
  * type of items
  * size of the bloom_filter table
  * type of cells in bloom_filter table 
  * >
  ***/
  Quick_set< long int, hash_size, unsigned short int>
  my_set({std::hash< long int >{}, my_simple_hash_fn, my_another_simple_hash_fn});
```

Author: [sid1057](http://www.github.com/Sid1057)
