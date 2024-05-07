

#include "branch-and-bound.h"

#include <iostream>
#include <vector>
#include <algorithm>


Solution BranchAndBound::Solve() {
  Solution initialSolution = GRASP(problem_, solutionSize_).Solve();
  std::cout << "Initial solution: " << initialSolution << '\n';
  LB = initialSolution.CalculatesObjectiveFunction(problem_);
  std::cout << "lB: " << LB << '\n';
  while (!ActiveNodes.empty()) {
    // std::cout << "Active nodes size: " << ActiveNodes.size() << '\n';
    Node* node = ActiveNodes.front();
    if (node->IsLeafNode()) {
      Solution solution = GetSolutionFromLeafNode(node);
      double distance = solution.CalculatesObjectiveFunction(problem_);
      if (distance > LB) {
        LB = distance;
        std::cout << "New LB: " << LB << '\n';
        std::cout << "Solution: " << solution << '\n';
      }
      ActiveNodes.erase(ActiveNodes.begin());
    } else {
      Solution partialSolution = GetPartialSolution(node);
      if (partialSolution.GetSize() < solutionSize_) {
        std::cout << "Partial solution: ";
        std::cout << partialSolution << '\n';
        // Compute dmax for the partial solution
        std::vector<Element> UnSelectedElements = GetUnselectedElements(partialSolution);
        if (ComputeDmax(partialSolution) < ComputeDmin(UnSelectedElements)) {
          // std::cout << "Pruning" << '\n';
          ActiveNodes.erase(ActiveNodes.begin());
          continue;
        } else {
          // Computing the Upper Bound: z1 + UB23 of node
          // z1 is the objective function of the partial solution
          double z1 = partialSolution.CalculatesObjectiveFunction(problem_);
          std::cout << "Solution: " << partialSolution << '\n';
          double UB23 = CalculateUB23(partialSolution);
          std::vector<Element> selectedVertices = SelectVerticesWithMaxZValues(partialSolution, solutionSize_ - partialSolution.GetSize());
          // Compute the value z' of solution x = (51, 52, .., Sk Vi, V2..., Va )
          Solution AddedSolution;
          for (int i = 0; i < selectedVertices.size(); i++) {
            AddedSolution.AddElement(selectedVertices[i]);
          }
          double zPrime = CalculatesZPrime(partialSolution, AddedSolution);
          if (zPrime > LB) {
            std::cout << "New LB: " << zPrime << '\n';
            LB = zPrime;
          }
          if (z1 + UB23 < LB) {
            // std::cout << "Pruning" << '\n';
            ActiveNodes.erase(ActiveNodes.begin());
            continue;
          } else if (zPrime < z1 + UB23) {
            // Calculate IUB.
            double IUB = CalculateIUB(LB, partialSolution);
            if (IUB < LB) {
              // std::cout << "Pruning" << '\n';
              ActiveNodes.erase(ActiveNodes.begin());
              continue;
            }
            ActiveNodes.erase(ActiveNodes.begin());
            ActiveNodes.push_back(node);
          } else {
            // add the child nodes to the active nodes
            std::vector<Node*> children = node->GetChildren();
            for (int i = 0; i < children.size(); i++) {
              ActiveNodes.push_back(children[i]);
            }
            ActiveNodes.erase(ActiveNodes.begin());
          }
        }
      } else {
        ActiveNodes.erase(ActiveNodes.begin());
      }
    }
  }
}

double BranchAndBound::CalculateIUB(double z, Solution partialSolution) {
  // Calcular el valor z para la solución parcial
  double zValue = partialSolution.CalculatesObjectiveFunction(problem_);
  // Obtener los vértices con los valores UBz
  std::vector<Element> selectedVertices = SelectVerticesWithMaxZValues(partialSolution, solutionSize_ - partialSolution.GetSize());
  // Inicializar IUB con el valor z
  double IUB = z;
  // Calcular z + UBz para cada vértice seleccionado y actualizar IUB si es necesario
  for (const Element& vertex : selectedVertices) {
    double UBzValue = CalculateUB23(partialSolution, vertex);
    double currentIUB = zValue + UBzValue;
    if (currentIUB > IUB) {
      IUB = currentIUB;
    }
  }
  return IUB;
}


double BranchAndBound::CalculatesZ2(Solution partialSolution, Solution AddedSolution) {
  // Caculates the distance between the new solution and the partial solution
  double z2 = 0.0;
  for (int i = 0; i < partialSolution.GetSize(); i++) {
    for (int j = 0; j < AddedSolution.GetSize(); j++) {
      z2 += EuclideanDistance(partialSolution.GetElement(i), AddedSolution.GetElement(j));
    }
  }
  return z2;
}

double BranchAndBound::CalculatesZPrime(Solution partialSolution, Solution AddedSolution) {
  double zPrime = 0.0;
  // Z prime is z1 + z2 + z3
  // z1 is the objective function of the partial solution
  double z1 = partialSolution.CalculatesObjectiveFunction(problem_);
  double z2 = CalculatesZ2(partialSolution, AddedSolution);
  double z3 = AddedSolution.CalculatesObjectiveFunction(problem_);
  zPrime = z1 + z2 + z3;
  return zPrime;
}

std::vector<Element> BranchAndBound::SelectVerticesWithMaxZValues(const Solution& partialSolution, int left) {
  std::vector<Element> selectedVertices;

  // Obtener todos los vértices de la solución parcial
  std::vector<Element> partialElements = partialSolution.GetElements();

  // Calcular el valor z para cada vértice y almacenarlo junto con el vértice
  std::vector<std::pair<Element, double>> zValues;
  for (const Element& vertex : problem_.GetElements()) {
    // Verificar si el vértice ya está en la solución parcial
    if (std::find(partialElements.begin(), partialElements.end(), vertex) == partialElements.end()) {
      double zValue = CalculateZValue(vertex, partialSolution);
      zValues.push_back(std::make_pair(vertex, zValue));
    }
  }

  // Ordenar los vértices en función de sus valores z de manera descendente
  std::sort(zValues.begin(), zValues.end(), [](const std::pair<Element, double>& a, const std::pair<Element, double>& b) {
    return a.second > b.second;
  });

  // Seleccionar los primeros left vértices de la lista ordenada
  for (int i = 0; i < left && i < zValues.size(); ++i) {
    selectedVertices.push_back(zValues[i].first);
  }

  return selectedVertices;
}

double BranchAndBound::CalculateUB23(const Solution& partialSolution, const Element& element) {
  // Now element it is not able to be selected
  double UB23 = 0.0;
  std::vector<Element> unselectedElements = GetUnselectedElements(partialSolution);
  std::vector<double> zValues;
  for (int i = 0; i < unselectedElements.size(); i++) {
    double zValue = CalculateZValue(unselectedElements[i], partialSolution);
    if (unselectedElements[i] != element) {
      zValues.push_back(zValue);
    }
  }
  std::sort(zValues.begin(), zValues.end());
  // Obtener las m - k mayores distancias
  for (int i = 0; i < solutionSize_ - partialSolution.GetSize(); i++) {
    UB23 += zValues[i];
  }
  return UB23;
}


double BranchAndBound::CalculateUB23(const Solution& partialSolution) {
  double UB23 = 0.0;
  std::vector<Element> unselectedElements = GetUnselectedElements(partialSolution);
  std::vector<double> zValues;
  for (int i = 0; i < unselectedElements.size(); i++) {
    double zValue = CalculateZValue(unselectedElements[i], partialSolution);
    zValues.push_back(zValue);
  }
  std::sort(zValues.begin(), zValues.end());
  // Obtener las m - k mayores distancias
  for (int i = 0; i < solutionSize_ - partialSolution.GetSize(); i++) {
    UB23 += zValues[i];
  }
  return UB23;
}

double BranchAndBound::CalculateZValue(const Element& element, const Solution& partialSolution) {
  double zValue = 0.0;
  // Distancia entre el elemento y los elementos de la solución parcial
  for (int i = 0; i < partialSolution.GetSize(); i++) {
    zValue += EuclideanDistance(element, partialSolution.GetElement(i));
  }
  // Sumar el mayor valor de la distancia entre el elemento y los elementos que no están en la solución parcial
  std::vector<Element> unselectedElements = GetUnselectedElements(partialSolution);
  double maxDistance = 0.0;
  for (int i = 0; i < unselectedElements.size(); i++) {
    double distance = EuclideanDistance(element, unselectedElements[i]);
    if (distance > maxDistance) {
      maxDistance = distance;
    }
  }
  zValue += maxDistance / 2;
  return zValue;
}

std::vector<Element> BranchAndBound::GetUnselectedElements(const Solution& partialSolution) {
  // elements - partial solution
  std::vector<Element> elements = problem_.GetElements();
  std::vector<Element> partialElements = partialSolution.GetElements();
  std::vector<Element> unselectedElements;
  for (int i = 0; i < elements.size(); i++) {
    if (std::find(partialElements.begin(), partialElements.end(), elements[i]) == partialElements.end()) {
      unselectedElements.push_back(elements[i]);
    }
  }
  return unselectedElements;
}

double BranchAndBound::ComputeDminForElement(const Element& element, const int left) {
  double dmin = 0.0;
  std::vector<Element> sortedVertexes = GetSortedVertexes(element);
  std::reverse(sortedVertexes.begin(), sortedVertexes.end());
  for (int i = 0; i < left; i++) {
    dmin += EuclideanDistance(sortedVertexes[i], element);
  }
  return dmin;
}

double BranchAndBound::ComputeDmin(const std::vector<Element>& elements) {
  double dmin = 0.0;
  int left = solutionSize_ - elements.size();
  for (int i = 0; i < elements.size(); i++) {
    dmin += ComputeDminForElement(elements[i], left);
  }
  return dmin;
}

double BranchAndBound::ComputeDmaxForElement(const Element& element, const int left) {
  double dmax = 0.0;
  std::vector<Element> sortedVertexes = GetSortedVertexes(element);
  for (int i = 0; i < left; i++) {
    dmax += EuclideanDistance(sortedVertexes[i], element);
  }
  return dmax;
}


double BranchAndBound::ComputeDmax(const Solution& solution) {
  double dmax = 0.0;
  int left = solutionSize_ - solution.GetSize();
  for (int i = 0; i < solution.GetSize(); i++) {
    dmax += ComputeDmaxForElement(solution.GetElement(i), left);
  }
  return dmax;
}
    

std::vector<Element> BranchAndBound::GetSortedVertexes(Element element) {
  // Sort the vertexes by distance to the element
  std::vector<Element> sortedVertexes = problem_.GetElements();
  std::sort(sortedVertexes.begin(), sortedVertexes.end(), [&element](Element a, Element b) {
    return EuclideanDistance(a, element) < EuclideanDistance(b, element);
  });
  return sortedVertexes;
}

void BranchAndBound::ComputeLeafNodes() {
  for (int i = 0; i < ActiveNodes.size(); i++) {
    int parentCount = 0;
    while (ActiveNodes[i]->GetParent() != nullptr) {
      parentCount++;
      ActiveNodes[i] = ActiveNodes[i]->GetParent();
    }
    if (parentCount == solutionSize_) {
      ActiveNodes[i]->SetIsLeafNode(true);
    }
  }
}


void BranchAndBound::CreateActiveNodes() {
  // std::cout << "ELements size: " << problem_.GetElements().size() << std::endl;
  Node* rootNode;
  for (int i = 0; i < problem_.GetElements().size(); i++) {
    rootNode = new Node(problem_.GetElements()[i]);

    CreateActiveNodes(rootNode, 1);
    AddNodeAndDescendantsToActiveNodes(rootNode);
    // ActiveNodes.push_back(rootNode);
  }
}

Solution BranchAndBound::GetPartialSolution(Node* node) {
  Solution solution;
  while (node != nullptr) {
    solution.AddElement(node->GetElement());
    node = node->GetParent();
  }
  return solution;
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

void BranchAndBound::PrintParents(Node* node) {
  if (node->GetParent() != nullptr) {
    std::cout << node->GetElement() << " -> ";
    PrintParents(node->GetParent());
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

Solution BranchAndBound::GetSolutionFromLeafNode(Node* node) {
  Solution solution;
  while (node->GetParent() != nullptr) {
    solution.AddElement(node->GetElement());
    node = node->GetParent();
  }
  return solution;
}

void BranchAndBound::CreateActiveNodes(Node* node, int index) {
  if (index == solutionSize_ + 1) {
    // std::cout << "LEAF NODE: " << node->GetElement() << std::endl;
    node->SetIsLeafNode(true);
    return;
  }
  std::vector<Node*> children;
  for (int i = 0; i < problem_.GetElements().size(); i++) {
    if (node->GetElement() != problem_.GetElements()[i] && !IsInParents(node, Node(problem_.GetElements()[i], node))) {
      Node* child = new Node(problem_.GetElements()[i], node);
      children.push_back(child);
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
