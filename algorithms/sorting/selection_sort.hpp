#pragma once
#ifndef _SELECTION_SORT_HPP_
#define _SELECTION_SORT_HPP_
#include "vector.hpp"
#include <cstddef>

namespace dby
{
  class SelectionSort
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
      std::size_t minIndex;
      std::size_t n = vec.size();

      for (std::size_t i = 0; i < n - 1; ++i)
      {
        minIndex = i;
        for (std::size_t j = i + 1; j < n; ++j)
        {
          if (compare(vec.at(minIndex), vec.at(j)))
          {
            minIndex = j;
          }
        }
        SelectionSort::swap(vec.at(minIndex), vec.at(i));
      }
    }

    template <typename T>
    static void sort(dby::vector<T>* &vec, bool(*compare)(T, T) = [](T a, T b){ return a > b; })
    {
      std::size_t minIndex;
      std::size_t n = vec->size();

      for (std::size_t i = 0; i < n - 1; ++i)
      {
        minIndex = i;
        for (std::size_t j = i + 1; j < n; ++j)
        {
          if (compare(vec->at(minIndex), vec->at(j)))
          {
            minIndex = j;
          }
        }
        SelectionSort::swap(vec->at(minIndex), vec->at(i));
      }
    }
  };
}

#endif