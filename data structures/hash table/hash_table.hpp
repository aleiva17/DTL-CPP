#pragma once
#ifndef _HASH_TABLE_HPP_
#define _HASH_TABLE_HPP_
#include <list>
#include <vector>
#include <string>
#include <cstddef>

namespace dby
{
  template <class K, class V>
  class HashTable
  {
  private:
    std::size_t bucketSize;
    std::vector<std::list<std::pair<K, V>>> table;
  public:
    HashTable(std::size_t initial_size, bool strict_mode = false)
    {
      this->bucketSize = strict_mode ? initial_size : this->_next_prime(initial_size);
      for (std::size_t i = 0; i < this->bucketSize; ++i)
      {
        std::list<std::pair<K, V>> l;
        this->table.push_back(l);
      }
    }

    ~HashTable()
    {
      for (std::list<std::pair<K, V>> &p : this->table)
      {
        p.clear();
      }
      this->table.clear();
    }

    /* ACCESS METHODS */

    /**
     * @brief Returns a pointer to the value if the 'key' exists in the HashTable. 
     * 
     * @param key 
     * @return V*
     * @return nullptr
     */
    V* get(K key)
    {
      std::size_t ind = this->_hash_function(key);
      std::list<std::pair<K, V>> &items = this->table.at(ind);

      for (std::pair<K, V> &it : items) 
      {
        if (it.first == key) 
        {
          return &it.second;
        }
      }

      return nullptr;
    }

    /* MODIFIER METHODS */

    /**
     * @brief Adds an element with the specified key and value into the HashTable.
     * 
     * @param key 
     * @param value 
     */
    void insert(K key, V value)
    {
      if (this->search(key))
      {
        return;
      }
      std::size_t index = this->_hash_function(key);
      this->table.at(index).push_back(std::make_pair(key, value));
    }

    /**
     * @brief Removes an element if the 'key' exists in the HashTable.
     * 
     * @param key 
     */
    void remove(K key)
    {
      std::size_t index = this->_hash_function(key);
      std::list<std::pair<K, V>> &temp = this->table.at(index);
      temp.remove_if([&key](std::pair<K, V> p) { return key == p.first; });
    }

    /* DECLARATIVE METHODS */

    /**
     * @brief Applies the given function to every element of the HashTable.
     * 
     * @param doThis Void function that receives a pair <Key, Value> as parameter.
     */
    void for_each(void(*doThis)(std::pair<K, V> value)) {
      for (std::size_t i = 0; i < this->bucketSize; ++i)
      {
        if (this->table.at(i).size() == 0)
        {
          continue;
        }

        std::list<std::pair<K, V>> &temp = this->table.at(i);

        for (std::pair<K, V> &it : temp)
        {
          doThis(it);
        }
      }
    }

    void for_each(void(*doThisCell)(int), void(*doThisList)(std::pair<K, V>), bool every_cell = false) {
      for (std::size_t i = 0; i < this->bucketSize; ++i)
      {
        if (this->table.at(i).size() == 0)
        {
          if (every_cell)
          {
            doThisCell(i);
          }
          continue;
        }

        std::list<std::pair<K, V>> &temp = this->table.at(i);

        doThisCell(i);
        for (std::pair<K, V> &it : temp)
        {
          doThisList(it);
        }
      }
    }

    /**
     * @brief Check whether a particular key is present in the HashTable or not.
     * 
     * @param key 
     * @return true 
     * @return false 
     */
    bool search(K key)
    {
      std::size_t ind = this->_hash_function(key);
      std::list<std::pair<K, V>> &items = this->table.at(ind);

      for (std::pair<K, V> &it : items) 
      {
        if (it.first == key) 
        {
          return true;
        }
      }

      return false;
    }

    /**
     * @brief Returns the number of collisions in the HashTable.
     * 
     * @return std::size_t 
     */
    std::size_t count_collisions() 
    {
      std::size_t count = 0;

      for (std::size_t i = 0; i < this->bucketSize; ++i)
      {
        if (this->table.at(i).size() == 0)
        {
          continue;
        }
        count += this->table.at(i).size() - 1;
      }

      return count;
    }

  private:
    bool _is_prime(std::size_t num)
    {
      for (std::size_t i = 2; i * i <= num; ++i)
      {
        if (num % i == 0)
        {
          return false;
        }
      }
      return true;
    }

    std::size_t _next_prime(std::size_t num)
    {
      if (num <= 2)
      {
        return 3;
      }

      std::size_t init, end, ans;

      init = num + 1 + (num % 2);
      end = 2 * init - 2;

      for (ans = init; ans < end; ans = ans + 2)
      {
        if (this->_is_prime(ans))
        {
          break;
        }
      }
      return ans;
    }

    std::size_t _hash_function(int key)
    {
      return key % this->bucketSize;
    }

    std::size_t _hash_function(std::string key)
    {
      return this->_horner_polinomial_hash(key);
    }

    std::size_t _horner_polinomial_hash(std::string key)
    {
      for (char &c : key)
      {
        c = tolower(c);
      }

      const int C = 31;
      std::size_t index = key.at(0) - 'a' + 1;
      std::size_t n = key.size();

      for (std::size_t i = 1; i < n; ++i)
      {
        index = (((index % this->bucketSize * C % this->bucketSize) % this->bucketSize) + ((key.at(i) - 'a' + 1) % this->bucketSize)) % this->bucketSize;
      }

      return index % this->bucketSize;
    }
  };
}

#endif