#pragma once
#ifndef _COMB_SORT_HPP_
#define _COMB_SORT_HPP_
#include "vector.hpp"
#include <cstddef>

namespace dby
{
  class CombSort
  {
    template <typename T>
    static void swap(T& a, T& b)
    {
      T c = a;
      a = b;
      b = c;
    }

    static std::size_t getNextGap(std::size_t gap)
    {
      gap = gap * 10 / 13;
      return (gap >= 1 ? gap : 1);
    }
  public:
    template <typename T>
    static void sort(dby::vector<T> &vec, bool(*compare)(T, T) = [](T a, T b){ return a > b; })
    {
      std::size_t n = vec.size();
      std::size_t gap = n;
      bool swapped = true;

      while (gap != 1 || swapped)
      {
        gap = CombSort::getNextGap(gap);
        swapped = false;

        for (std::size_t i = 0; i < n - gap; ++i)
        {
          if (compare(vec.at(i), vec.at(i + gap)))
          {
            CombSort::swap(vec.at(i), vec.at(i + gap));
            swapped = true;
          }
        }
      }
    }

    template <typename T>
    static void sort(dby::vector<T>* &vec, bool(*compare)(T, T) = [](T a, T b){ return a > b; })
    {
      std::size_t n = vec->size();
      std::size_t gap = n;
      bool swapped = true;

      while (gap != 1 || swapped)
      {
        gap = CombSort::getNextGap(gap);
        swapped = false;

        for (std::size_t i = 0; i < n - gap; ++i)
        {
          if (compare(vec->at(i), vec->at(i + gap)))
          {
            CombSort::swap(vec->at(i), vec->at(i + gap));
            swapped = true;
          }
        }
      }
    }
  };
}

#endif