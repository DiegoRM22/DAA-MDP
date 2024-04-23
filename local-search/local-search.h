
#ifndef LOCAL_SEARCH_H
#define LOCAL_SEARCH_H

#include <vector>

#include "../problem/problem.h"
#include "../solution/solution.h"

class LocalSearch {
 public:
  LocalSearch(Problem problem, Solution solution) : problem_(problem), currentSolution_(solution) {}
  Solution Solve();
  Solution GenerateRandomSolution();
  virtual std::vector<Solution> GenerateNeighbors(const Solution& solution) = 0;
  Solution FindBetterNeighbor(const std::vector<Solution>& neighbors);
  Solution FindBestNeighbor(const std::vector<Solution>& neighbors);
  bool IsLocalOptimum(Solution& solution, std::vector<Solution>& neighbors);
 protected:
  Solution currentSolution_;
  Problem problem_;
};

#endif // LOCAL_SEARCH_H