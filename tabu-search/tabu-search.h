#ifndef TABU_SEARCH_H
#define TABU_SEARCH_H

#include <vector>
#include <iostream>
#include <queue>

#include "../problem/problem.h"
#include "../solution/solution.h"
#include "../local-search/local-search.h"
#include "../local-search/swap-elements-search/swap-elements-search.h"
#include "../GRASP/GRASP.h"
#include "../movement/movement.h"


class TabuSearch {
 public:
  TabuSearch(Problem problem, int tabuListSize, int maxIterations) : problem_(problem), tabuListSize_(tabuListSize), maxIterations_(maxIterations) {}
  Solution Solve(const Solution& initialSolution = Solution());
  Movement FindMovement(const Solution& originalSolution, const Solution& bestNeighbor);
  bool IsInTabuList(const Movement& movement);
  Solution GenerateCandidateSolution(Solution currentSolution, Solution bestSolution);

 private:
  Problem problem_;
  int tabuListSize_;
  int maxIterations_;
  std::queue<Movement> tabuList_;
};

#endif