#pragma once
#ifndef _INTRO_SORT_HPP_
#define _INTRO_SORT_HPP_
#include "vector.hpp"
#include <cstddef>
#include <cmath>

namespace dby
{
  class IntroSort
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
      return a + b + c - IntroSort::min(a, IntroSort::min(b, c)) - IntroSort::max(a, IntroSort::max(b, c));
    }

    template <typename T>
    static void insertionSort(dby::vector<T> &vec, int begin, int end, bool(*compare)(T, T))
    {
      for (std::size_t i = begin + 1; i <= end; ++i)
      {
        T temp = vec.at(i);
        int j = i - 1;

        while (j >= begin && compare(vec.at(j), temp))
        {
          vec.at(j + 1) = vec.at(j);
          --j;
        }

        vec.at(j + 1) = temp;
      }
    }

    template <typename T>
    static void insertionSort(dby::vector<T>* &vec, int begin, int end, bool(*compare)(T, T))
    {
      for (std::size_t i = begin + 1; i <= end; ++i)
      {
        T temp = vec->at(i);
        int j = i - 1;

        while (j >= begin && compare(vec->at(j), temp))
        {
          vec->at(j + 1) = vec->at(j);
          --j;
        }

        vec->at(j + 1) = temp;
      }
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
          IntroSort::swap(vec.at(i++), vec.at(j));
        }
      }

      IntroSort::swap(vec.at(i), vec.at(end));
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
          IntroSort::swap(vec->at(i++), vec->at(j));
        }
      }

      IntroSort::swap(vec->at(i), vec->at(end));
      return i;
    }

    template <typename T>
    static void heapify(dby::vector<T> &vec, int n, int i, bool(*compare)(T, T))
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
        IntroSort::swap(vec.at(i), vec.at(largest));
        IntroSort::heapify(vec, n, largest, compare);
      }
    }

    template <typename T>
    static void heapify(dby::vector<T>* &vec, int n, int i, bool(*compare)(T, T))
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
        IntroSort::swap(vec->at(i), vec->at(largest));
        IntroSort::heapify(vec, n, largest, compare);
      }
    }

    template <typename T>
    static void heapSort(dby::vector<T> &vec, int n, bool(*compare)(T, T))
    {
      for (int i = n / 2 - 1; i >= 0; --i)
      {
        IntroSort::heapify(vec, n, i, compare);
      }

      for (int i = n - 1; i > 0; --i)
      {
        IntroSort::swap(vec.at(0), vec.at(i));
        IntroSort::heapify(vec, i, 0, compare);
      }
    }

    template <typename T>
    static void heapSort(dby::vector<T>* &vec, int n, bool(*compare)(T, T))
    {
      for (int i = n / 2 - 1; i >= 0; --i)
      {
        IntroSort::heapify(vec, n, i, compare);
      }

      for (int i = n - 1; i > 0; --i)
      {
        IntroSort::swap(vec->at(0), vec->at(i));
        IntroSort::heapify(vec, i, 0, compare);
      }
    }

    template <typename T>
    static void introSort(dby::vector<T> &vec, int begin, int end, int maxDepth, bool(*compare)(T, T))
    {
      if (begin >= end)
      {
        return;
      }

      int size = end - begin;

      if (size < 16)
      {
        IntroSort::insertionSort(vec, begin, end, compare);
        return;
      }

      if (maxDepth == 0)
      {
        IntroSort::heapSort(vec, end + 1, compare);
        return;
      }

      int pivot = IntroSort::median(begin, begin + size / 2, end);
      IntroSort::swap(vec.at(pivot), vec.at(end));

      int partitionIndex = IntroSort::partition(vec, begin, end, compare);
      IntroSort::introSort(vec, begin, partitionIndex - 1, maxDepth - 1, compare);
      IntroSort::introSort(vec, partitionIndex + 1, end, maxDepth - 1, compare);
    }

    template <typename T>
    static void introSort(dby::vector<T>* &vec, int begin, int end, int maxDepth, bool(*compare)(T, T))
    {
      if (begin >= end)
      {
        return;
      }

      int size = end - begin;

      if (size < 16)
      {
        IntroSort::insertionSort(vec, begin, end, compare);
        return;
      }

      if (maxDepth == 0)
      {
        IntroSort::heapSort(vec, end + 1, compare);
        return;
      }

      int pivot = IntroSort::median(begin, begin + size / 2, end);
      IntroSort::swap(vec->at(pivot), vec->at(end));

      int partitionIndex = IntroSort::partition(vec, begin, end, compare);
      IntroSort::introSort(vec, begin, partitionIndex - 1, maxDepth - 1, compare);
      IntroSort::introSort(vec, partitionIndex + 1, end, maxDepth - 1, compare);
    }

  public:
    template <typename T>
    static void sort(dby::vector<T> &vec, bool(*compare)(T, T) = [](T a, T b){ return a > b; })
    {
      std::size_t n = vec.size();
      if (n == 0)
      {
        return;
      }
			int maxDepth = (n >= 1 ? log(n) * 2 : 1);
      IntroSort::introSort(vec, 0, n - 1, maxDepth, compare);
    }

    template <typename T>
    static void sort(dby::vector<T>* &vec, bool(*compare)(T, T) = [](T a, T b){ return a > b; })
    {
      std::size_t n = vec->size();
      if (n == 0)
      {
        return;
      }
			int maxDepth = (n >= 1 ? log(n) * 2 : 1);
      IntroSort::introSort(vec, 0, n - 1, maxDepth, compare);
    }
  };
}

#endif