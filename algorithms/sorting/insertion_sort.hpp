#pragma once
#ifndef _INSERTION_SORT_HPP_
#define _INSERTION_SORT_HPP_
#include "vector.hpp"
#include <cstddef>

namespace dby
{
  class InsertionSort
  {
  public:
    template <typename T>
    static void sort(dby::vector<T> &vec, bool(*compare)(T, T) = [](T a, T b){ return a > b; })
    {
      long long j;
      std::size_t n = vec.size();
      T key;

      for (std::size_t i = 1; i < n; ++i)
      {
        key = vec.at(i);
        j = i - 1;

        while (j >= 0 && compare(vec.at(j), key))
        {
          vec.at(j + 1) = vec.at(j);
          --j;
        }

        vec.at(j + 1) = key;
      }
    }

    template <typename T>
    static void sort(dby::vector<T>* &vec, bool(*compare)(T, T) = [](T a, T b){ return a > b; })
    {
      long long j;
      std::size_t n = vec->size();
      T key;

      for (std::size_t i = 1; i < n; ++i)
      {
        key = vec->at(i);
        j = i - 1;

        while (j >= 0 && compare(vec->at(j), key))
        {
          vec->at(j + 1) = vec->at(j);
          --j;
        }

        vec->at(j + 1) = key;
      }
    }
  };
}

#endif