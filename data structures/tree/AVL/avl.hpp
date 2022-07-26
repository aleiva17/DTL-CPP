#pragma once
#ifndef _AVL_HPP_
#define _AVL_HPP_
#include <iostream>
#include <queue>
#include <functional>

namespace dby
{
  enum class avl_traverse
  {
    pre_order,
    in_order,
    post_order,
    level_order
  };

  template <class T, class K = T>
  class AVL
  {
    struct Node
    {
      T value;
      Node* left;
      Node* right;
      int h;

      Node(T value, Node* left = nullptr, Node* right = nullptr) : value(value), left(left), right(right), h(0) { }

      ~Node() { }
      
      static int height(Node* n)
      {
        return n == nullptr ? -1: n->h;
      }

      void updateH()
      {
        this->h = std::max(Node::height(this->left), Node::height(this->right)) + 1;
      }
    };
    Node* root;
    std::size_t length;
    std::function<K(T)> key;
  public:
    AVL(std::function<K(T)> key = [](T a){ return a; })
    {
      this->root = nullptr;
      this->key = key;
      this->length = 0;
    }

    ~AVL()
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
      return Node::height(this->root);
    }

    /**
     * @brief Returns the length of the tree.
     * 
     * @return std::size_t 
     */
    std::size_t size()
    {
      return this->length;
    }

    /* ACCESS METHODS */

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
      ++this->length;
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
    bool remove(T value)
    {
      return this->_remove(this->root, value);
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
    void traverse(dby::avl_traverse type, std::function<void(T)>doThis = [](T value){ std::cout << value << ' '; })
    {
      switch(type)
      {
      case dby::avl_traverse::pre_order: this->_pre_order(this->root, doThis); break;
      case dby::avl_traverse::in_order: this->_in_order(this->root, doThis); break;
      case dby::avl_traverse::post_order: this->_post_order(this->root, doThis); break;
      case dby::avl_traverse::level_order: this->_level_order(this->root, doThis); break;
      }
    }

    /**
     * @brief Find if a key is stored in the tree.
     * 
     * @param key
     * @return true 
     * @return false 
     */
    bool search(T value)
    {
      return this->_search(this->root, value);
    }
  private:
    void _rotAB(Node* &node)
    {
      Node* aux = node->left;
      
      node->left = aux->right;
      node->updateH();

      aux->right = node;
      node = aux;

      node->updateH();
    }

    void _rotBA(Node* &node)
    {
      Node* aux = node->right;

      node->right = aux->left;
      node->updateH();

      aux->left = node;
      node = aux;

      node->updateH();
    }

    void _balance(Node* &node)
    {
      int delta = Node::height(node->left) - Node::height(node->right);

      if (delta < -1)
      {
        if (Node::height(node->right->left) > Node::height(node->right->right))
        {
          this->_rotAB(node->right);
        }
        this->_rotBA(node);
      }
      else if (delta > 1)
      {
        if (Node::height(node->left->right) > Node::height(node->left->left))
        {
          this->_rotBA(node->left);
        }
        this->_rotAB(node);
      }
    }

    void _insert(Node* &node, T value)
    {
      if (node == nullptr)
      {
        node = new Node(value);
        return;
      }
      else if (this->key(value) == this->key(node->value))
      {
        --this->length;
        return;
      }
      else if (this->key(value) < this->key(node->value))
      {
        this->_insert(node->left, value);
      }
      else
      {
        this->_insert(node->right, value);
      }

      this->_balance(node);
      node->updateH();
    }

    bool _remove(Node* &node, T value)
    {
      if (node == nullptr)
      {
        return false;
      }

      if (this->key(value) < this->key(node->value))
      {
        return this->_remove(node->left, value);
      }
        
      if (this->key(value) > this->key(node->value))
      {
        return this->_remove(node->right, value);
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

        node->updateH();
        this->_balance(node);

        return true;
      }
      
      if (node->right == nullptr)
      {
        Node* tmp = node;
        node = node->left;
        delete tmp;

        node->updateH();
        this->_balance(node);

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

    bool _search(Node* node, T value)
    {
      if (node == nullptr)
      {
        return false;
      }

      if (this->key(node->value) == this->key(value))
      {
        return true;
      }

      if (this->key(value) < this->key(node->value))
      {
        return this->_search(node->left, value);
      }

      return this->_search(node->right, value);
    }

    T* _find(Node* node, T value)
    {
      if (node == nullptr)
      {
        return nullptr;
      }

      if (this->key(node->value) == this->key(value))
      {
        return &node->value;
      }

      if (this->key(value) < this->key(node->value))
      {
        return this->_find(node->left, value);
      }

      return this->_find(node->right, value);
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