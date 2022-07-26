#pragma once
#ifndef _PRIORITY_QUEUE_HPP_
#define _PRIORITY_QUEUE_HPP_
#include <cstddef>

namespace dby
{
  template<class T>
  class PriorityQueue 
  {
  private:
    T* array;
    std::size_t sz;
    std::size_t capacity;
    bool(*compare)(T, T);
  public:
    PriorityQueue(std::size_t capacity)
    {
      this->sz = 0;
      this->capacity = capacity;
      this->array = new T[this->capacity];
      this->compare = [](T a, T b) { return a > b; };
    }

    PriorityQueue(std::size_t capacity, bool(*compare)(T, T))
    {
      this->sz = 0;
      this->capacity = capacity;
      this->array = new T[this->capacity];
      this->compare = compare;
    }

    ~PriorityQueue()
    {
      delete[] this->array;
    }

    /* CAPACITY METHODS */

    /**
     * @brief Returns the number of elements in the queue.
     * 
     * @return std::size_t 
     */
    inline std::size_t size()
    {
      return this->sz;
    }

    /**
     * @brief Returns the max size of the queue.
     * 
     * @return std::size_t 
     */
    inline std::size_t max_size()
    {
      return this->capacity;
    }

    /**
     * @brief Returns whether the queue is empty or not.
     * 
     * @return true 
     * @return false 
     */
    inline bool empty()
    {
      return this->sz == 0;
    }

    /* ACCESS METHODS */

    /**
     * @brief Returns the topmost element of the queue.
     * 
     * @return T 
     */
    T top()
    {
      if (this->sz == 0)
      {
        throw "Error: Priority Queue is empty";
      }
      return this->array[0];
    }

    /* MODIFIER METHODS */

    /**
     * @brief Adds the element 'data' at the end of the queue.
     * 
     * @param data 
     */
    void push(T data)
    {
      if (this->sz == this->capacity)
      {
        return;
      }

      this->array[this->sz++] = data;
      this->_bottomUpHeapify(this->sz - 1);
    }

    /**
     * @brief Deletes the first element of the queue.
     * 
     */
    void pop()
    {
      if (this->sz == 0)
      {
        return;
      }

      this->_swap(this->array[0], this->array[this->sz]);
      --this->sz;

      this->_topDownHeapify(0);
    }

    /**
     * @brief Returns and deletes the first element of the queue.
     * 
     * @return T
     */
    T extract()
    {
      if (this->sz == 0)
      {
        throw "Error: Priority Queue is empty";
      }

      T data = this->array[0];
      
      this->_swap(this->array[0], this->array[this->sz - 1]);
      --this->sz;
      
      this->_topDownHeapify(0);
      return data;
    }

  private:
    void _swap(T &a, T &b)
    {
      T aux = a;
      a = b;
      b = aux;
    }

    inline std::size_t _parent(std::size_t index)
    {
      return (index - 1) / 2;
    }

    
    inline std::size_t _left(std::size_t index)
    {
      return 2 * index + 1;
    }

    
    inline std::size_t _right(std::size_t index)
    {
      return 2 * index + 2;
    }

    void _bottomUpHeapify(std::size_t index)
    {
      if (index <= 0)
      {
        return;
      }

      std::size_t parentIndex = this->_parent(index);

      if (this->compare(this->array[index], this->array[parentIndex]))
      {
        this->_swap(this->array[index], this->array[parentIndex]);
        this->_bottomUpHeapify(parentIndex);
      }
    }

    void _topDownHeapify(std::size_t index)
    {
      std::size_t l = this->_left(index);
      std::size_t r = this->_right(index);
      std::size_t new_index = index;

      if (l < this->sz && this->compare(this->array[l], this->array[new_index]))
      {
        new_index = l;
      }
      
      if (r < this->sz && this->compare(this->array[r], this->array[new_index]))
      {
        new_index = r;
      }
  
      if (new_index != index)
      {
        this->_swap(this->array[index], this->array[new_index]);
        this->_topDownHeapify(new_index);
        return;
      }
    }
  };
}

#endif