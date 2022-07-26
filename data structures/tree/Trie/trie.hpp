#pragma once
#ifndef _TRIE_HPP_
#define _TRIE_HPP_
#include <string>
#include <vector>

namespace dby
{
  class Trie
  {
  private:
    struct Node
    {
      std::vector<Node*> children;
      bool isLeaf;

      Node() 
      {
        this->children = std::vector<Node*>(26, 0);
        this->isLeaf = false;
      }

      ~Node()
      {
        this->children.clear();
      }

      int to_index(char c) 
      {
        return c - 97;
      }

      void add_child(char c)
      {
        int index = this->to_index(c);

        if (this->children.at(index) == 0) 
        {
          this->children.at(index) = new Node();
        }
      }

      Node* get_child(char c)
      {
        int index = this->to_index(c);
        return this->children.at(index);
      }
    };
    Node* root;
  public:
    Trie()
    {
      this->root = nullptr;
    }

    ~Trie()
    {
      delete this->root;
    }

    /**
     * @brief Inserts the string 'word' into the trie.
     * 
     * @param word 
     */
    void insert(std::string word)
    {
      if (this->root == nullptr)
      {
        this->root = new Node();
      }

      Node* current = this->root;

      for (char c : word)
      {
        current->add_child(c);
        current = current->get_child(c);
      }

      current->isLeaf = true;
    }

    /**
     * @brief Returs true if the string 'word' is in the trie.
     * 
     * @param word 
     * @return true 
     * @return false 
     */
    bool search(std::string word)
    {
      if (this->root == nullptr)
      {
        return false;
      }

      Node* current = this->root;

      for (char c : word)
      {
        current = current->get_child(c);

        if (current == 0)
        {
          return false;
        }
      }

      return current->isLeaf;
    }

    /**
     * @brief Returns true if there is a previously inserted string word that has the prefix 'prefix'.
     * 
     * @param prefix 
     * @return true 
     * @return false 
     */
    bool starts_with(std::string prefix)
    {
      if (this->root == nullptr)
      {
        return false;
      }

      Node* current = this->root;

      for (char c : prefix)
      {
        current = current->get_child(c);

        if (current == 0)
        {
          return false;
        }
      }

      return true;
    }
  };
} 


#endif