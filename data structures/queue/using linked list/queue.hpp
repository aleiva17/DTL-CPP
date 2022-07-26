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
    struct Node
    {
      T data;
      Node* next;
      Node* prev;
      Node(T data, Node* next = nullptr, Node* prev = nullptr) : data(data), next(next), prev(prev) { }
      ~Node() { }
    };
    Node* head;
    Node* tail;
    std::size_t sz;
  public:
    Queue()
    {
      this->head = nullptr;
      this->tail = nullptr;
      this->sz = 0;
    }

    ~Queue()
    {
      while (this->sz)
      {
        this->pop();
      }
    }

    /* CAPACITY METHODS */

    /**
     * @brief Returns the current size of the queue.
     * 
     * @return std::size_t
     */
    inline std::size_t size()
    {
      return this->sz;
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
     * @brief Returns a reference to the first element of the queue.
     * 
     * @return T&
     */
    inline T& front()
    {
      if (this->head == nullptr)
      {
        throw "Error: Queue is empty";
      }
      return this->head->data;
    }

    /**
     * @brief Returns a reference to the last element of the queue.
     * 
     * @return T& 
     */
    inline T& back()
    {
      if (this->tail == nullptr)
      {
        throw "Error: Queue is empty";
      }
      return this->tail->data;
    }

    /* MODIFIER METHODS */

    /**
     * @brief Adds the element 'data' at the end of the queue.
     * 
     * @param data 
     */
    void push(T data)
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
     * @brief Deletes the first element of the queue.
     * 
     */
    void pop()
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
      T data = this->head->data;
      this->pop();
      return data;
    }

    /**
     * @brief Reverses the order of the elements in the queue.
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
  };
}

#endif