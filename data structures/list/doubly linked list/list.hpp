#pragma once
#ifndef _LIST_HPP_
#define _LIST_HPP_
#include <initializer_list>
#include <cstddef>

namespace dby
{
  template <class T>
  class List
  {
  private:
    struct Node
    {
      T data;
      Node* next;
      Node* prev;
      Node(T data, Node* next = nullptr, Node* prev = nullptr) : data(data), next(next), prev(prev) { }
      ~Node() { };
    };
    Node* head;
    Node* tail;
    std::size_t sz;
  public:
    List()
    {
      this->head = nullptr;
      this->tail = nullptr;
      this->sz = 0;
    }

    List(std::initializer_list<T> list)
    {
      this->head = nullptr;
      this->tail = nullptr;
      this->sz = 0;

      for (const T& val : list)
      {
        this->push_back(val);
      }
    }

    ~List()
    {
      this->_destroyList(this->head);
      this->head = nullptr;
      this->tail = nullptr;
    }

    /* CAPACITY METHODS */

    /**
     * @brief Returns the number of elements in the list.
     * 
     * @return std::size_t 
     */
    inline std::size_t size()
    {
      return this->sz;
    }

    /**
     * @brief Returns whether the list is empty or not.
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
     * @brief Returns a reference to the first element in the list.
     * 
     * @return T value
     */
    inline T& front()
    {
      if (this->head == nullptr)
      {
        throw "Error: Empty list";
      }
      return this->head->data;
    }

    /**
     * @brief Returns a reference to the last element in the list.
     * 
     * @return T value
     */
    inline T& back()
    {
      if (this->tail == nullptr)
      {
        throw "Error: Empty list";
      }
      return this->tail->data;
    }

    /**
     * @brief Returns a reference to the middle element in the list.
     * 
     * @return T value
     */
    T& middle()
    {
      if (this->head == nullptr)
      {
        throw "Error: Empty list";
      }

      Node* it = this->head;
      std::size_t mid = this->sz / 2;

      for (std::size_t i = 0; i < mid; ++i)
      {
        it = it->next;
      }

      return it->data;
    }

    /**
     * @brief Returns a reference to the element at position 'index' in the list.
     * 
     * @param index Index of the element to be accessed.
     * @return T value
     */
    T& at(std::size_t index)
    {
      if (index < 0 || index >= this->sz)
      {
        throw "Error: Index out of range";
      }

      if (index == 0)
      {
        return this->head->data;
      }

      if (index == this->sz - 1)
      {
        return this->tail->data;
      }

      std::size_t mid = this->sz / 2;
      Node* it = nullptr;

      if (index < mid)
      {
        it = this->head;

        for (std::size_t curr = 0; curr < index; ++curr)
        {
          it = it->next;
        }
      }
      else
      {
        it = this->tail;
        
        for (std::size_t curr = this->sz - 1; curr > index; --curr)
        {
          it = it->prev;
        }
      }

      return it->data;
    }

    /* MODIFIER METHODS */

    /**
     * @brief Insert a new element at a specified position.
     * 
     * @param index
     * @param data
     */
    void insert(std::size_t index, T data)
    {
      if (index < 0 || index > this->sz)
      {
        return;
      }
      
      ++this->sz;

      if (this->head == nullptr)
      {
        if (index != 0)
        {
          return;
        }
        this->head = new Node(data, this->head);
        this->tail = this->head;
        return;
      }

      if (index == 0)
      {
        this->head = new Node(data, this->head);
        this->head->next->prev = this->head;
        return;
      }

      if (index == this->sz - 1)
      {
        this->tail->next = new Node(data);
        this->tail->next->prev = this->tail;
        this->tail = this->tail->next;
        return;
      }

      Node* before = nullptr;
      Node* it = this->head;

      for (std::size_t i = 0; i < index; ++i)
      {
        before = it;
        it = it->next;
      }

      before->next = new Node(data, it, before);
      it->prev = before->next;
    }

    /**
     * @brief Adds a new element at the beginning of the list.
     * 
     * @param data Element to be added.
     */
    void push_front(T data)
    {
      this->head = new Node(data, this->head);

      if (this->sz == 0)
      {
        this->tail = this->head;
      }
      else{
        this->head->next->prev = this->head;
      }
      
      ++this->sz;
    }

    /**
     * @brief Adds a new element at the end of the list.
     * 
     * @param data Element to be added.
     */
    void push_back(T data)
    {
      ++this->sz;

      if (this->head == nullptr)
      {
        this->head = new Node(data);
        this->tail = this->head;
        return;
      }

      this->tail->next = new Node(data, nullptr, this->tail);
      this->tail = this->tail->next;
    }

    /**
     * @brief Remove an element from the list at the specified position.
     * 
     * @param index 
     */
    void erase(std::size_t index)
    {
      if (index < 0 || index >= this->sz)
      {
        return;
      }

      if (index == 0)
      {
        this->pop_front();
        return;
      }

      if (index == this->sz - 1)
      {
        this->pop_back();
        return;
      }
      
      Node* before = nullptr;
      Node* it = this->head;

      for (std::size_t i = 0; i < index; ++i)
      {
        before = it;
        it = it->next;
      }

      before->next = it->next;
      it->next->prev = before;

      it->next = nullptr;
      it->prev = nullptr;
      delete it;

      --this->sz;
    }

    /**
     * @brief Removes the first element of the list.
     * 
     */
    void pop_front()
    {
      if (this->head == nullptr)
      {
        return;
      }

      --this->sz;
      Node* toDelete = this->head;
      this->head = this->head->next;

      toDelete->next = nullptr;
      delete toDelete;

      if (this->head == nullptr)
      {
        this->tail = nullptr;
      }
      else
      {
        this->head->prev = nullptr;
      }
    }

    /**
     * @brief Removes the last element of the list.
     * 
     */
    void pop_back()
    {
      if (this->head == nullptr)
      {
        return;
      }

      --this->sz;

      if (this->head->next == nullptr)
      {
        delete this->head;
        this->head = nullptr;
        this->tail = nullptr;
        return;
      }

      Node* before = this->tail->prev;
      before->next = nullptr;
      this->tail->prev = nullptr;
      delete this->tail;
      this->tail = before;
    }

    /**
     * @brief Resizes the list so that it contains 'new_size' elements.
     * 
     * @param new_size
     */
    void resize(std::size_t new_size)
    {
      if (new_size < 0 || new_size >= this->sz)
      {
        return;
      }

      if (new_size == 0)
      {
        this->clear();
        return;
      }

      Node* before = nullptr;
      Node* it = this->head;
      
      for (std::size_t i = 0; i < new_size; ++i)
      {
        before = it;
        it = it->next;
      }

      before->next = nullptr;
      it->prev = nullptr;
      this->tail = before;
      this->_destroyList(it);

      this->sz = new_size;
    }

    /**
     * @brief Reverses the order of the elements in the list.
     * 
     */
    void reverse()
    {
      if (this->head == nullptr)
      {
        return;
      }

      this->tail = head;
      Node* present = this->head;
      Node* past = this->head;
      Node* future = this->head->next;
      past->next = nullptr;

      while (future != nullptr)
      {
        present = future;
        past->prev = present;

        future = future->next;

        present->next = past;
        present->prev = nullptr;

        past = present;
      }

      this->head = present;
    }

    /**
     * @brief Sorts the list using a compare function (incresing order by default).
     * 
     * @param compare Swap the elements if the condition returns true.
     */
    void sort(bool(*compare)(T a, T b) = [](T a, T b){ return a > b; })
    {
      if (this->sz <= 1)
      {
        return;
      }
      this->head = this->_sort(this->head, compare);
      this->_end(this->tail);
    }

    /**
     * @brief Remove all the elements of the list.
     * 
     */
    void clear()
    {
      this->_destroyList(this->head);
      this->head = nullptr;
      this->tail = nullptr;
      this->sz = 0;
    }

    /* DECLARATIVE METHODS */

    /**
     * @brief Applies the given function to every element of the list in normal or reverse order.
     * 
     * @param doThis Void function that receives T as parameter.
     * @param reverse Optional parameter to indicate whether the iteration order is reversed or not.
     */
    void for_each(void(*doThis)(T data), bool reverse = false)
    {
      Node* it = reverse ? this->tail : this->head;

      while (it != nullptr)
      {
        doThis(it->data);
        it = reverse ? it->prev : it->next;
      }
    }

    /**
     * @brief If the 'condition' function is true it applies the 'doThis' function.
     * 
     * @param condition Boolean function that receives T as parameter.
     * @param doThis Void function that receives T as parameter.
     */
    void filter(bool(*condition)(T data), void(*doThis)(T data))
    {
      Node* it = this->head;

      while (it != nullptr)
      {
        if (condition(it->data))
        {
          doThis(it->data);
        }
        it = it->next;
      }
    }

    /**
     * @brief Find if a value is stored in the list by making a comparison.
     * 
     * @param value 
     * @param compare Optional parameter to modify the compare behavior between two elements.
     * @return true 
     * @return false 
     */
    bool search(T value, bool(*compare)(T first_val, T second_val) = [](T a, T b){ return a == b; })
    {
      Node* it = this->head;

      while (it != nullptr)
      {
        if (compare(it->value, value))
        {
          return true;
        }
        it = it->next;
      }

      return false;
    }

    /**
     * @brief Find if any element of the list satisfies a 'condition' function.
     * 
     * @param condition Boolean function that receives T as parameter.
     * @return true 
     * @return false 
     */
    bool search_if(bool(*condition)(T value))
    {
      Node* it = this->head;

      while (it != nullptr)
      {
        if (condition(it->data))
        {
          return true;
        }
        it = it->next;
      }
      
      return false;
    }

    /**
     * @brief Returns a pointer to the data if it is stored in the list.
     * 
     * @param data Data value to find.
     * @param comparison Optional parameter to modify the compare behavior between two elements.
     * @return T* 
     */
    T* find(T data, bool(*comparison)(T a, T b) = [](T a, T b){ return a == b; })
    {
      Node* it = this->head;

      while (it != nullptr)
      {
        if (comparison(data, it->data))
        {
          return &it->data;
        }
        it = it->next;
      }

      return nullptr;
    }

    /**
     * @brief Returns the number of elements in the list for which the 'condition' function returns true
     * 
     * @param condition Boolean function that receives T as parameter.
     * @return std::size_t 
     */
    std::size_t count_if(bool(*condition)(T value))
    {
      std::size_t count = 0;
      Node* it = this->head;

      while (it != nullptr)
      {
        if (condition(it->data))
        {
          ++count;
        }
        it = it->next;
      }

      return count;
    }

  private:
    void _destroyList(Node* &node)
    {
      if (node == nullptr)
      {
        return;
      }

      this->_destroyList(node->next);
      delete node;
    }

    Node* _merge(Node* left, Node* right, bool(*compare)(T a, T b))
    {
      if (left == nullptr)
      {
        return right;
      }

      if (right == nullptr)
      {
        return left;
      }

      if (compare(right->data, left->data))
      {
        left->next = this->_merge(left->next, right, compare);
        left->next->prev = left;
        left->prev = nullptr;
        return left;
      }

      right->next = this->_merge(left, right->next, compare);
      right->next->prev = right;
      right->prev = nullptr;
      return right;
    }

    Node* _split(Node* node)
    {
      Node* faster = node;
      Node* slower = node;

      while (faster->next != nullptr && faster->next->next != nullptr)
      {
        slower = slower->next;
        faster = faster->next->next;
      }

      Node* mid = slower->next;
      slower->next = nullptr;

      return mid;
    }

    Node* _sort(Node* node, bool(*compare)(T a, T b))
    {
      if (node == nullptr || node->next == nullptr)
      {
        return node;
      }

      Node* right = this->_split(node);

      node = this->_sort(node, compare);
      right = this->_sort(right, compare);

      return this->_merge(node, right, compare);
    }

    void _end(Node* &node)
    {
      while (node->next != nullptr)
      {
        node = node->next;
      }
    }
  };
}

#endif