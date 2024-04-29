#include <iostream>

#include "local-search.h"

/**
  * @brief Method to solve the problem.
  * @return The best solution found.
  */
Solution LocalSearch::Solve() {
  Solution bestSolution = currentSolution_;
  // print neighbor solutions
  std::vector<Solution> neighbors = GenerateNeighbors(currentSolution_);
  do {
    currentSolution_ = FindBestNeighbor(neighbors);
    if (currentSolution_.CalculatesObjectiveFunction(problem_) > bestSolution.CalculatesObjectiveFunction(problem_)) {
      bestSolution = currentSolution_;
    }
    neighbors = GenerateNeighbors(currentSolution_);
  } while (!IsLocalOptimum(currentSolution_, neighbors));
  return bestSolution;
}

/**
 * @brief Method to solve the problem only evaluating the movement that improves the solution.
 * @return The best solution found.
*/
Solution LocalSearch::SolveModified() {
  Solution bestSolution = currentSolution_;
  // print neighbor solutions
  std::vector<Solution> neighbors = GenerateNeighbors(currentSolution_);
  do {
    currentSolution_ = FindBestNeighbor(neighbors);
    if (currentSolution_.CalculatesObjectiveFunction(problem_) > bestSolution.CalculatesObjectiveFunction(problem_)) {
      bestSolution = currentSolution_;
    }
    neighbors = GenerateNeighbors(currentSolution_);
  } while (!IsLocalOptimum(currentSolution_, neighbors));
  return bestSolution;
}

/**
 * @brief Finds the best neighbor solution.
 * @param neighbors Neighbors to evaluate.
 * @return The best neighbor solution.
*/
Solution LocalSearch::FindBestNeighbor(const std::vector<Solution>& neighbors) {
  Solution bestNeighbor = neighbors[0];
  for (Solution neighbor : neighbors) {
    if (neighbor.CalculatesObjectiveFunction(problem_) > bestNeighbor.CalculatesObjectiveFunction(problem_)) {
      bestNeighbor = neighbor;
    }
  }
  return bestNeighbor;
}

/**
 * @brief Checks if the solution is a local optimum.
 * @param solution Solution to evaluate.
 * @param neighbors Neighbors to evaluate.
 * @return True if the solution is a local optimum, false otherwise.
 */
bool LocalSearch::IsLocalOptimum(Solution& solution, std::vector<Solution>& neighbors) {
  for (Solution& neighbor : neighbors) {
    if (neighbor.CalculatesObjectiveFunction(problem_) > solution.CalculatesObjectiveFunction(problem_)) {
      return false;
    }
  }
  return true;
}