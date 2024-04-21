
#include "greedy.h"

/**
 * @brief Solve the problem using a greedy algorithm.
*/
Solution Greedy::Solve() {
  // Create the solution with the most distant element.
  Solution solution;
  // Calculate the gravity center of the problem.
  Element gravityCenter = CalculatesGravityCenter(problem_.GetElements(), problem_.GetElementDimensions());
  do {
    // Find the most distant element from the gravity center.
    Element mostDistantElement = MostDistantElement(problem_.GetElements(), gravityCenter);
    // Add the most distant element to the solution.
    solution.AddElement(mostDistantElement);
    // Remove the most distant element from the problem.
    problem_.RemoveElement(mostDistantElement);
    // Update the gravity center.
    gravityCenter = CalculatesGravityCenter(solution.GetElements(), problem_.GetElementDimensions());
  } while (solution.GetSize() < solutionSize_);
  return solution;
}