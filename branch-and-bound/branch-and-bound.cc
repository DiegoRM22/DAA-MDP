

#include "branch-and-bound.h"

#include <iostream>
#include <vector>

Solution BranchAndBound::Solve() {
  Solution initialSolution = GRASP(problem_, solutionSize_).Solve();
  LB = initialSolution.CalculatesObjectiveFunction(problem_);
  std::cout << "lB: " << LB << '\n';
  while (!ActiveNodes.empty()) {
    
  }


}

void BranchAndBound::CreateActiveNodes() {

  // std::cout << "ELements size: " << problem_.GetElements().size() << std::endl;
  Node* rootNode;
  for (int i = 0; i < problem_.GetElements().size(); i++) {
    rootNode = new Node(problem_.GetElements()[i]);

    std::cout << "Metiendo nodo: " << rootNode->GetElement() << std::endl;
    CreateActiveNodes(rootNode, 1);
    AddNodeAndDescendantsToActiveNodes(rootNode);
    // ActiveNodes.push_back(rootNode);
  }
}

void BranchAndBound::AddNodeAndDescendantsToActiveNodes(Node* node) {
  // Agregar el nodo actual a ActiveNodes
  ActiveNodes.push_back(node);

  // Recorrer todos los hijos del nodo actual y agregarlos recursivamente
  const std::vector<Node*>& children = node->GetChildren();
  for (int i = 0; i < children.size(); i++) {
    AddNodeAndDescendantsToActiveNodes(children[i]);
  }
}

bool IsInParents(Node* node, Node toSearch) {
  while (node->GetParent() != nullptr) {
    if (node->GetElement() == toSearch.GetElement()) {
      return true;
    }
    node = node->GetParent();
  }
  return false;
}

void BranchAndBound::CreateActiveNodes(Node* node, int index) {
  if (index == solutionSize_) {
    // std::cout << "LEAF NODE: " << node->GetElement() << std::endl;
    node->SetIsLeafNode(true);
    return;
  }
  std::cout << "NODE: " << node->GetElement() << std::endl;
  std::vector<Node*> children;
  for (int i = 0; i < problem_.GetElements().size(); i++) {
    std::cout << "comparando " << problem_.GetElements()[i] << '\n';
    if (node->GetElement() != problem_.GetElements()[i] && !IsInParents(node, Node(problem_.GetElements()[i], node))) {
      Node* child = new Node(problem_.GetElements()[i], node);
      children.push_back(child);
      std::cout << "Child: " << child->GetElement() << std::endl;
    }
  }
  node->SetChildren(children);
  for (int i = 0; i < children.size(); i++) {
    // children[i]->SetParent(node);
    CreateActiveNodes(children[i], index + 1);
  }
}




// Llamar a esta función con el nodo raíz para imprimir todos los nodos del árbol
// Ejemplo: PrintAllNodes(rootNode);
