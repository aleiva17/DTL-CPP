#pragma once
#ifndef _QUEUE_HPP_
#define _QUEUE_HPP_
#include <cstddef>

namespace dby
{
  template <class T>
  class Queue
  {
  private:
    T* array;
    long long current;
    std::size_t capacity;
  public:
    Queue(std::size_t capacity)
    {
      this->current = -1;
      this->capacity = capacity;
      this->array = new T[this->capacity];
    }

    ~Queue()
    {
      delete[] this->array;
    }

    /* CAPACITY METHODS */

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
     * @brief Returns the current size of the queue.
     * 
     * @return std::size_t
     */
    inline std::size_t size()
    {
      return this->current + 1;
    }

    /**
     * @brief Returns whether the queue is full or not.
     * 
     * @return true
     * @return false
     */
    inline bool full()
    {
      return this->current + 1 == this->capacity;
    }

    /**
     * @brief Returns whether the queue is empty or not.
     * 
     * @return true 
     * @return false 
     */
    inline bool empty()
    {
      return this->current == -1;
    }

    /* ACCESS METHODS */

    /**
     * @brief Returns a reference to the first element of the queue.
     * 
     * @return T&
     */
    inline T& front()
    {
      if (this->empty())
      {
        throw "Error: Queue is empty";
      }
      return this->array[0];
    }

    /**
     * @brief Returns a reference to the last element of the queue.
     * 
     * @return T& 
     */
    inline T& back()
    {
      if (this->empty())
      {
        throw "Error: Queue is empty";
      }
      return this->array[this->current];
    }

    /* MODIFIER METHODS */

    /**
     * @brief Adds the element 'data' at the end of the queue.
     * 
     * @param data 
     */
    void push(T data)
    {
      if (this->full())
      {
        return;
      }
      this->array[++this->current] = data;
    }

    /**
     * @brief Deletes the first element of the queue.
     * 
     */
    void pop()
    {
      if (this->empty())
      {
        return;
      }

      for (std::size_t i = 1; i < this->current + 1; ++i)
      {
        this->array[i - 1] = this->array[i];
      }
      --this->current;
    }

    /**
     * @brief Returns and deletes the first element of the queue.
     * 
     * @return T
     */
    T extract()
    {
      if (this->empty())
      {
        throw "Error: Queue is empty";
      }
      T data = this->array[0];
      this->pop();
      return data;
    }

    /**
     * @brief Reverses the order of the elements in the queue.
     * 
     */
    void reverse()
    {
      if (this->current == -1)
      {
        return;
      }

      std::size_t i = 0;
      long long j = this->current;

      while (i < j)
      {
        T aux = this->array[i];
        this->array[i] = this->array[j];
        this->array[j] = aux;
        ++i;
        --j;
      }
    }
  };
}

#endif