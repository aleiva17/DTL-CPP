#pragma once
#ifndef _MERGE_SORT_HPP_
#define _MERGE_SORT_HPP_
#include "vector.hpp"
#include <cstddef>

namespace dby
{
  class MergeSort
  {
    template <typename T>
    static void swap(T& a, T& b)
    {
      T c = a;
      a = b;
      b = c;
    }

    template <typename T>
    static void merge(dby::vector<T>* &left, dby::vector<T>* &right, dby::vector<T> &vec, std::size_t n, bool(*compare)(T, T))
    {
      std::size_t i = 0, j = 0, k = 0;
      std::size_t leftSize = n / 2;
      std::size_t rightSize = n - leftSize;

      while (i < leftSize && j < rightSize)
      {
        vec.at(k++) = (compare(right->at(j), left->at(i)) ? left->at(i++) : right->at(j++));
      }

      while (i < leftSize)
      {
        vec.at(k++) = left->at(i++);
      }

      while (j < rightSize)
      {
        vec.at(k++) = right->at(j++);
      }
    }

    template <typename T>
    static void merge(dby::vector<T>* &left, dby::vector<T>* &right, dby::vector<T>* &vec, std::size_t n, bool(*compare)(T, T))
    {
      std::size_t i = 0, j = 0, k = 0;
      std::size_t leftSize = n / 2;
      std::size_t rightSize = n - leftSize;

      while (i < leftSize && j < rightSize)
      {
        vec->at(k++) = (compare(right->at(j), left->at(i)) ? left->at(i++) : right->at(j++));
      }

      while (i < leftSize)
      {
        vec->at(k++) = left->at(i++);
      }

      while (j < rightSize)
      {
        vec->at(k++) = right->at(j++);
      }
    }

    template <typename T>
    static void divide(dby::vector<T> &vec, std::size_t n, bool(*compare)(T, T))
    {
      if (n <= 1)
      {
        return;
      }

      std::size_t mid = n / 2;
      dby::vector<T>* left = new dby::vector<T>(mid);
      dby::vector<T>* right = new dby::vector<T>(n - mid);

      for (size_t i = 0; i < mid; ++i)
      {
        left->at(i) = vec.at(i);
      }

      for (size_t i = mid; i < n; ++i)
      {
        right->at(i - mid) = vec.at(i);
      }

      MergeSort::divide(left, mid, compare);
      MergeSort::divide(right, n - mid, compare);
      MergeSort::merge(left, right, vec, n, compare);
      
      left->clear();
      right->clear();
      delete left, right;
    }

    template <typename T>
    static void divide(dby::vector<T>* &vec, std::size_t n, bool(*compare)(T, T))
    {
      if (n <= 1)
      {
        return;
      }

      std::size_t mid = n / 2;
      dby::vector<T>* left = new dby::vector<T>(mid);
      dby::vector<T>* right = new dby::vector<T>(n - mid);

      for (size_t i = 0; i < mid; ++i)
      {
        left->at(i) = vec->at(i);
      }

      for (size_t i = mid; i < n; ++i)
      {
        right->at(i - mid) = vec->at(i);
      }

      MergeSort::divide(left, mid, compare);
      MergeSort::divide(right, n - mid, compare);
      MergeSort::merge(left, right, vec, n, compare);
      
      left->clear();
      right->clear();
      delete left, right;
    }

  public:
    template <typename T>
    static void sort(dby::vector<T> &vec, bool(*compare)(T, T) = [](T a, T b){ return a > b; })
    {
      MergeSort::divide(vec, vec.size(), compare);
    }

    template <typename T>
    static void sort(dby::vector<T>* &vec, bool(*compare)(T, T) = [](T a, T b){ return a > b; })
    {
      MergeSort::divide(vec, vec->size(), compare);
    }
  };
}

#endif