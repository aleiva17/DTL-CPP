#pragma once
#ifndef _FISHER_YATES_HPP_
#define _FISHER_YATES_HPP_
#include "vector.hpp"
#include <cstddef>
#include <cstdlib>

namespace dby
{
  class FisherYates
  {
    static std::size_t randInt(std::size_t bottom, std::size_t top)
    {
      return rand() % (top - bottom + 1) + bottom;
    }

    template <typename T>
    static void swap(T& a, T& b)
    {
      T c = a;
      a = b;
      b = c;
    }
  public:
    template <typename T>
    static void shuffle(dby::vector<T> &vec)
    {
      if (vec.size() == 0)
      {
        return;
      }

      std::size_t i, j;

      for (i = vec.size() - 1; i > 0; --i) {
        j = randInt(0, i - 1);
        dby::FisherYates::swap(vec.at(i), vec.at(j));
      }
    }

    template <typename T>
    static void shuffle(dby::vector<T>* &vec)
    {
      if (vec->size() == 0)
      {
        return;
      }

      std::size_t i, j;

      for (i = vec->size() - 1; i > 0; --i) {
        j = randInt(0, i - 1);
        dby::FisherYates::swap(vec->at(i), vec->at(j));
      }
    }
  };
}

#endif