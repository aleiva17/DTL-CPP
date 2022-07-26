#pragma once
#ifndef _HEAP_SORT_HPP_
#define _HEAP_SORT_HPP_
#include "vector.hpp"
#include <cstddef>

namespace dby
{
  class HeapSort
  {
    template <typename T>
    static void swap(T& a, T& b)
    {
      T c = a;
      a = b;
      b = c;
    }

    template <typename T>
    static void heapify(dby::vector<T> &vec, std::size_t n, std::size_t i, bool(*compare)(T, T))
    {
      std::size_t largest = i;
      std::size_t left = 2 * i + 1;
      std::size_t right = 2 * i + 2;

      if (left < n && compare(vec.at(left), vec.at(largest)))
      {
        largest = left;
      }

      if (right < n && compare(vec.at(right), vec.at(largest)))
      {
        largest = right;
      }

      if (largest != i)
      {
        HeapSort::swap(vec.at(i), vec.at(largest));
        HeapSort::heapify(vec, n, largest, compare);
      }
    }

    template <typename T>
    static void heapify(dby::vector<T>* &vec, std::size_t n, std::size_t i, bool(*compare)(T, T))
    {
      std::size_t largest = i;
      std::size_t left = 2 * i + 1;
      std::size_t right = 2 * i + 2;

      if (left < n && compare(vec->at(left), vec->at(largest)))
      {
        largest = left;
      }

      if (right < n && compare(vec->at(right), vec->at(largest)))
      {
        largest = right;
      }

      if (largest != i)
      {
        HeapSort::swap(vec->at(i), vec->at(largest));
        HeapSort::heapify(vec, n, largest, compare);
      }
    }

  public:
    template <typename T>
    static void sort(dby::vector<T> &vec, bool(*compare)(T, T) = [](T a, T b){ return a > b; })
    {
      std::size_t n = vec.size();

      for (long long i = n / 2 - 1; i >= 0; --i)
      {
        HeapSort::heapify(vec, n, i, compare);
      }

      for (std::size_t i = n - 1; i > 0; --i)
      {
        HeapSort::swap(vec.at(0), vec.at(i));
        HeapSort::heapify(vec, i, 0, compare);
      }
    }

    template <typename T>
    static void sort(dby::vector<T>* &vec, bool(*compare)(T, T) = [](T a, T b){ return a > b; })
    {
      std::size_t n = vec->size();

      for (long long i = n / 2 - 1; i >= 0; --i)
      {
        HeapSort::heapify(vec, n, i, compare);
      }

      for (std::size_t i = n - 1; i > 0; --i)
      {
        HeapSort::swap(vec->at(0), vec->at(i));
        HeapSort::heapify(vec, i, 0, compare);
      }
    }
  };
}

#endif