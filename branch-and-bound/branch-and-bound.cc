

#include "branch-and-bound.h"

#include <iostream>
#include <vector>

Solution BranchAndBound::Solve() {
  Solution initialSolution = GRASP(problem_, solutionSize_).Solve();
  LB = initialSolution.CalculatesObjectiveFunction(problem_);
}

void BranchAndBound::CreateActiveNodes() {
  // Node rootNode{Element()};
  // std::vector<Node*> children;
  // for (int i = 0; i < problem_.GetElements().size(); i++) {
  //   Node* child = new Node(problem_.GetElements()[i], &rootNode);
  //   children.push_back(child);
  // }
  std::cout << "ELements size: " << problem_.GetElements().size() << std::endl;
  for (int i = 0; i < problem_.GetElements().size(); i++) {
    Node* rootNode = new Node(problem_.GetElements()[i]);
    std::cout << "Metiendo nodo: " << rootNode->GetElement() << std::endl;
    CreateActiveNodes(rootNode, 1);
    ActiveNodes.push_back(rootNode);
  }

  // ActiveNodes[0]->PrintDescendants();
  // std::cout << "----------------" << std::endl;
  // ActiveNodes[1]->PrintDescendants();
  // std::cout << "----------------" << std::endl;
  // ActiveNodes[2]->PrintDescendants();
  // std::cout << "----------------" << std::endl;
  // ActiveNodes[3]->PrintDescendants();
  // std::cout << "----------------" << std::endl;
  // std::cout << ActiveNodes[4]->GetElement() << std::endl;


  // for (int i = 0; i < ActiveNodes.size(); i++) {
  //   ActiveNodes[i]->PrintDescendants();
  // }

}

bool IsInParents(Node* node, Node* toSearch) {
  std::cout << "ENTRAMOS EN ESTA FUNCION" << std::endl;
  while (node->GetParent() != nullptr) {
    if (node->GetElement() == toSearch->GetElement()) {
      std::cout << "Elemento repetido: " << node->GetElement() << std::endl;
      return true;
    }
    node = node->GetParent();
  }
  return false;
}

void BranchAndBound::CreateActiveNodes(Node* node, int index) {
  if (index == solutionSize_) {
    std::cout << "LEAF NODE: " << node->GetElement() << std::endl;
    node->SetIsLeafNode(true);
    return;
  }
  // std::cout << "NODE: " << node->GetElement() << std::endl;
  std::vector<Node*> children;
  for (int i = 0; i < problem_.GetElements().size(); i++) {
    if (node->GetElement() != problem_.GetElements()[i] && !IsInParents(node, new Node(problem_.GetElements()[i], node))) {
      Node* child = new Node(problem_.GetElements()[i], node);
      children.push_back(child);
      std::cout << "Child: " << child->GetElement() << std::endl;
    } else {
      std::cout << "Elemento repetido: " << problem_.GetElements()[i] << std::endl;
    }
  }
  node->SetChildren(children);
  for (int i = 0; i < children.size(); i++) {
    CreateActiveNodes(children[i], index + 1);
  }

}




// Llamar a esta función con el nodo raíz para imprimir todos los nodos del árbol
// Ejemplo: PrintAllNodes(rootNode);
