
#include <algorithm>
#include <queue>
#include <vector>


#include "tabu-search.h"

Solution TabuSearch::Solve() {
  Solution bestSolution = GRASP(problem_, 3).Solve();
  double bestDistance = bestSolution.CalculatesObjectiveFunction(problem_);
  
  Solution currentSolution = bestSolution;
  int iterations = 0;
  while (iterations < maxIterations_) {
    Solution candidateSolution = GenerateCandidateSolution(currentSolution, bestSolution);
    double candidateDistance = candidateSolution.CalculatesObjectiveFunction(problem_);
    if (candidateDistance > bestDistance) {
      bestSolution = candidateSolution;
      bestDistance = candidateDistance;
    }
    tabuList_.push(FindMovement(currentSolution, candidateSolution));
    if (tabuList_.size() > tabuListSize_) {
      tabuList_.pop();
    }
    currentSolution = candidateSolution;
    iterations++;
  }
  return bestSolution;
}

Solution TabuSearch::GenerateCandidateSolution(Solution currentSolution, Solution bestSolution) {
  SwapElementsSearch swapElementsSearch(problem_, currentSolution);
  std::vector<Solution> neighbors = swapElementsSearch.GenerateNeighbors(currentSolution);
  Solution bestNeighbor = swapElementsSearch.FindBestNeighbor(neighbors);
  // Comprobar si el movimiento es tabu
  Movement movement = FindMovement(currentSolution, bestNeighbor);
  if (!IsInTabuList(movement)) {
    // Si no está en la lista tabú, se acepta
    return bestNeighbor;
  } else {
    // Criterio de aspiración.
    // Si está en la lista tabú, se acepta si es mejor que la mejor solución encontrada hasta ahora
    if (bestNeighbor.CalculatesObjectiveFunction(problem_) > bestSolution.CalculatesObjectiveFunction(problem_)) {
      return bestNeighbor;
    } else {
      // Si no es mejor, se acepta el mejor vecino no tabú
      while (IsInTabuList(movement)) {
        neighbors.erase(std::remove(neighbors.begin(), neighbors.end(), bestNeighbor), neighbors.end());
        bestNeighbor = swapElementsSearch.FindBestNeighbor(neighbors);
        movement = FindMovement(currentSolution, bestNeighbor);
      }
      return bestNeighbor;
    }
  }
}

Movement TabuSearch::FindMovement(const Solution& originalSolution, const Solution& bestNeighbor) {
  // encontrar el movimiento que ha llevado de originalSolution a bestNeighbor
  Element element1;
  Element element2;
  for (int i = 0; i < originalSolution.GetElements().size(); i++) {
    if (originalSolution.GetElements()[i] != bestNeighbor.GetElements()[i]) {
      element1 = originalSolution.GetElements()[i];
      element2 = bestNeighbor.GetElements()[i];
      break;
    }
  }
  return Movement(element1, element2);
}

bool TabuSearch::IsInTabuList(const Movement& movement) {
  // recorre la lista tabú y comprueba si el movimiento está en ella
  std::queue<Movement> aux = tabuList_;
  while (!aux.empty()) {
    if (aux.front() == movement) {
      return true;
    }
    aux.pop();
  }
  return false;
}
