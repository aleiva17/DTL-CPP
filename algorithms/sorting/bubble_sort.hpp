#pragma once
#ifndef _BUBBLE_SORT_HPP_
#define _BUBBLE_SORT_HPP_
#include "vector.hpp"
#include <cstddef>

namespace dby
{
  class BubbleSort
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
      bool isSorted;
      std::size_t n = vec.size();

      for (std::size_t i = 0; i < n - 1; ++i) 
      {
        isSorted = true;

        for (std::size_t j = 0; j < n - i - 1; ++j) 
        {
          if (compare(vec.at(j), vec.at(j + 1)))
          {
            BubbleSort::swap(vec.at(j), vec.at(j + 1));
            isSorted = false;
          }
        }
        
        if (isSorted)
        {
          break;
        }
      }
    }

    template <typename T>
    static void sort(dby::vector<T>* &vec, bool(*compare)(T a, T b) = [](T a, T b){ return a > b; })
    {
      bool isSorted;
      std::size_t n = vec->size();

      for (std::size_t i = 0; i < n - 1; ++i) {
        isSorted = true;

        for (std::size_t j = 0; j < n - i - 1; ++j) 
        {
          if (compare(vec->at(j), vec->at(j + 1)))
          {
            BubbleSort::swap(vec->at(j), vec->at(j + 1));
            isSorted = false;
          }
        }
        
        if (isSorted)
        {
          break;
        }
      }
    }
  };
}

#endif