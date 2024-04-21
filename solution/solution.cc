
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


std::ostream& operator<<(std::ostream& os, const Solution& solution) {
  os << "Solution with " << solution.GetSize() << " elements: ";
  for (Element element : solution.GetElements()) {
    os << element << " ";
  }
  return os;
}