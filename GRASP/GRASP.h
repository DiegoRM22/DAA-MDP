#ifndef GRASP_H
#define GRASP_H

#include <vector>

#include "../element/element.h"
#include "../problem/problem.h"
#include "../utils/utils.h"
#include "../solution/solution.h"

class GRASP {
 public:
  GRASP(const Problem& problem, const int solutionSize) : problem_(problem), solutionSize_(solutionSize) {}
  Solution Solve();
  Solution ExecuteNTimes(const int number);
  std::vector<Element> GetNMostDistantElements(const std::vector<Element>& elements, const Element& gravityCenter, const int n);
 private:
  Problem problem_;
  int solutionSize_;
};

#endif