#pragma once
#ifndef _ARRAY_HPP_
#define _ARRAY_HPP_
#include <initializer_list>
#include <cstddef>

namespace dby
{
  template <class T, std::size_t N>
  class array
  {
  private:
    T* arr;
    std::size_t capacity;
  public:
    array()
    {
      this->capacity = N;
      this->arr = new T[this->capacity];
    }

    array(T value)
    {
      this->capacity = N;
      this->arr = new T[this->capacity];
      for (std::size_t i = 0; i < this->capacity; ++i)
      {
        this->arr[i] = value;
      }
    }

    array(std::initializer_list<T> list)
    {
      if (N != list.size())
      {
        throw "Error: Size doesn't match with initializer list.";
      }
      this->capacity = N;
      this->arr = new T[this->capacity];
      std::size_t it = 0;

      for (const T& val : list) {
        this->arr[it++] = val;
      }
    }

    ~array()
    {
      delete[] this->arr;
    }

    /* CAPACITY METHODS */

    /**
     * @brief Returns the number of elements in the array.
     * 
     * @return std::size_t 
     */
    inline std::size_t size()
    {
      return this->capacity;
    }

    /* ACCESS METHODS */

    /**
     * @brief Returns a reference to the element at position 'index' in the array.
     * 
     * @param index Index of the element to be accessed.
     * @return T value
     */
    inline T& at(std::size_t index)
    {
      if (index < 0 || index >= this->capacity) throw "Error: Index out of range";
      return this->arr[index];
    }

    inline T& operator[](std::size_t index)
    {
      return this->arr[index];
    }

    /**
     * @brief Returns a pointer to the first element in the array.
     * 
     * @return T* pointer
     */
    inline T* begin()
    {
      return &this->arr[0];
    }

    /**
     * @brief Returns a pointer to the theoretical element that follows the last element in the array.
     * 
     * @return T* pointer
     */
    inline T* end()
    {
      return &this->arr[this->capacity];
    }

    /**
     * @brief Returns a reference to the first element in the array.
     * 
     * @return T value
     */
    inline T front()
    {
      return this->arr[0];
    }

    /**
     * @brief Returns a reference to the last element in the array.
     * 
     * @return T value
     */
    inline T back()
    {
      return this->arr[this->capacity - 1];
    }

    /* MODIFIER METHODS */

    /**
     * @brief Fill all the indexes of the array with a similar value.
     * 
     * @param value 
     */
    void fill(T value)
    {
      for (std::size_t i = 0; i < this->capacity; ++i)
      {
        this->arr[i] = value;
      }
    }

    /**
     * @brief Reverses the order of the elements in the array.
     * 
     */
    void reverse()
    {
      if (this->capacity <= 1)
      {
        return;
      }

      std::size_t i = 0, j = this->capacity - 1;
      
      while (i < j)
      {
        T aux = this->arr[i];
        this->arr[i] = this->arr[j];
        this->arr[j] = aux;
        ++i;
        --j;
      }
    }

    /* DECLARATIVE METHODS */

    /**
     * @brief Applies the given function to every element of the array.
     * 
     * @param doThis Void function that receives T as parameter.
     */
    void for_each(void(*doThis)(T value))
    {
      for (std::size_t i = 0; i < this->capacity; ++i)
      {
        doThis(this->arr[i]);
      }
    }

    /**
     * @brief If the 'condition' function is true it applies the 'doThis' function.
     * 
     * @param condition Boolean function that receives T as parameter.
     * @param doThis Void function that receives T as parameter.
     */
    void filter(bool(*condition)(T value), void(*doThis)(T value))
    {
      for (std::size_t i = 0; i < this->capacity; ++i)
      {
        if (condition(this->arr[i]))
        {
          doThis(this->arr[i]);
        }
      }
    }

    /**
     * @brief Find if a value is stored in the array by making a comparison.
     * 
     * @param value 
     * @param compare Optional parameter to modify the compare behavior between two elements.
     * @return true 
     * @return false 
     */
    bool search(T value, bool(*compare)(T first_val, T second_val) = [](T a, T b){ return a == b; })
    {
      for (std::size_t i = 0; i < this->capacity; ++i)
      {
        if (compare(this->arr[i], value))
        {
          return true;
        }
      }
      return false;
    }

    /**
     * @brief Find if any element of the array satisfies a 'condition' function.
     * 
     * @param condition Boolean function that receives T as parameter.
     * @return true 
     * @return false 
     */
    bool search_if(bool(*condition)(T value))
    {
      for (std::size_t i = 0; i < this->capacity; ++i)
      {
        if (condition(this->arr[i]))
        {
          return true;
        }
      }
      return false;
    }

    /**
     * @brief Returns the number of elements in the array for which the 'condition' function returns true
     * 
     * @param condition Boolean function that receives T as parameter.
     * @return std::size_t 
     */
    std::size_t count_if(bool(*condition)(T value))
    {
      std::size_t count = 0;

      for (std::size_t i = 0; i < this->capacity; ++i)
      {
        if (condition(this->arr[i]))
        {
          ++count;
        }
      }

      return count;
    }
  };
}

#endif