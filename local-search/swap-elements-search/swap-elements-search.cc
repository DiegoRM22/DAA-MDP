
#include "swap-elements-search.h"

#include <iostream>


/**
 * @brief Generates the neighbors of a solution by swapping an elemnt in the
 * solution with an element not in the solution.
 * @param solution Solution to generate neighbors.
 * @return The neighbors of the solution.
 */
std::vector<Solution> SwapElementsSearch::GenerateNeighbors(const Solution& solution) {
  std::vector<Solution> neighbors;
  std::vector<Element> elements = problem_.GetElements();
  std::vector<bool> inSolution = solution.GetInSolution();
  int indexSolution = 0;
  for (int i = 0; i < inSolution.size(); i++) {
    if (inSolution[i]) {
      for (int j = 0; j < elements.size(); j++) {
        if (!inSolution[j]) {
          Solution neighbor = solution;
          neighbor.ReplaceElement(elements[j], indexSolution);
          neighbors.push_back(neighbor);
        }
      }
      ++indexSolution;
    }
  }
  return neighbors;
}