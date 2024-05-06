#include "GRASP.h"

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>


Solution GRASP::Solve() {
  Solution solution;
  Element gravityCenter = CalculatesGravityCenter(problem_.GetElements(), problem_.GetElementDimensions());
  do {
    // Generates the restricted candidate list.
    std::vector<Element> restrictedCandidateList = GetNMostDistantElements(problem_.GetElements(), gravityCenter, 3);
    // Selects a random element from the restricted candidate list.
    int randomIndex = rand() % restrictedCandidateList.size();
    Element randomElement = restrictedCandidateList[randomIndex];
    // Adds the random element to the solution.
    solution.AddElement(randomElement);
    // Removes the random element from the problem.
    problem_.RemoveElement(randomElement);
    // Updates the gravity center.
    gravityCenter = CalculatesGravityCenter(solution.GetElements(), problem_.GetElementDimensions());
  } while (solution.GetSize() < solutionSize_);
  return solution;
}

Solution GRASP::ExecuteNTimes(const int number) {
  Solution bestSolution;
  double bestDistance = std::numeric_limits<double>::max();
  for (int i = 0; i < number; i++) {
    Solution solution = Solve();
    double distance = solution.CalculatesObjectiveFunction(problem_);
    if (distance < bestDistance) {
      bestSolution = solution;
      bestDistance = distance;
    }
  }
  return bestSolution;
}

std::vector<Element> GRASP::GetNMostDistantElements(const std::vector<Element>& elements, const Element& gravityCenter, const int n) {
  std::vector<Element> mostDistantElements;
  std::vector<Element> elementsCopy = elements;
  for (int i = 0; i < n; i++) {
    if (elementsCopy.empty()) {
      break;
    }
    Element mostDistantElement = MostDistantElement(elementsCopy, gravityCenter);
    mostDistantElements.push_back(mostDistantElement);
    elementsCopy.erase(std::find(elementsCopy.begin(), elementsCopy.end(), mostDistantElement));
  }
  return mostDistantElements;
}