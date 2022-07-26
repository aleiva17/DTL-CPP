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
    struct Node
    {
      T data;
      Node* next;
      Node(T data, Node* next = nullptr) : data(data), next(next) { }
      ~Node() { }
    };
    Node* head;
    std::size_t sz;
  public:
    Stack()
    {
      this->head = nullptr;
      this->sz = 0;
    }

    ~Stack()
    {
      while (this->sz)
      {
        this->pop();
      }
    }

    /* CAPACITY METHODS */

    /**
     * @brief Returns the current size of the stack.
     * 
     * @return std::size_t
     */
    inline std::size_t size()
    {
      return this->sz;
    }

    /**
     * @brief Returns whether the stack is empty or not.
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
     * @brief Returns a reference to the top most element of the stack
     * 
     * @return T&
     */
    inline T& top()
    {
      if (this->head == nullptr)
      {
        throw "Error: Stack is empty";
      }
      return this->head->data;
    }

    /* MODIFIER METHODS */

    /**
     * @brief Adds the element 'data' at the top of the stack.
     * 
     * @param data 
     */
    void push(T data)
    {
      this->head = new Node(data, this->head);
      ++this->sz;
    }

    /**
     * @brief Deletes the top most element of the stack.
     * 
     */
    void pop()
    {
      if (this->head == nullptr)
      {
        return;
      }
      Node* toDelete = this->head;
      this->head = this->head->next;

      toDelete->next = nullptr;
      delete toDelete;
      
      --this->sz;
    }

    /**
     * @brief Returns and deletes the top most element of the stack.
     * 
     * @return T
     */
    T extract()
    {
      if (this->head == nullptr)
      {
        throw "Error: Stack is empty";
      }
      T data = this->head->data;
      this->pop();
      return data;
    }

    /**
     * @brief Reverses the order of the elements in the stack.
     * 
     */
    void reverse()
    {
      if (this->head == nullptr)
      {
        return;
      }

      Node* present = this->head;
      Node* past = this->head;
      Node* future = this->head->next;
      past->next = nullptr;

      while (future != nullptr)
      {
        present = future;
        future = future->next;
        present->next = past;
        past = present;
      }

      this->head = present;
    }
  };
}

#endif