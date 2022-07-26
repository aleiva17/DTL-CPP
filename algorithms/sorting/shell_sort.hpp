#pragma once
#ifndef _SHELL_SORT_HPP_
#define _SHELL_SORT_HPP_
#include "vector.hpp"
#include <cstddef>

namespace dby
{
  class ShellSort
  {
    template <typename T>
    static void swap(T& a, T& b)
    {
      T c = a;
      a = b;
      b = c;
    }
  public:
    template <typename T>
    static void sort(dby::vector<T> &vec, bool(*compare)(T, T) = [](T a, T b){ return a > b; })
    {
      std::size_t j, n = vec.size();
      
      for (std::size_t gap = n / 2; gap > 0; gap /= 2)
      {
        for (std::size_t i = gap; i < n; ++i)
        {
          T temp = vec.at(i);
          for (j = i; j >= gap && compare(vec.at(j - gap), temp); j -= gap)
          {
            vec.at(j) = vec.at(j - gap);
          }
          vec.at(j) = temp;
        }
      }
    }

    template <typename T>
    static void sort(dby::vector<T>* &vec, bool(*compare)(T, T) = [](T a, T b){ return a > b; })
    {
      std::size_t j, n = vec->size();
      
      for (std::size_t gap = n / 2; gap > 0; gap /= 2)
      {
        for (std::size_t i = gap; i < n; ++i)
        {
          T temp = vec->at(i);
          for (j = i; j >= gap && compare(vec->at(j - gap), temp); j -= gap)
          {
            vec->at(j) = vec->at(j - gap);
          }
          vec->at(j) = temp;
        }
      }
    }
  };
}

#endif