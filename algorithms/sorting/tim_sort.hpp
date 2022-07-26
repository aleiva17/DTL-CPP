#pragma once
#ifndef _TIM_SORT_HPP_
#define _TIM_SORT_HPP_
#include "vector.hpp"
#include <cstddef>

namespace dby
{
  class TimSort
  {
    template <typename T>
    static void swap(T& a, T& b)
    {
      T c = a;
      a = b;
      b = c;
    }

    static inline std::size_t min(std::size_t a, std::size_t b)
    {
      return (a < b ? a : b);
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
    static void merge(dby::vector<T> &vec, int left, int mid, int right, bool(*compare)(T, T))
    {
      int leftSize = mid - left + 1;
      int rightSize = right - mid;

      dby::vector<T>* leftVec = new dby::vector<T>(leftSize);
      dby::vector<T>* rightVec = new dby::vector<T>(rightSize);

      for (std::size_t i = 0; i < leftSize; ++i)
      {
        leftVec->at(i) = vec.at(left + i);
      }

      for (std::size_t i = 0; i < rightSize; ++i)
      {
        rightVec->at(i) = vec.at(mid + i + 1);
      }

      std::size_t i = 0, j = 0, k = left;

      while (i < leftSize && j < rightSize)
      {
        vec.at(k++) = compare(rightVec->at(j), leftVec->at(i)) ? leftVec->at(i++) : rightVec->at(j++);
      }

      while (i < leftSize)
      {
        vec.at(k++) = leftVec->at(i++);
      }

      while (j < rightSize)
      {
        vec.at(k++) = rightVec->at(j++);
      }

      leftVec->clear();
      rightVec->clear();
      delete leftVec, rightVec;
    }

    template <typename T>
    static void merge(dby::vector<T>* &vec, int left, int mid, int right, bool(*compare)(T, T))
    {
      int leftSize = mid - left + 1;
      int rightSize = right - mid;

      dby::vector<T>* leftVec = new dby::vector<T>(leftSize);
      dby::vector<T>* rightVec = new dby::vector<T>(rightSize);

      for (std::size_t i = 0; i < leftSize; ++i)
      {
        leftVec->at(i) = vec->at(left + i);
      }

      for (std::size_t i = 0; i < rightSize; ++i)
      {
        rightVec->at(i) = vec->at(mid + i + 1);
      }

      std::size_t i = 0, j = 0, k = left;

      while (i < leftSize && j < rightSize)
      {
        vec->at(k++) = compare(rightVec->at(j), leftVec->at(i)) ? leftVec->at(i++) : rightVec->at(j++);
      }

      while (i < leftSize)
      {
        vec->at(k++) = leftVec->at(i++);
      }

      while (j < rightSize)
      {
        vec->at(k++) = rightVec->at(j++);
      }

      leftVec->clear();
      rightVec->clear();
      delete leftVec, rightVec;
    }

    template <typename T>
    static void tim_sort(dby::vector<T> &vec, std::size_t n, bool(*compare)(T, T))
    {
      const int RUN = 32;

      for (std::size_t i = 0; i < n; i += RUN)
      {
        TimSort::insertionSort(vec, i, TimSort::min(i + RUN - 1, n - 1), compare);
      }

      for (std::size_t size = RUN; size < n; size *= 2)
      {
        for (std::size_t left = 0; left < n; left += 2 * size)
        {
          int mid = left + size - 1;
          int right = TimSort::min(left + 2 * size - 1, n - 1);

          if (mid < right)
          {
            TimSort::merge(vec, left, mid, right, compare);
          }
        }
		  }
    }

    template <typename T>
    static void tim_sort(dby::vector<T>* &vec, std::size_t n, bool(*compare)(T, T))
    {
      const int RUN = 32;

      for (std::size_t i = 0; i < n; i += RUN)
      {
        TimSort::insertionSort(vec, i, TimSort::min(i + RUN - 1, n - 1), compare);
      }

      for (std::size_t size = RUN; size < n; size *= 2)
      {
        for (std::size_t left = 0; left < n; left += 2 * size)
        {
          int mid = left + size - 1;
          int right = TimSort::min(left + 2 * size - 1, n - 1);

          if (mid < right)
          {
            TimSort::merge(vec, left, mid, right, compare);
          }
        }
		  }
    }

  public:
    template <typename T>
    static void sort(dby::vector<T> &vec, bool(*compare)(T, T) = [](T a, T b){ return a > b; })
    {
      TimSort::tim_sort(vec, vec.size(), compare);
    }

    template <typename T>
    static void sort(dby::vector<T>* &vec, bool(*compare)(T, T) = [](T a, T b){ return a > b; })
    {
      TimSort::tim_sort(vec, vec->size(), compare);
    }
  };
}

#endif