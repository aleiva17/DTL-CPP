#pragma once
#ifndef _HEAP_HPP_
#define _HEAP_HPP_
#include "vector.hpp"
#include <cstddef>

namespace dby
{
  class Heap
  {
  public:
    template<typename T>
    static void make_heap(dby::vector<T> &vec, bool(*compare)(T, T) = [](T a, T b){ return a < b; })
    {
      for (long long i = vec.size() / 2 - 1; i >= 0; --i)
      {
        dby::Heap::_topDownHeapify(vec, i, compare);
      }
    }

    /**
     * @brief Inserts elements into the heap.
     * 
     * @param data 
     */
    template <typename T>
    static void push_heap(dby::vector<T> &vec, T data, bool(*compare)(T, T) = [](T a, T b){ return a < b; })
    {
      vec.push_back(data);
      if (vec.size() == 1)
      {
        return;
      }

      for (long long i = vec.size() / 2 - 1; i >= 0; --i)
      {
        dby::Heap::_topDownHeapify(vec, i, compare);
      }
    }

    /**
     * @brief Delete the top element of the heap.
     * 
     */
    template <typename T>
    static void pop_heap(dby::vector<T> &vec, bool(*compare)(T, T) = [](T a, T b){ return a < b; })
    {
      if (vec.size() == 0)
      {
        return;
      }

      dby::Heap::_swap(vec.at(0), vec.back());
      vec.pop_back();

      dby::Heap::_topDownHeapify(vec, 0, compare);
    }
  private:
    template <typename T>
    static void _swap(T &a, T &b)
    {
      T aux = a;
      a = b;
      b = aux;
    }

    template <typename T>
    static void _topDownHeapify(dby::vector<T> &vec, std::size_t index, bool(*compare)(T, T))
    {
      std::size_t l = 2 * index + 1;
      std::size_t r = 2 * index + 2;
      std::size_t new_index = index;
      std::size_t sz = vec.size();

      if (l < sz && compare(vec.at(l), vec.at(new_index)))
      {
        new_index = l;
      }
      
      if (r < sz && compare(vec.at(r), vec.at(new_index)))
      {
        new_index = r;
      }

      if (new_index != index)
      {
        dby::Heap::_swap(vec.at(index), vec.at(new_index));
        dby::Heap::_topDownHeapify(vec, new_index, compare);
      }
    }
  };
}

#endif