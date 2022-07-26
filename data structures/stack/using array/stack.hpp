#pragma once
#ifndef _STACK_HPP_
#define _STACK_HPP_
#include <cstddef>

namespace dby
{
  template <class T>
  class Stack
  {
  private:
    T* array;
    long long current;
    std::size_t capacity;
  public:
    Stack(std::size_t capacity)
    {
      this->current = -1;
      this->capacity = capacity;
      this->array = new T[this->capacity];
    }

    ~Stack()
    {
      delete[] this->array;
    }

    /* CAPACITY METHODS */

    /**
     * @brief Returns the max size of the stack.
     * 
     * @return std::size_t
     */
    inline std::size_t max_size()
    {
      return this->capacity;
    }

    /**
     * @brief Returns the current size of the stack.
     * 
     * @return std::size_t
     */
    inline std::size_t size()
    {
      return this->current + 1;
    }

    /**
     * @brief Returns whether the stack is full or not.
     * 
     * @return true
     * @return false
     */
    inline bool full()
    {
      return this->current + 1 == this->capacity;
    }

    /**
     * @brief Returns whether the stack is empty or not.
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
     * @brief Returns a reference to the top most element of the stack
     * 
     * @return T&
     */
    inline T& top()
    {
      if (this->empty())
      {
        throw "Error: Stack is empty";
      }
      return this->array[this->current];
    }

    /* MODIFIER METHODS */

    /**
     * @brief Adds the element 'data' at the top of the stack.
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
     * @brief Deletes the top most element of the stack.
     * 
     */
    void pop()
    {
      if (this->current >= 0)
      {
        --this->current;
      }
    }

    /**
     * @brief Returns and deletes the top most element of the stack.
     * 
     * @return T
     */
    T extract()
    {
      if (this->empty())
      {
        throw "Error: Stack is empty";
      }
      --this->current;
      return this->array[this->current + 1];
    }

    /**
     * @brief Reverses the order of the elements in the stack.
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