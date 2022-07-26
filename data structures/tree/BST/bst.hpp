#pragma once
#ifndef _BST_HPP_
#define _BST_HPP_
#include <iostream>
#include <queue>
#include <functional>

namespace dby
{
  enum class bst_traverse
  {
    pre_order,
    in_order,
    post_order,
    level_order
  };

  template <class T>
  class BST
  {
    struct Node 
    {
      T value;
      Node* left;
      Node* right;
      Node(T value, Node* left = nullptr, Node* right = nullptr) : value(value), left(left), right(right) { }
      ~Node() { }
    };
    
    Node* root;
    std::function<bool(T, T)>compare;
    std::function<bool(T, T)>equals;
  public:
    BST()
    {
      this->root = nullptr;
      this->compare = [](T a, T b){ return a < b; };
      this->equals = [](T a, T b){ return a == b; };
    }

    BST(std::function<bool(T, T)>compare, std::function<bool(T, T)>equals)
    {
      this->root = nullptr;
      this->compare = compare;
      this->equals = equals;
    }

    ~BST()
    {
      this->_destroy_tree(this->root);
    }

    /* CAPACITY METHODS */

    /**
     * @brief Returns the height of the tree.
     * 
     * @return std::size_t 
     */
    std::size_t height()
    {
      std::size_t h = this->_height(this->root);
      return h - (h != 0);
    }

    /**
     * @brief Returns the total count of nodes in the tree.
     * 
     * @return std::size_t 
     */
    std::size_t count_nodes()
    {
      return this->_count_nodes(this->root);
    }

    /* ACCESS METHODS */

    /**
     * @brief Returns a pointer to the lowest element of the tree.
     * 
     * @return T* 
     */
    T* lowest_element()
    {
      if (this->root == nullptr)
      {
        return nullptr;
      }

      Node* it = this->root;

      while (it->left != nullptr)
      {
        it = it->left;
      }

      return &it->value;
    }

    /**
     * @brief Returns a pointer to the highest element of the tree.
     * 
     * @return T* 
     */
    T* highest_element()
    {
      if (this->root == nullptr)
      {
        return nullptr;
      }

      Node* it = this->root;

      while (it->right != nullptr)
      {
        it = it->right;
      }

      return &it->value;
    }

    /**
     * @brief Returns a pointer to the value if exists in the tree. 
     * 
     * @param key 
     * @return V*
     * @return nullptr
     */
    T* find(T value)
    {
      return this->_find(root, value);
    }

    /* MODIFIER METHODS */

    /**
     * @brief Adds a new element in the tree.
     * 
     * @param value 
     */
    void insert(T value)
    {
      if (this->root == nullptr)
      {
        this->root = new Node(value);
        return;
      }
      this->_insert(this->root, value);
    }
    
    /**
     * @brief Remove an element from the tree if exists.
     * 
     * @param key 
     * @return true 
     * @return false 
     */
    bool remove(T key)
    {
      return this->_remove(this->root, key);
    }

    /**
     * @brief Destroys the tree.
     * 
     */
    void destroy_tree()
    {
      this->_destroy_tree(this->root);
    }

    /* DECLARATIVE METHODS */

    /**
     * @brief Traverse through the tree elements.
     * 
     * @param type Type of tree traversal
     * @param doThis Optional void function that receives T as parameter.
     */
    void traverse(dby::bst_traverse type, std::function<void(T)>doThis = [](T value){ std::cout << value << ' '; })
    {
      switch (type)
      {
      case dby::bst_traverse::pre_order: this->_pre_order(this->root, doThis); break;
      case dby::bst_traverse::in_order: this->_in_order(this->root, doThis); break;
      case dby::bst_traverse::post_order: this->_post_order(this->root, doThis); break;
      case dby::bst_traverse::level_order: this->_level_order(this->root, doThis);
      }
    }

    /**
     * @brief Returns the number of elements in the tree for which the 'condition' function returns true.
     * 
     * @param condition Boolean function that receives T as parameter.
     * @return std::size_t 
     */
    std::size_t count_if(std::function<bool(T)>condition)
    {
      return this->_count_if(root, condition);
    }

    /**
     * @brief Find if a key is stored in the tree.
     * 
     * @param key
     * @return true 
     * @return false 
     */
    bool search(T key)
    {
      return this->_search(root, key);
    }
  private:
    std::size_t _height(Node* node)
    {
      if (node == nullptr)
      {
        return 0;
      }

      return std::max(this->_height(node->left), this->_height(node->right)) + 1;
    }

    bool _remove(Node* &node, T key)
    {
      if (node == nullptr)
      {
        return false;
      }

      if (this->compare(key, node->value))
      {
        return this->_remove(node->left, key);
      }
        
      if (this->compare(node->value, key))
      {
        return this->_remove(node->right, key);
      }
        
      if (node->left == nullptr && node->right == nullptr)
      {
        delete node;
        node = nullptr;
        return true;
      }
        
      if (node->left == nullptr)
      {
        Node* tmp = node;
        node = node->right;
        delete tmp;
        return true;
      }
        
      if (node->right == nullptr)
      {
        Node* tmp = node;
        node = node->left;
        delete tmp;
        return true;
      }

      Node* next = this->_successor(node);
      node->value = next->value;
      return this->_remove(root->right, next->value);
    }

    Node* _successor(Node* node)
    {
      Node* current = node->right;
      while(current && current->left)
      {
        current = current->left;
      }
      return current;
    }

    bool _search(Node* node, T key)
    {
      if (node == nullptr)
      {
        return false;
      }

      if (this->equals(node->value, key))
      {
        return true;
      }

      if (this->compare(key, node->value))
      {
        return this->_search(node->left, key);
      }

      return this->_search(node->right, key);
    }

    std::size_t _count_nodes(Node* node) 
    {
      if (node == nullptr) 
      {
        return 0;
      }

      return 1 + this->_count_nodes(node->left) + this->_count_nodes(node->right);
    }

    std::size_t _count_if(Node* node, std::function<bool(T)>&condition) 
    {
      if (node == nullptr) 
      {
        return 0;
      }

      return condition(node->value) + this->_count_if(node->left, condition) + this->_count_if(node->right, condition);
    }

    void _destroy_tree(Node* node)
    {
      if (node == nullptr)
      {
        return;
      }
      this->_destroy_tree(node->left);
      this->_destroy_tree(node->right);
      delete node;
    }

    T* _find(Node* node, T value)
    {
      if (node == nullptr)
      {
        return nullptr;
      }

      if (this->equals(node->value, value))
      {
        return &node->value;
      }

      if (this->compare(value, node->value))
      {
        return this->_find(node->left, value);
      }

      return this->_find(node->right, value);
    }
      
    void _insert(Node* node, T value)
    {
      if (this->equals(value, node->value))
      {
        return;
      }

      if (this->compare(value, node->value))
      {
        if (node->left == nullptr)
        {
          node->left = new Node(value);
          return;
        }
        this->_insert(node->left, value);
      }
      else
      {
        if (node->right == nullptr)
        {
          node->right = new Node(value);
          return;
        }
        this->_insert(node->right, value);
      }
    }

    void _pre_order(Node* node, std::function<void(T)>&doThis)
    {
      if (node == nullptr)
      {
        return;
      }
        
      doThis(node->value);
      this->_pre_order(node->left, doThis);
      this->_pre_order(node->right, doThis);
    }

    void _in_order(Node* node, std::function<void(T)>&doThis)
    {
      if (node == nullptr)
      {
        return;
      }

      this->_in_order(node->left, doThis);
      doThis(node->value);
      this->_in_order(node->right, doThis);
    }

    void _post_order(Node* node, std::function<void(T)>&doThis)
    {
      if (node == nullptr)
      {
        return;
      }

      this->_post_order(node->left, doThis);
      this->_post_order(node->right, doThis);
      doThis(node->value);
    }

    void _level_order(Node* node, std::function<void(T)>&doThis)
    {
      if (node == nullptr)
      {
        return;
      }

      std::queue<Node*> q;
      q.push(node);

      while (!q.empty())
      {
        Node* otherNode = q.front();
        doThis(otherNode->value);
        q.pop();

        if (otherNode->left != nullptr)
        {
          q.push(otherNode->left);
        }

        if (otherNode->right != nullptr)
        {
          q.push(otherNode->right);
        }
      }
    }
  };
}

#endif