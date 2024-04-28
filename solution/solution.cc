
#include "solution.h"

double Solution::CalculatesObjectiveFunction(const Problem& problem) {
  double objectiveFunction = 0.0;
  this->SetInSolution(problem.GetElements());
  for (int i = 0; i < problem.GetElementsSize() - 1; i++) {
    for (int j = i + 1; j < problem.GetElementsSize(); j++) {
      if (inSolution[i] && inSolution[j]) {
        objectiveFunction += EuclideanDistance(problem.GetElement(i), problem.GetElement(j));
      }
    }
  }
  return objectiveFunction;
}

void Solution::SetInSolution(const std::vector<Element>& problemElements) {
  inSolution = std::vector<bool>(problemElements.size(), false);
  for (Element element : elements) {
    for (int i = 0; i < problemElements.size(); i++) {
      if (element == problemElements[i]) {
        inSolution[i] = true;
        break;
      }
    }
  }
}

/**
 * @brief Evaluates the diversity of the solution after a movement. Only recalculates
 * the diversity of the elements that are affected by the movement. Compares the contribution
 * of the element in the solution before and after the movement.
 * @param element Element that was moved.
 * @param index Index of the element in the solution.
 * @return The maximum diversity between the element and the other elements in the solution.
 */
Element Solution::EvaluatesMovementDiversity(const Element& element, const int index, const Problem& problem) {
  double diversityBefore = 0.0;
  int initialIndex = index;
  for (int j = initialIndex + 1; j < problem.GetElementsSize(); j++) {
    if (inSolution[initialIndex] && inSolution[j]) {
      diversityBefore += EuclideanDistance(problem.GetElement(initialIndex), problem.GetElement(j));
    }
  }
  double diversityAfter = 0.0;
  for (int j = initialIndex + 1; j < problem.GetElementsSize(); j++) {
    if (inSolution[initialIndex] && inSolution[j]) {
      diversityAfter += EuclideanDistance(element, problem.GetElement(j));
    }
  }
  return diversityAfter > diversityBefore ? element : this->GetElements()[index];
}

/**
  * @brief Calculates the element that differs from the solution.
  * @param solution Solution to compare.
  * @return The element that differs from the solution.
  */
Element Solution::Difference(const Solution& solution) const {
  for (int i = 0; i < this->GetSize(); i++) {
    if (this->GetElements()[i] != solution.GetElements()[i]){
      return this->GetElements()[i];
    }
  }
}


std::ostream& operator<<(std::ostream& os, const Solution& solution) {
  os << "Solution with " << solution.GetSize() << " elements: ";
  for (Element element : solution.GetElements()) {
    os << element << " ";
  }
  return os;
}