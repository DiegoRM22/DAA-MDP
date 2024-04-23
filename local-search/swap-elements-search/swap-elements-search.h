#ifndef SWAP_ELEMENTS_SEARCH_H
#define SWAP_ELEMENTS_SEARCH_H

#include <vector>

#include "../../problem/problem.h"
#include "../../solution/solution.h"
#include "../local-search.h"

class SwapElementsSearch : public LocalSearch {
 public:
  SwapElementsSearch(Problem problem, Solution solution) : LocalSearch(problem, solution) {}
  std::vector<Solution> GenerateNeighbors(const Solution& solution) override;
};

#endif // SWAP_ELEMENTS_SEARCH_H