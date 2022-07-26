#pragma once
#ifndef _QUICK_SORT_HPP_
#define _QUICK_SORT_HPP_
#include "vector.hpp"
#include <cstddef>
#include <cstdlib>

namespace dby
{
  enum class quick_sort_type
  {
    normal,
    median_of_three,
    randomized
  };

  class QuickSort
  {
    template <typename T>
    static void swap(T& a, T& b)
    {
      T c = a;
      a = b;
      b = c;
    }

    static inline int max(int a, int b)
    {
      return (a > b ? a : b);
    }

    static inline int min(int a, int b)
    {
      return (a < b ? a : b);
    }

    static int median(int a, int b, int c)
    {
      return a + b + c - QuickSort::min(a, QuickSort::min(b, c)) - QuickSort::max(a, QuickSort::max(b, c));
    }

    template <typename T>
    static int partition(dby::vector<T> &vec, int begin, int end, bool(*compare)(T, T))
    {
      T pivote = vec.at(end);
      int i = begin;

      for (std::size_t j = begin; j < end; ++j) 
      {
        if (compare(pivote, vec.at(j))) 
        {
          QuickSort::swap(vec.at(i++), vec.at(j));
        }
      }

      QuickSort::swap(vec.at(i), vec.at(end));
      return i;
    }

    template <typename T>
    static int partition(dby::vector<T>* &vec, int begin, int end, bool(*compare)(T, T))
    {
      T pivote = vec->at(end);
      int i = begin;

      for (std::size_t j = begin; j < end; ++j) 
      {
        if (compare(pivote, vec->at(j))) 
        {
          QuickSort::swap(vec->at(i++), vec->at(j));
        }
      }

      QuickSort::swap(vec->at(i), vec->at(end));
      return i;
    }

    template <typename T>
    static void normal_quick_sort(dby::vector<T> &vec, int begin, int end, bool(*compare)(T, T))
    {
      if (begin >= end)
      {
        return;
      }

      int pivot = QuickSort::partition(vec, begin, end, compare);
      QuickSort::normal_quick_sort(vec, begin, pivot - 1, compare);
      QuickSort::normal_quick_sort(vec, pivot + 1, end, compare);
    }

    template <typename T>
    static void normal_quick_sort(dby::vector<T>* &vec, int begin, int end, bool(*compare)(T, T))
    {
      if (begin >= end)
      {
        return;
      }

      int pivot = QuickSort::partition(vec, begin, end, compare);
      QuickSort::normal_quick_sort(vec, begin, pivot - 1, compare);
      QuickSort::normal_quick_sort(vec, pivot + 1, end, compare);
    }

    template <typename T>
    static void randomized_quick_sort(dby::vector<T> &vec, int begin, int end, bool(*compare)(T, T))
    {
      if (begin >= end)
      {
        return;
      }

      int pivotIndex = rand() % (end - begin + 1) + begin;
      QuickSort::swap(vec.at(pivotIndex), vec.at(end));

      int pivot = QuickSort::partition(vec, begin, end, compare);
      QuickSort::randomized_quick_sort(vec, begin, pivot - 1, compare);
      QuickSort::randomized_quick_sort(vec, pivot + 1, end, compare);
    }

    template <typename T>
    static void randomized_quick_sort(dby::vector<T>* &vec, int begin, int end, bool(*compare)(T, T))
    {
      if (begin >= end)
      {
        return;
      }

      int pivotIndex = rand() % (end - begin + 1) + begin;
      QuickSort::swap(vec->at(pivotIndex), vec->at(end));

      int pivot = QuickSort::partition(vec, begin, end, compare);
      QuickSort::randomized_quick_sort(vec, begin, pivot - 1, compare);
      QuickSort::randomized_quick_sort(vec, pivot + 1, end, compare);
    }

    template <typename T>
    static void median_of_three_quick_sort(dby::vector<T> &vec, int begin, int end, bool(*compare)(T, T))
    {
      if (begin >= end)
      {
        return;
      }

      int size = end - begin;
      int pivotIndex = QuickSort::median(begin, begin + size / 2, end);
      QuickSort::swap(vec.at(pivotIndex), vec.at(end));

      int pivot = QuickSort::partition(vec, begin, end, compare);
      QuickSort::median_of_three_quick_sort(vec, begin, pivot - 1, compare);
      QuickSort::median_of_three_quick_sort(vec, pivot + 1, end, compare);
    }

    template <typename T>
    static void median_of_three_quick_sort(dby::vector<T>* &vec, int begin, int end, bool(*compare)(T, T))
    {
      if (begin >= end)
      {
        return;
      }

      int size = end - begin;
      int pivotIndex = QuickSort::median(begin, begin + size / 2, end);
      QuickSort::swap(vec->at(pivotIndex), vec->at(end));

      int pivot = QuickSort::partition(vec, begin, end, compare);
      QuickSort::median_of_three_quick_sort(vec, begin, pivot - 1, compare);
      QuickSort::median_of_three_quick_sort(vec, pivot + 1, end, compare);
    }

  public:
    template <typename T>
    static void sort(dby::vector<T> &vec, dby::quick_sort_type type = dby::quick_sort_type::normal, bool(*compare)(T, T) = [](T a, T b){ return a > b; })
    {
      switch(type)
      {
      case dby::quick_sort_type::normal: QuickSort::normal_quick_sort(vec, 0, vec.size() - 1, compare); break;
      case dby::quick_sort_type::randomized: QuickSort::randomized_quick_sort(vec, 0, vec.size() - 1, compare); break;
      case dby::quick_sort_type::median_of_three: QuickSort::median_of_three_quick_sort(vec, 0, vec.size() - 1, compare);
      }
    }

    template <typename T>
    static void sort(dby::vector<T>* &vec, dby::quick_sort_type type = dby::quick_sort_type::normal, bool(*compare)(T, T) = [](T a, T b){ return a > b; })
    {
      switch(type)
      {
      case dby::quick_sort_type::normal: QuickSort::normal_quick_sort(vec, 0, vec->size() - 1, compare); break;
      case dby::quick_sort_type::randomized: QuickSort::randomized_quick_sort(vec, 0, vec->size() - 1, compare); break;
      case dby::quick_sort_type::median_of_three: QuickSort::median_of_three_quick_sort(vec, 0, vec->size() - 1, compare);
      }
    }
  };
}

#endif