#pragma once
#ifndef _BINARY_SEARCH_HPP_
#define _BINARY_SEARCH_HPP_
#include <cstddef>
#include "vector.hpp"

namespace dby
{
  class BinarySearch
  {
  private:
    template <typename T>
    static int recursiveBinarySearch(dby::vector<T> &vec, int low, int high, T element)
    {
      if (high < low)
      {
        return -1;
      }

      int mid = low + (high - low) / 2;

      if (vec.at(mid) == element)
      {
        return mid;
      }

      if (vec.at(mid) > element)
      {
        return BinarySearch::recursiveBinarySearch(vec, low, mid - 1, element);
      }

      return BinarySearch::recursiveBinarySearch(vec, mid + 1, high, element);
    }

    template <typename T>
    static int recursiveBinarySearch(dby::vector<T>* &vec, int low, int high, T element)
    {
      if (high < low)
      {
        return -1;
      }

      int mid = low + (high - low) / 2;

      if (vec->at(mid) == element)
      {
        return mid;
      }

      if (vec->at(mid) > element)
      {
        return BinarySearch::recursiveBinarySearch(vec, low, mid - 1, element);
      }

      return BinarySearch::recursiveBinarySearch(vec, mid + 1, high, element);
    }

    template <typename T>
    static int iterativeBinarySearch(dby::vector<T> &vec, int low, int high, T element)
    {
      while (low <= high)
      {
        int mid = low + (high - low) / 2;

        if (vec.at(mid) == element)
        {
          return mid;
        }

        if (vec.at(mid) > element)
        {
          high = mid - 1;
        }
        else 
        {
          low = mid + 1;
        }
      }

      return -1;
    }

    template <typename T>
    static int iterativeBinarySearch(dby::vector<T>* &vec, int low, int high, T element)
    {
      while (low <= high)
      {
        int mid = low + (high - low) / 2;

        if (vec->at(mid) == element)
        {
          return mid;
        }

        if (vec->at(mid) > element)
        {
          high = mid - 1;
        }
        else 
        {
          low = mid + 1;
        }
      }

      return -1;
    }

  public:
    template <typename T>
    static int recursive(dby::vector<T> &vec, T element)
    {
      return BinarySearch::recursiveBinarySearch(vec, 0, vec.size() - 1, element);
    }

    template <typename T>
    static int recursive(dby::vector<T>* &vec, T element)
    {
      return BinarySearch::recursiveBinarySearch(vec, 0, vec->size() - 1, element);
    }

    template <typename T>
    static int iterative(dby::vector<T> &vec, T element)
    {
      return BinarySearch::iterativeBinarySearch(vec, 0, vec.size() - 1, element);
    }

    template <typename T>
    static int iterative(dby::vector<T>* &vec, T element)
    {
      return BinarySearch::iterativeBinarySearch(vec, 0, vec->size() - 1, element);
    }
  };
};

#endif