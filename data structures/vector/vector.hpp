#pragma once
#ifndef _VECTOR_HPP_
#define _VECTOR_HPP_
#include <initializer_list>
#include <cstddef>

namespace dby
{
  template <class T>
  class vector
  {
  private:
    T* array;
    std::size_t capacity;
  public:
    vector()
    {
      this->array = nullptr;
      this->capacity = 0;
    }

    vector(std::initializer_list<T> list)
    {
      this->capacity = list.size();
      this->array = new T[this->capacity];
      std::size_t it = 0;

      for (const T& val : list) {
        this->array[it++] = val;
      }
    }

    vector(T array[], std::size_t capacity)
    {
      this->capacity = capacity;
      this->array = new T[this->capacity];

      for (std::size_t i = 0; i < this->capacity; ++i)
      {
        this->array[i] = array[i];
      }
    }

    vector(std::size_t initial_capacity)
    {
      this->capacity = initial_capacity;
      this->array = new T[this->capacity];
    }

    vector(std::size_t initial_capacity, T value)
    {
      this->capacity = initial_capacity;
      this->array = new T[this->capacity];

      for (std::size_t i = 0; i < this->capacity; ++i)
      {
        this->array[i] = value;
      }
    }

    ~vector()
    {
      delete[] this->array;
    }

    /* CAPACITY METHODS */

    /**
     * @brief Returns the number of elements in the vector.
     * 
     * @return std::size_t 
     */
    inline std::size_t size()
    {
      return this->capacity;
    }

    /**
     * @brief Returns whether the vector is empty or not.
     * 
     * @return true 
     * @return false 
     */
    inline bool empty()
    {
      return this->capacity == 0;
    }

    /* ACCESS METHODS */

    /**
     * @brief Returns a reference to the element at position 'index' in the vector.
     * 
     * @param index Index of the element to be accessed.
     * @return T value
     */
    inline T& at(std::size_t index)
    {
      if (index < 0 || index >= this->capacity)
      {
        throw "Error: Index out of range";
      }
      return this->array[index];
    }

    inline T& operator[](std::size_t index)
    {
      return this->array[index];
    }

    /**
     * @brief Returns a pointer to the first element in the vector.
     * 
     * @return T* pointer
     */
    inline T* begin()
    {
      return &this->array[0];
    }

    /**
     * @brief Returns a pointer to the theoretical element that follows the last element in the vector.
     * 
     * @return T* pointer
     */
    inline T* end()
    {
      return &this->array[this->capacity];
    }

    /**
     * @brief Returns a reference to the first element in the vector.
     * 
     * @return T value
     */
    inline T& front()
    {
      return this->array[0];
    }

    /**
     * @brief Returns a reference to the last element in the vector
     * 
     * @return T value
     */
    inline T& back()
    {
      return this->array[this->capacity - 1];
    }

    /* MODIFIER METHODS */

    /**
     * @brief Push an element into the vector from the back.
     * 
     * @param value Element to be added.
     */
    void push_back(T value)
    {
      T* aux = new T[this->capacity + 1];

      for (std::size_t i = 0; i < this->capacity; ++i)
      {
        aux[i] = this->array[i];
      }

      aux[this->capacity] = value;
      
      delete[] this->array;
      this->array = aux;
      ++this->capacity; 
    }

    /**
     * @brief Inserts a new element at the specified position.
     * 
     * @param value Element to be inserted.
     * @param index Position.
     */
    void emplace(T value, std::size_t index)
    {
      if (index < 0 || index >= this->capacity)
      {
        return;
      }

      T* aux = new T[this->capacity + 1];

      std::size_t j = 0;
      for (std::size_t i = 0; i < this->capacity + 1; ++i)
      {
        aux[i] = i == index ? value : this->array[j++];
      }

      delete[] this->array;
      this->array = aux;
      ++this->capacity;
    }
    
    /**
     * @brief Pop or remove an element from the back.
     * 
     */
    void pop_back()
    {
      if (this->capacity == 0)
      {
        return;
      }

      T* aux = new T[this->capacity - 1];

      for (std::size_t i = 0; i < this->capacity - 1; ++i)
      {
        aux[i] = this->array[i];
      }

      delete[] this->array;
      this->array = aux;
      --this->capacity;
    }

    /**
     * @brief Resizes the vector so that it contains 'new_size' elements.
     * 
     * @param new_size New vector size.
     */
    void resize(std::size_t new_size)
    {
      if (new_size >= this->capacity || new_size < 0)
      {
        return;
      }

      T* aux = new T[new_size];

      for (std::size_t i = 0; i < new_size; ++i)
      {
        aux[i] = this->array[i];
      }

      delete[] this->array;
      this->array = aux;
      this->capacity = new_size;
    }

    /**
     * @brief Remove an element from the vector at the specified position.
     * 
     * @param index 
     */
    void erase(std::size_t index)
    {
      if (index < 0 || index >= this->capacity)
      {
        return;
      }

      T* aux = new T[this->capacity - 1];

      std::size_t j = 0;
      for (std::size_t i = 0; i < this->capacity; ++i)
      {
        if (i == index)
        {
          continue;
        }
        aux[j++] = this->array[i];
      }

      delete[] this->array;
      this->array = aux;
      --this->capacity;
    }

    /**
     * @brief Remove all the elements of the vector.
     * 
     */
    void clear()
    {
      delete[] this->array;
      this->array = nullptr;
      this->capacity = 0;
    }

    /**
     * @brief Reverses the order of the elements in the vector.
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
        T aux = this->array[i];
        this->array[i] = this->array[j];
        this->array[j] = aux;
        ++i;
        --j;
      }
    }

    /* DECLARATIVE METHODS */

    /**
     * @brief Applies the given function to every element of the vector.
     * 
     * @param doThis Void function that receives T as parameter.
     */
    void for_each(void(*doThis)(T value))
    {
      for (std::size_t i = 0; i < this->capacity; ++i)
      {
        doThis(this->array[i]);
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
        if (condition(this->array[i]))
        {
          doThis(this->array[i]);
        }
      }
    }

    /**
     * @brief Find if a value is stored in the vector by making a comparison.
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
        if (compare(this->array[i], value))
        {
          return true;
        }
      }
      return false;
    }

    /**
     * @brief Find if any element of the vector satisfies a 'condition' function.
     * 
     * @param condition Boolean function that receives T as parameter.
     * @return true 
     * @return false 
     */
    bool search_if(bool(*condition)(T value))
    {
      for (std::size_t i = 0; i < this->capacity; ++i)
      {
        if (condition(this->array[i]))
        {
          return true;
        }
      }
      return false;
    }

    /**
     * @brief Returns the number of elements in the vector for which the 'condition' function returns true
     * 
     * @param condition Boolean function that receives T as parameter.
     * @return std::size_t 
     */
    std::size_t count_if(bool(*condition)(T value))
    {
      std::size_t count = 0;

      for (std::size_t i = 0; i < this->capacity; ++i)
      {
        if (condition(this->array[i]))
        {
          ++count;
        }
      }

      return count;
    }
  };
}

#endif