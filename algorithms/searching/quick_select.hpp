#pragma once
#ifndef _QUICK_SELECT_HPP_
#define _QUICK_SELECT_HPP_
#include <cstddef>
#include "vector.hpp"

namespace dby
{
  class QuickSelect 
  {
    template <typename T>
    static void swap(T& a, T& b)
    {
      T c = a;
      a = b;
      b = c;
    }

    template <typename T>
    static int partition(dby::vector<T> &vec, int begin, int end)
    {
      T pivote = vec.at(end);
      int i = begin;

      for (std::size_t j = begin; j < end; ++j) 
      {
        if (vec.at(j) <= pivote) 
        {
          QuickSelect::swap(vec.at(i++), vec.at(j));
        }
      }

      QuickSelect::swap(vec.at(i), vec.at(end));
      return i;
    }

    template <typename T>
    static int partition(dby::vector<T>* &vec, int begin, int end)
    {
      T pivote = vec->at(end);
      int i = begin;

      for (std::size_t j = begin; j < end; ++j) 
      {
        if (vec->at(j) <= pivote)
        {
          QuickSelect::swap(vec->at(i++), vec->at(j));
        }
      }

      QuickSelect::swap(vec->at(i), vec->at(end));
      return i;
    }

    template <typename T>
    static T quickSelect (dby::vector<T> &vec, int begin, int end, int k)
    {
      if (k <= 0 || k > end - begin + 1)
      {
        return -1;
      }

      int index = QuickSelect::partition(vec, begin, end);

      if (index - begin == k - 1)
      {
        return vec.at(index);
      }

      if (index - begin > k - 1)
      {
        return QuickSelect::quickSelect(vec, begin, index - 1, k);
      }

      return QuickSelect::quickSelect(vec, index + 1, end, k - index + begin - 1);
    }

    template <typename T>
    static T quickSelect (dby::vector<T>* &vec, int begin, int end, int k)
    {
      if (k <= 0 || k > end - begin + 1)
      {
        return -1;
      }

      int index = QuickSelect::partition(vec, begin, end);

      if (index - begin == k - 1)
      {
        return vec->at(index);
      }

      if (index - begin > k - 1)
      {
        return QuickSelect::quickSelect(vec, begin, index - 1, k);
      }

      return QuickSelect::quickSelect(vec, index + 1, end, k - index + begin - 1);
    }

  public:
    template <typename T>
    static T kthSmallest(dby::vector<T> &vec, int k)
    {
      return QuickSelect::quickSelect(vec, 0, vec.size() - 1, k);
    }

    template <typename T>
    static T kthSmallest(dby::vector<T>* &vec, int k)
    {
      return QuickSelect::quickSelect(vec, 0, vec->size() - 1, k);
    }

    template <typename T>
    static T kthLargest(dby::vector<T> &vec, int k)
    {
      return QuickSelect::quickSelect(vec, 0, vec.size() - 1, vec.size() - k + 1);
    }

    template <typename T>
    static T kthLargest(dby::vector<T>* &vec, int k)
    {
      return QuickSelect::quickSelect(vec, 0, vec->size() - 1, vec->size() - k + 1);
    }
  };
}

#endif