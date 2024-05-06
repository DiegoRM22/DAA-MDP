#ifndef NODE_H
#define NODE_H

#include <vector>

#include "../element/element.h"

class Node {
 public:
  Node(Element element, std::vector<Node*> children, Node* parent) : element_(element), children_(children), parent_(parent) {}
  Node(Element element, Node* parent) : element_(element), parent_(parent) {}
  Node(Element element, std::vector<Node*> children) : element_(element), children_(children) {}
  Node(Element element) : element_(element) {}

  Element GetElement() const { return element_; }
  std::vector<Node*> GetChildren() const { return children_; }
  Node* GetParent() const { return parent_; }

  void SetElement(const Element& element) { element_ = element; }
  void AddChild(Node* child) { children_.push_back(child); }
  void SetChildren(std::vector<Node*> children) { children_ = children; }
  void SetParent(Node* parent) { parent_ = parent; }
  void SetIsLeafNode(bool isLeafNode) { isLeafNode_ = isLeafNode; }

  void PrintChildren() {
    for (int i = 0; i < children_.size(); i++) {
      std::cout << children_[i]->GetElement() << std::endl;
    }
  }

  void PrintDescendants(int level = 0) {
    for (int i = 0; i < children_.size(); i++) {
      // Imprimir indentación según el nivel del árbol
      for (int j = 0; j < level; ++j) {
        std::cout << "|   ";
      }
      // Imprimir el elemento del nodo actual
      std::cout << "|---" << children_[i]->GetElement() << std::endl;
      // Llamar recursivamente a la función de impresión para los hijos de este nodo
      children_[i]->PrintDescendants(level + 1);
    }
}


 private:
  Element element_;
  std::vector<Node*> children_;
  Node* parent_;
  bool isLeafNode_ = false;
};

#endif // NODE_H